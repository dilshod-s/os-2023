#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

void runCommand(const std::string& command) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Error forking process\n";
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        const char* cmd = command.c_str();
        execl("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        
        std::cerr << "Error executing command\n";
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) == 0) {
            std::cerr << "Command terminated abnormally\n";
        }
    }
}

int main() {
    std::string userInput;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            break;
        }

        runCommand(userInput);
    }

    return 0;
}
