#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define len 200

void command_execute(char *command, char **arguments, int input_fd, int output_fd) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating process");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        //дочерний процесс

        //проверяем нужно ли перенаправить ввод
        if (input_fd != STDIN_FILENO) { //если input_fd не равен STDIN_FILENO, значит нужно изменить текущий ввод дочернего процесса
            dup2(input_fd, STDIN_FILENO); //дублируем input_fd в стандартный ввод (STDIN_FILENO). Когда дочерний процесс читает из стандартного ввода, он будет читать из input_fd
            close(input_fd); //после дублирования удяляем ненужный оригинальный файловый дескриптор
        }

        //проверяем нужно ли перенаправить вывод
        if (output_fd != STDOUT_FILENO) { //если output_fd не равен STDOUT_FILENO, значит нужно изменить текущий вывод дочернего процесса
            dup2(output_fd, STDOUT_FILENO);//дублируем output_fd в стандартный вывод (STDOUT_FILENO). Когда дочерний процесс записывает в стандартный вывод, он будет записывать в output_fd
            close(output_fd); //после дублирования удяляем ненужный оригинальный файловый дескриптор
        }

        execvp(command, arguments); //заменяем этот процесс другим, запуская исполняемый файл с указанными аргументами.
        perror("Error executing command"); //если execlp() завершилась с ошибкой, выводится сообщение об ошибке и завершается выполнение программы
        exit(EXIT_FAILURE);
    }
    else {
        //родительский процесс
        int status; //тут храним статус о выполнении команды в дочернем процессе
        waitpid(pid, &status, 0); //ждем, когда завершится дочерний процесс. Статус завершения будет храниться в переменной status

        if (WIFEXITED(status)!=0) { //проверяем, завершился ли дочерний процесс нормально
            printf("Command executed successfully. Exit code: %d \n", WEXITSTATUS(status));
        }
        else {
            printf("Command terminated with an error. \n");
        }
    }
}

int main() {
    char input[len];

    while (1) {
        //вывод приглашения командной строки
        printf("Enter a command: ");
        fflush(stdout);

        //читаем команду, будет сохранена команда в input,
        // размер = sizeof(input), читаться команда будет из стандартного ввода. Возвращается указатель на буфер
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        //удаляем символ новой строки из ввода
        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        } else if (input[0] == '\n') {
            input[0] = '\0';
        }

        //если введено exit, то выходим из терминала
        if (strcmp(input, "exit") == 0) {
            break;
        }


        char *commands[len]; //тут храним все команды от '|' до '|'
        int command_count = 0; //тут храним количество команд, которые от от '|' до '|'


        //проверяем наличие оператора "|"
        char *pipe_token = strchr(input, '|');
        if (pipe_token != NULL) {
            //разбиваем введенную строку на команды с использованием "|"
            while (pipe_token != NULL) {
                commands[command_count] = pipe_token;
                ++command_count;
                pipe_token = strtok(NULL, "|");
            }

            int input_fd = STDIN_FILENO; //файловый дескриптор, который определяет, откуда дочерний процесс должен читать ввод

            //обработка каждой команды
            for (int i = 0; i < command_count; ++i) {
                char *command = strtok(commands[i], " "); // берем первую часть строки(первое слово). Она является командой, которую нужно выполнить
                char *arguments[len]; //массив указателей на строки
                int j = 0;

                while (command != NULL) { // будет возвращаться нулевой указатель после strtok до тех пор, пока не закончатся аргументы
                    // strtok возвращает указатель на следующий аргумент
                    arguments[j] = command; //arguments[0] - команда
                    ++j;
                    command = strtok(NULL, " "); //тут уже берем слеующий аргумент
                }
                arguments[j] = NULL; // последний элемент массива = NULL

                int output_fd; //файловый дескриптор, который определяет, куда дочерний процесс должен записывать вывод
                if (i == command_count - 1) {
                    output_fd = STDOUT_FILENO;
                } else {
                    output_fd = -1;
                }

                command_execute(arguments[0], arguments, input_fd, output_fd);

                int pipe_fd[2]; //массив для хранения файловых дескрипторов pipe
                // pipe_fd[0] будем использовать для чтения (read-end), pipe_fd[1] для записи (write-end)

                //создаем новый pipe, если есть следующая команда
                if (i < command_count - 1 && pipe(pipe_fd) == -1) { //если есть команда, но создание pipe заверщается в ошибкой, то выводим ошибку
                    perror("Error creating pipe");
                    exit(EXIT_FAILURE);
                }

                //перенаправляем ввод следующей команде
                if (i < command_count - 1) { //если есть еще команда, то
                    input_fd = pipe_fd[0]; //input_fd, который был направлен на стандартный ввод (STDIN_FILENO), теперь перенаправляется на read-end pipe (pipe_fd[0])
                    //т.е. вывод текущей команды это ввод для следующей команды
                    close(pipe_fd[1]); //write-end pipe (pipe_fd[1]) закрывается, потому что команда больше не будет записывать в нее
                }
            }
        }
        else{
            //одиночная команда
            char *command = strtok(input, " "); //берем первую часть строки(первое слово). Она является командой, которую нужно выполнить
            char *arguments[len]; //массив указателей на строки
            int i = 0;

            while (command != NULL) { //будет возвращаться нулевой указатель после strtok до тех пор, пока не закончатся аргументы
                // strtok возвращает указатель на следующий аргумент
                arguments[i] = command; //arguments[0] - команда
                ++i;
                command = strtok(NULL, " "); //тут уже берем слеующий аргумент
            }
            arguments[i] = NULL; // последний элемент массива = NULL

            command_execute(arguments[0], arguments, STDIN_FILENO, STDOUT_FILENO);
        }
    }

    printf("Program terminated.\n");

    return 0;
}