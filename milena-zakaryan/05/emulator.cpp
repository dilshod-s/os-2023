#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::string command;

    while (true) {
        std::cout << "$-->  ";
        std::getline(std::cin, command);
        if (command == "end") {
            break;
        }

        std::istringstream iss(command);
        std::vector<std::string> arguments;
        std::string argument;
        while (iss >> argument) {
            arguments.push_back(argument);
        }

        char* argv[arguments.size() + 1];
        for (size_t i = 0; i < arguments.size(); ++i) {
            argv[i] = const_cast<char*>(arguments[i].c_str());
        }
        argv[arguments.size()] = nullptr;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(argv[0], argv);
            perror("error...");
            return 1;
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("error...");
            return 1;
        }
    }

    return 0;
}

