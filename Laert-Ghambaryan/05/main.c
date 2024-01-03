#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void executeCommand(char** args) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error in fork()\n");
    }
    /// Код, выполняемый в дочернем процессе
    else if (pid == 0) {
        /// Замена текущего образа процесса новым (выполнение команды)
        execvp(args[0], args);
        perror("Error in execvp()\n");
        return;
    }
    /// Код, выполняемый в родительском процессе
    else {
        int status;
        waitpid(pid, &status, 0);

        /// Обработка статуса завершения дочернего процесса
        if (!WIFEXITED(status)){
            perror("Дочерний процесс завершился не нормально\n");
            
        }
    }
}


int main() {
    while (1) {
        printf("$ ");
        
        char input[1024];
        fgets(input, sizeof(input), stdin);

        char* args[64];
        int argc = 0;

        char* token = strtok(input, " \n");

        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " \n");
        }

        args[argc] = NULL;

        if (argc > 0) {
            executeCommand(args);
        }
    }

    return 0;
}
