#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#define len 200

int main() {
    char input[len];

    while (true) {
        std::cout << "Enter a command: ";
        std::cout.flush();

        if (std::cin.getline(input, sizeof(input)).eof()) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        } else if (input[0] == '\n') {
            input[0] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        char* arguments[len];
        int i = 0;
        char* command = strtok(input, " ");
        while (command != NULL) {
            arguments[i] = command;
            ++i;
            command = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        if (pid == -1) {
            perror("Error creating process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(arguments[0], arguments);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) != 0) {
                std::cout << "Command executed successfully. Exit code: " << WEXITSTATUS(status) << std::endl;
            } else {
                std::cout << "Command terminated with an error." << std::endl;
            }
        }
    }

    std::cout << "Program terminated." << std::endl;

    return 0;
}

