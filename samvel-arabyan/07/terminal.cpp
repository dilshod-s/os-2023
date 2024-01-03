#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    while (true) {
        std::string input;

        std::cout << "Введите команду: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        pid_t pid = fork(); // Создаем новый процесс

        if (pid == -1) {
            std::cerr << "Ошибка при создании процесса." << std::endl;
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Код в дочернем процессе
            // Поддержка перенаправления ввода/вывода и конвейеров
            std::istringstream iss(input);
            std::vector<std::string> args;
            std::string token;

            while (iss >> token) {
                if (token == "<") {
                    // Перенаправление ввода
                    iss >> token;
                    int fd = open(token.c_str(), O_RDONLY);
                    if (fd == -1) {
                        perror("Ошибка при открытии файла для чтения");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                } else if (token == ">") {
                    // Перенаправление вывода
                    iss >> token;
                    int fd = open(token.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    if (fd == -1) {
                        perror("Ошибка при открытии файла для записи");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                } else if (token == "|") {
                    // Пайплайн
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
                        // Код для второй команды в пайплайне
                        close(pipefd[1]); // Закрываем конец для записи
                        dup2(pipefd[0], STDIN_FILENO);
                        close(pipefd[0]);

                        // Выполнение команды
                        // Подготовка аргументов для первой команды
                    char **argv = new char *[args.size() + 1];
                    for (size_t i = 0; i < args.size(); ++i) {
                    // Use c_str() to get a const char* from std::string
                    argv[i] = const_cast<char *>(args[i].c_str());
                    }                   
                    argv[args.size()] = nullptr;

                    // Выполнение первой команды
                        execvp(argv[0], argv);

                        perror("Ошибка при выполнении команды в пайплайне");
                        exit(EXIT_FAILURE);
                    } else {
                        // Код для первой команды в пайплайне
                        close(pipefd[0]); // Закрываем конец для чтения
                        dup2(pipefd[1], STDOUT_FILENO);
                        close(pipefd[1]);

                        // Подготовка аргументов для первой команды
                        char **argv = new char *[args.size() + 1];
                        for (size_t i = 0; i < args.size(); ++i) {
                            argv[i] = const_cast<char *>(args[i].c_str());
                        }
                        argv[args.size()] = nullptr;

                        // Выполнение первой команды
                        execvp(argv[0], argv);
                        perror("Ошибка при выполнении первой команды в пайплайне");
                        delete[] argv;
                        exit(EXIT_FAILURE);
                    }
                } else {
                    // Обычные аргументы команды
                    args.push_back(token);
                }
            }

            // Освобождение выделенной памяти и выполнение команды
            char **argv = new char *[args.size() + 1];
            for (size_t i = 0; i < args.size(); ++i) {
                argv[i] = const_cast<char *>(args[i].c_str());
            }
            argv[args.size()] = nullptr;

            execvp(argv[0], argv);

            // Если execvp завершилась с ошибкой
            perror("Ошибка при выполнении команды");
            delete[] argv; // Освобождаем выделенную память
            exit(EXIT_FAILURE);
        } else { // Код в родительском процессе
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                std::cerr << "Команда '" << input << "' завершилась с ошибкой." << std::endl;
            }
        }
    }

    return 0;
}
