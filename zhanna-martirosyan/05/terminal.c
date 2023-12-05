#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define len 200

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
        if(strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] = '\0';
        }
        else if(input[0] == '\n'){
            input[0] = '\0';
        }

        //если введено exit, то выходим из терминала
        if (strcmp(input, "exit") == 0) {
            break;
        }

        pid_t pid = fork(); //создаем новый процесс для выполнения команды

        char *arguments[len]; //массив указателей на строки
        int i = 0;
        char *command = strtok(input, " "); // берем первую часть строки(первое слово). Она является командой, которую нужно выполнить
        while (command != NULL) { //будет возвращаться нулевой указатель после strtok до тех пор, пока не закончатся аргументы
            // strtok возвращает указатель на следующий аргумент
            arguments[i] = command; //arguments[0] - команда
            ++i;
            command = strtok(NULL, " "); //тут уже берем слеующий аргумент
        }
        arguments[i] = NULL; // последний элемент массива = NULL

        if (pid == -1) {
            perror("Error creating process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            //дочерний процесс
            execvp(arguments[0], arguments); //заменяем этот процесс другим, запуская исполняемый файл с указанными аргументами.
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

    printf("Program terminated.\n");

    return 0;
}
