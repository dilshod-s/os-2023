#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define len 200

int main() {
    char input[len];

    while (1) {
        printf("Enter a command: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if(strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
            input[strlen(input) - 1] = '\0';
        }
        else if(input[0] == '\n'){
            input[0] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        char *arguments[len];
        int i = 0;
        char *command = strtok(input, " ");
        while (command != NULL) {
            arguments[i] = command;
            ++i;
            command = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        if (pid == -1) {
            perror("Error creating process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            execvp(arguments[0], arguments);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
        else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)!=0) {
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
