#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::string userInput;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") {
            break;
        }

        std::istringstream inputStringStream(userInput);
        std::vector<std::string> userCommands;
        std::string command;
        
        while (inputStringStream >> command) {
            userCommands.push_back(command);
        }

        char* commandArgs[userCommands.size() + 1];
        for (size_t i = 0; i < userCommands.size(); ++i) {
            commandArgs[i] = const_cast<char*>(userCommands[i].c_str());
        }
        commandArgs[userCommands.size()] = nullptr;

        pid_t processId = fork();

        if (processId == 0) {
            execvp(commandArgs[0], commandArgs);
            perror("Error executing command...");
            return 1;
        } else if (processId > 0) {
            int status;
            waitpid(processId, &status, 0);
        } else {
            perror("Fork error...");
            return 1;
        }
    }

    return 0;
}
