#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

std::vector<std::string> splitString(const std::string& input);

int main()
{
    std::string command;
    std::cout << "Type command here or '/q' to exit"  << std::endl;

    while (true)
    {
        std::cout << "$ " << std::flush;
        std::getline(std::cin, command);
        if (command == "/q")
            break;

        // Split the input command into arguments
        std::vector<std::string> args = splitString(command);

        // Convert arguments to argv type
        char** argv = new char*[args.size() + 1];
        for (size_t i = 0; i < args.size(); i++)
            argv[i] = strdup(args[i].c_str());
        argv[args.size()] = nullptr;


        pid_t pid = fork();

        if (pid < 0)
            std::cerr << "Failed to fork a child process" << std::endl;

        // Child process
        if (pid == 0)
        {
            execvp(argv[0], argv);

            std::cerr << "Command not found or failed to execute" << std::endl;
            exit(1);
        }
        // Parent process
        else
        {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status))
                    std::cerr << "Command returned with exit code: " << WEXITSTATUS(status) << std::endl;
            }
            else
                std::cerr << "Command didn't exit normally" << std::endl;

            for (size_t i = 0; argv[i] != nullptr; ++i)
                free(argv[i]);
            delete[] argv;
        }
    }

    return 0;
}


std::vector<std::string> splitString(const std::string& input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token)
        tokens.push_back(token);

    return tokens;
}
