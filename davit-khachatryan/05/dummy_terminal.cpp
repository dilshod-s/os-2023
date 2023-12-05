/*
    The code is written using SOLID prinviple to provide more flexibility and to facilitate further development.
    I also used `doxygen` comments to give the user and reviewer a better understanding of what the code does and how it works.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stdexcept>

/**
 * @brief Class responsible for parsing commands into argument vectors.
 */
class CommandParser
{
public:
    /**
     * @brief Parses the input command into individual arguments.
     * @param command The command string to be parsed.
     * @return A vector containing individual command arguments.
     */
    static std::vector<std::string> parse(const std::string &command)
    {
        std::istringstream iss(command);
        std::vector<std::string> args;
        std::string arg;
        while (iss >> arg)
        {
            args.push_back(arg);
        }
        return args;
    }
};

/**
 * @brief Class responsible for executing processes using parsed arguments.
 */
class ProcessExecutor
{
public:
    /**
     * @brief Executes a process using the provided arguments.
     * @param args A vector containing command arguments.
     * @throws std::runtime_error if 'execvp' fails to execute the command.
     */
    static void execute(const std::vector<std::string> &args)
    {
        char *argv[args.size() + 1];
        for (size_t i = 0; i < args.size(); ++i)
        {
            argv[i] = const_cast<char *>(args[i].c_str());
        }
        argv[args.size()] = nullptr;

        execvp(argv[0], argv);

        // If execvp() returns, an error occurred
        perror("execvp");
        throw std::runtime_error("Failed to execute command");
    }
};

/**
 * @brief Class representing a basic command shell.
 */
class CommandShell
{
public:
    /**
     * @brief Initiates the command shell and handles command execution.
     */
    static void start()
    {
        std::string command;

        while (true)
        {
            std::cout << "$ ";
            std::getline(std::cin, command);

            if (command == "exit" || command == "quit")
            {
                break;
            }

            try
            {
                std::vector<std::string> args = CommandParser::parse(command);

                // Forking process
                pid_t pid = fork();

                if (pid == 0)
                {
                    // Child process
                    ProcessExecutor::execute(args);
                    return; // In case executeCommand() fails
                }
                else if (pid > 0)
                {
                    // Parent process
                    int status;
                    waitpid(pid, &status, 0); // Wait for the child process to finish
                }
                else
                {
                    // Error forking
                    perror("fork");
                    return;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
};

int main()
{
    CommandShell::start();

    return 0;
}
