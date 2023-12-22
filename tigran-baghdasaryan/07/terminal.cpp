#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define len 200

void command_execute(char *command, char **arguments, int input_fd, int output_fd, char *input_file, char *output_file) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error creating process");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        } else if (input_file != nullptr) {
            int input_file_fd = open(input_file, O_RDONLY);
            if (input_file_fd == -1) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            dup2(input_file_fd, STDIN_FILENO);
            close(input_file_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        } else if (output_file != nullptr) {
            int output_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (output_file_fd == -1) {
                perror("Error");
                exit(EXIT_FAILURE);
            }
            dup2(output_file_fd, STDOUT_FILENO);
            close(output_file_fd);
        }

        execvp(command, arguments);
        perror("Error");
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

int main() {
    char input[len];

    while (true) {
        std::cout << "Enter a command: ";
        std::cout.flush();

        if (fgets(input, sizeof(input), stdin) == nullptr) {
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

        char *commands[len];
        int command_count = 0;

        char input_copy[len];
        strcpy(input_copy, input);
        char *pipe_token = strtok(input_copy, "|");

        if (pipe_token != nullptr) {
            while (pipe_token != nullptr) {
                commands[command_count] = pipe_token;
                ++command_count;
                pipe_token = strtok(nullptr, "|");
            }

            int input_fd = STDIN_FILENO;

            for (int i = 0; i < command_count; ++i) {
                char *command = strtok(commands[i], " ");
                char *arguments[len];
                int j = 0;

                while (command != nullptr) {
                    arguments[j] = command;
                    ++j;
                    command = strtok(nullptr, " ");
                }
                arguments[j] = nullptr;

                int pipe_fd[2];
                if (i < command_count - 1 && pipe(pipe_fd) == -1) {
                    perror("Error creating pipe");
                    exit(EXIT_FAILURE);
                }

                int output_fd;
                if (i == command_count - 1) {
                    output_fd = STDOUT_FILENO;
                } else {
                    output_fd = pipe_fd[1];
                }

                command_execute(arguments[0], arguments, input_fd, output_fd, nullptr, nullptr);

                if (i < command_count - 1) {
                    input_fd = pipe_fd[0];
                    close(pipe_fd[1]);
                }
            }
        } else {
            char *command = strtok(input, " ");
            char *arguments[len];
            int i = 0;

            while (command != nullptr) {
                arguments[i] = command;
                ++i;
                command = strtok(nullptr, " ");
            }
            arguments[i] = nullptr;

            command_execute(arguments[0], arguments, STDIN_FILENO, STDOUT_FILENO, nullptr, nullptr);
        }
    }

    std::cout << "Program closed." << std::endl;

    return 0;
}

