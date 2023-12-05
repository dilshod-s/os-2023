#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            std::istringstream iss(input);
            std::vector<std::string> args;

            
            do {
                std::string arg;
                iss >> arg;
                if (!arg.empty()) {
                    args.push_back(arg);
                }
            } while (iss);

            char **argv = new char *[args.size() + 1];

           
            for (size_t i = 0; i < args.size(); ++i) {
                argv[i] = const_cast<char *>(args[i].c_str());
            }

            
            argv[args.size()] = nullptr;

            // Заменяем текущий процесс новым процессом с использованием execvp
            execvp(argv[0], argv);

            // Если execvp завершилась с ошибкой
            std::cerr << "Ошибка при выполнении команды." << std::endl;
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
