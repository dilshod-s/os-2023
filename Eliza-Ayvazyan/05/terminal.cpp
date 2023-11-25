#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

void executeCommand (const std::string& command) {
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Fork failed" << std::endl;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execlp("/bin/sh", "sh", "-c", command.c_str(), NULL);
        std::cerr << "Command not found" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            std::cerr << "Command failed" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    std::string input;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "/q") {
            break;
        }
        executeCommand(input);
    }
    return 0;
}
