#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define len 200

int main() {
    char input[len];

    while (1) {
        
        // Вывод приглашения для ввода команды
        printf("Waiting for a command: ");
        fflush(stdout);

        // Считывание команды из стандартного ввода
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Обработка символа новой строки в конце строки
        if(strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] = '\0';
        }
        // Обработка строки, состоящей только из символа новой строки
        else if(input[0] == '\n'){
            input[0] = '\0';
        }

        // Проверка на команду "exit" для завершения программы
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Создание нового процесса для выполнения команды
        pid_t pid = fork(); 

        // Массив аргументов для передачи в функцию execvp
        char *arguments[len]; 
        int i = 0;
        // Разбиение введенной строки на отдельные аргументы
        char *command = strtok(input, " "); 
        
        while (command != NULL) 
        {
            // Заполнение массива аргументов
            arguments[i] = command; 
            ++i;
            command = strtok(NULL, " "); 
        }
        // Установка последнего элемента массива в NULL для execvp
        arguments[i] = NULL; 

        if (pid == -1) {
            // Обработка ошибки при создании процесса
            perror("Error creating process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // Код, выполняемый дочерним процессом
            //заменяем этот процесс другим, запуская исполняемый файл с указанными аргументами.
            execvp(arguments[0], arguments); 
            // Если execvp завершилась с ошибкой
            perror("Error executing command"); 
            exit(EXIT_FAILURE);
        }
        else {
            // Код, выполняемый родительским процессом
            int status; 
            // Ожидание завершения дочернего процесса
            waitpid(pid, &status, 0); 

            // Проверка статуса завершения дочернего процесса
            if (WIFEXITED(status) != 0) {
                // Вывод сообщения об успешном выполнении
                printf("Command executed successfully. Exit code: %d \n", WEXITSTATUS(status));
            }
            else {
                // Вывод сообщения об ошибке в случае неудачного завершения
                printf("Command terminated with an error. \n");
            }
        }
    }

    // Сообщение о завершении программы
    printf("Program terminated.\n");

    return 0;
}

