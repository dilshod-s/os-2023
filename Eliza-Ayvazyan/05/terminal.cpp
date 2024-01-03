#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>

const int MAX_INPUT_SIZE = 1024;

void execute_command(const std::string& command) {
    std::istringstream is(command);
    std::string st;
    std::vector<std::string> arg;
    while (is >> st) {
        arg.push_back(st);
    }
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        std::vector<char*> args;
        args.reserve(arg.size() + 1);

        for (size_t i = 0; i < arg.size(); ++i) {
            args.push_back(const_cast<char*>(arg[i].c_str()));
        }

        args.push_back(nullptr);

        execvp(args[0], args.data());
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child process exited with status " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cout << "Child process exited abnormally" << std::endl;
        }
    }
}

int main() {
    std::string input;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);

        if (input == "/q") {
            break;
        }

        execute_command(input);
    }

    return 0;
}

