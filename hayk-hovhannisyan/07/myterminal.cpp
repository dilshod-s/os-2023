#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void executeCommand(const std::vector<std::string>& args) {
    char **argv = new char *[args.size() + 1];
    for (size_t i = 0; i < args.size(); ++i) {
        argv[i] = const_cast<char *>(args[i].c_str());
    }
    argv[args.size()] = nullptr;

    execvp(argv[0], argv);

    perror("Ошибка при выполнении команды");
    delete[] argv;
    exit(EXIT_FAILURE);
}

int main() {
    while (true) {
        std::string input;

        std::cout << "Введите команду: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Ошибка при создании процесса." << std::endl;
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            std::istringstream iss(input);
            std::vector<std::string> args;
            std::string token;
            bool pipeFound = false;

            while (iss >> token) {
                if (token == "|") {
                    pipeFound = true;
                    break;  
                }
                args.push_back(token);
            }

            if (pipeFound) {
                std::vector<std::string> argsBeforePipe = args;  

                int pipefd[2];
                if (pipe(pipefd) == -1) {
                    perror("Ошибка при создании пайпа");
                    exit(EXIT_FAILURE);
                }

                pid_t pipeline_pid = fork();
                if (pipeline_pid == -1) {
                    perror("Ошибка при создании процесса для пайплайна");
                    exit(EXIT_FAILURE);
                } else if (pipeline_pid == 0) {
                    close(pipefd[1]);
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);

                    std::vector<std::string> argsAfterPipe;
                    while (iss >> token) {
                        argsAfterPipe.push_back(token);
                    }

                    executeCommand(argsAfterPipe);
                } else {
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);

                    executeCommand(argsBeforePipe); 
                }
            } else {
                executeCommand(args);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                std::cerr << "Команда '" << input << "' завершилась с ошибкой." << std::endl;
            }
        }
    }

    return 0;
}
