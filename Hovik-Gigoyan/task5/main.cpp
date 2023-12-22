#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

std::vector<char*> parseCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<char*> args;
    std::string arg;

    while (iss >> arg) {
        char* cstr = new char[arg.length() + 1];
        strcpy(cstr, arg.c_str());
        args.push_back(cstr);
    }
    args.push_back(nullptr);

    return args;
}

int main() {
    std::string command;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);

        if (command.empty()) continue;

        if (command == "exit") {
            break;
        }

        std::vector<char*> args = parseCommand(command);

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            execvp(args[0], args.data());
            std::cerr << "Error executing " << args[0] << std::endl;
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, nullptr, 0);
        }

        for (char* arg : args) {
            delete[] arg;
        }
    }

    return 0;
}
