#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
    char input[500];

    while (1) {
        printf("$ ");
        fflush(stdout);

        ssize_t bytesRead = read(0, input, sizeof(input));

        if (bytesRead == -1) {
            perror("Error reading input");
            exit(1);
        }

        input[bytesRead - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Error creating process");
            exit(1);
        } else if (pid == 0) {
            execlp("/bin/sh", "/bin/sh", "-c", input, (char *)NULL);

            perror("Error executing command");
            exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) == 0) {
                printf("Command terminated with an error. \n");
            }
        }
    }

    return 0;
}
