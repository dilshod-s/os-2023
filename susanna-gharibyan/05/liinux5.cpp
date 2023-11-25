#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <algorithm>
#include <sstream> // Include for std::istringstream

int main() {
    std::cout << "Welcome to Susanna's terminal" << std::endl;
    std::string inputcommand;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, inputcommand);

        if (inputcommand == "/q") {
            break;
        }
        std::vector<std::string> args;
        std::istringstream iss(inputcommand);//we create a stringstream 
        std::string arg;

        while (iss >> arg) {
            args.push_back(arg);
        }//Read arguments from the stringstream and store them in vector

        pid_t pid = fork();
      
        if (pid == -1) {//we check if the fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // child process
            std::vector<char*> argv;// Vector to hold char* arguments for execvp
            argv.reserve(args.size() + 1);

            for (size_t i = 0; i < args.size(); ++i) {
                argv.push_back(const_cast<char*>(args[i].c_str()));
              // Convert string arguments to char*
            }
            argv.push_back(nullptr); // Adding a nullptr at the end as expected by argv

            execvp(argv[0], argv.data());
          // Execute the command with arguments using execvp

            // If execvp() returns, an error occurred
            perror("Execvp failed");
            exit(EXIT_FAILURE);
        } else { // parent process
            int status;
            waitpid(pid, &status, 0);// we wait for the child process to finish
            if (WIFEXITED(status)) {
                std::cout << "Child process exited with status " << WEXITSTATUS(status) << std::endl;
            } else {
std::cout << "Terminated by signal: " << WTERMSIG(status) <<std::endl;
            }
        }
    }
    return 0;
}

