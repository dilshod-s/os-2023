#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void runCommand(const std::string& cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Error forking process\n";
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *arguments[64]; 
        int i = 0;
        char *command = strtok((char*)cmd.c_str(), " "); 
        
        while (command != NULL) 
        {
            arguments[i] = command; 
            ++i;
            command = strtok(NULL, " "); 
        }
        arguments[i] = NULL; 
        
        
        execvp(arguments[0], arguments);
        
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
