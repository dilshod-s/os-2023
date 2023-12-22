#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

std::vector<std::string> tokenizeInput(const std::string& input);

int main()
{
    std::string userInput;
    std::cout << "Enter '/q' to quit." << std::endl;

    while (true)
    {
        std::cout << "> " << std::flush;
        std::getline(std::cin, userInput);
        if (userInput == "/q")
            break;

        std::vector<std::string> arguments = tokenizeInput(userInput);

        char** argumentArray = new char*[arguments.size() + 1];
        for (size_t i = 0; i < arguments.size(); i++)
            argumentArray[i] = strdup(arguments[i].c_str());
        argumentArray[arguments.size()] = nullptr;

        pid_t processId = fork();

        if (processId < 0)
            std::cerr << "Failed to create a child process." << std::endl;

        if (processId == 0)
        {
            execvp(argumentArray[0], argumentArray);

            std::cerr << "Command not found or failed to execute." << std::endl;
            for (size_t i = 0; argumentArray[i] != nullptr; ++i)
                free(argumentArray[i]);
            delete[] argumentArray;
            exit(1);
        }
        else
        {
            int processStatus;
            waitpid(processId, &processStatus, 0);

            if (WIFEXITED(processStatus))
            {
                if (WEXITSTATUS(processStatus))
                    std::cerr << "Command exited with status code: " << WEXITSTATUS(processStatus) << std::endl;
            }
            else
                std::cerr << "Command did not exit normally." << std::endl;

            for (size_t i = 0; argumentArray[i] != nullptr; ++i)
                free(argumentArray[i]);
            delete[] argumentArray;
        }
    }

    return 0;
}

std::vector<std::string> tokenizeInput(const std::string& input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token)
        tokens.push_back(token);

    return tokens;
}