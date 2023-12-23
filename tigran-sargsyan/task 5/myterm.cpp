#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <stdio.h>
#include <string.h>

void exCom(const std::string& com) {
    std::istringstream ist(com);
    std::vector<std::string> args;
    std::string arg;
    while (ist >> arg)
    {
        args.push_back(arg);
    }
    char *command_and_arguments[args.size() + 1];
    for (size_t i = 0; i < args.size(); i++)
    {
        command_and_arguments[i] = strdup(args[i].c_str());
    }
    command_and_arguments[args.size()] = nullptr;
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс - выполняет команду
        execvp(command_and_arguments[0], command_and_arguments);
        // Если execvp вернется, значит произошла ошибка
        std::cerr << "Ошибка выполнения команды\n";
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Родительский процесс - ожидает завершения дочернего
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Ошибка при создании дочернего процесса
        std::cerr << "Ошибка создания процесса\n";
    }
}

int main() {
    std::string input;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);
        if (input == "exit" || input == "quit") {
            break;
        }
        exCom(input);
    }
    return 0;
}
