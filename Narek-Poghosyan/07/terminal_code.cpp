#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LEN 200

void execute_command(char *command, char **arguments, int input_fd, int output_fd, char *input_file, char *output_file) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process

        // Input redirection
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        } else if (input_file != NULL) {
            int input_file_fd = open(input_file, O_RDONLY);
            if (input_file_fd == -1) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            dup2(input_file_fd, STDIN_FILENO);
            close(input_file_fd);
        }

        // Output redirection
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        } else if (output_file != NULL) {
            int output_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (output_file_fd == -1) {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
            dup2(output_file_fd, STDOUT_FILENO);
            close(output_file_fd);
        }

        execvp(command, arguments);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) != 0) {
            printf("Command executed successfully. Exit code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Command terminated with an error.\n");
        }
    }
}

int main() {
    char input[MAX_LEN];

    while (1) {
        printf("Enter a command: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        // Remove newline character from input
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        } else if (input[0] == '\n') {
            input[0] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        char *commands[MAX_LEN];
        int command_count = 0;

        char input_copy[MAX_LEN];
        strcpy(input_copy, input);
        char *pipe_token = strtok(input_copy, "|");

        if (pipe_token != NULL) {
            while (pipe_token != NULL) {
                commands[command_count] = pipe_token;
                ++command_count;
                pipe_token = strtok(NULL, "|");
            }

            int input_fd = STDIN_FILENO;

            for (int i = 0; i < command_count; ++i) {
                char *command = strtok(commands[i], " ");
                char *arguments[MAX_LEN];
                int j = 0;

                while (command != NULL) {
                    arguments[j] = command;
                    ++j;
                    command = strtok(NULL, " ");
                }
                arguments[j] = NULL;

                int pipe_fd[2];
                if (i < command_count - 1 && pipe(pipe_fd) == -1) {
                    perror("Error creating pipe");
                    exit(EXIT_FAILURE);
                }

                int output_fd = (i == command_count - 1) ? STDOUT_FILENO : pipe_fd[1];

                execute_command(arguments[0], arguments, input_fd, output_fd, NULL, NULL);

                if (i < command_count - 1) {
                    input_fd = pipe_fd[0];
                    close(pipe_fd[1]);
                }
            }
        } else {
            // Single command
            char *command = strtok(input, " ");
            char *arguments[MAX_LEN];
            int i = 0;

            while (command != NULL) {
                arguments[i] = command;
                ++i;
                command = strtok(NULL, " ");
            }
            arguments[i] = NULL;

            execute_command(arguments[0], arguments, STDIN_FILENO, STDOUT_FILENO, NULL, NULL);
        }
    }

    printf("Program terminated.\n");

    return 0;
}
