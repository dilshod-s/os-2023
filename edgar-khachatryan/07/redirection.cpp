#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

std::vector<std::string> splitString(const std::string& input);

int main()
{
    std::string command;
    std::cout << "Type command here or '/q' to exit"  << std::endl;

    while (true)
    {
        std::cout << "$ " << std::flush;
        std::getline(std::cin, command);
        if (command == "/q") {
            break;
        }

        bool inputRedirection = false, outputRedirection = false;
        std::string readFrom{}, writeTo{};

        // Split the input command into arguments
        std::vector<std::string> args = splitString(command);
        std::queue<char**> q;

        // Convert arguments to argv type
        char*** argv = new char**[args.size() + 1];

        int argument_id = 0, command_id = 0;
        argv[command_id] = new char*[args.size() + 1];
        for (size_t i = 0; i < args.size(); i++, argument_id++)
        {
            if (args[i] == "<")
            {
                inputRedirection = true;
                std::string tmp(args[i + 1]);
                ++i;
                readFrom = tmp;
            }
            else if (args[i] == ">")
            {
                outputRedirection = true;
                std::string tmp(args[i + 1]);
                ++i;
                writeTo = tmp;
            }
            else if (args[i] == "|")
            {
                argv[command_id][argument_id] = nullptr;
                q.push(argv[command_id]);
                argument_id = -1;
                ++command_id;
                argv[command_id] = new char*[args.size() + 1];
            }
            else
                argv[command_id][argument_id] = strdup(args[i].c_str());
        }

        argv[command_id][argument_id] = nullptr;
        q.push(argv[command_id]);



        auto qsize = q.size();
        for (unsigned long i = 0; i < qsize; ++i)
        {
            int fd = open("out.txt", O_RDWR | O_CREAT, 0644);
            int terminal_in = dup(0);
            if (i != 0)
                dup2(fd, 0);
            else if (inputRedirection)
            {
                fd = open(readFrom.c_str(), O_RDWR | O_CREAT, 0644);
                dup2(fd, 0);
            }

            int fd2 = open("out2.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
            int terminal_out = dup(1);
            if (i != qsize - 1)
                dup2(fd2, 1);
            else if (outputRedirection)
            {
                fd2 = open(writeTo.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
                dup2(fd2, 1);
            }

            pid_t pid = fork();

            if (pid < 0)
                std::cerr << "Failed to fork a child process" << std::endl;

            // Child process
            if (pid == 0)
            {
                execvp(q.front()[0], q.front());

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

            }

            std::string line;
            char buffer[4096];

            close(fd2);
            fd2 = open("out2.txt", O_RDWR | O_CREAT, 0644);
            std::ofstream fileStream("out.txt", std::ios::trunc);

            ssize_t bytesRead;
            while ((bytesRead = read(fd2, buffer, sizeof(buffer))) > 0)
                write(fd, buffer, bytesRead);

            close(fd);
            dup2(terminal_in, 0);
            dup2(terminal_out, 1);

            q.pop();
        }

//        for (size_t p = 0; p < args.size() + 1; ++p)
//        {
//            for (size_t c = 0; c < args.size() + 1; ++c)
//            {
//                if (argv[p][c] != nullptr)
//                    delete[] argv[p][c];
//            }
//            delete[] argv[p];
//        }
//        delete[] argv;
    }
    
    std::string argv12[3] = {"rm", "out.txt", "out2.txt"};
    
    char* argv1[] = {(char*)argv12[0].c_str(), (char*)argv12[1].c_str(), nullptr};
    char* argv2[] = {(char*)argv12[0].c_str(), (char*)argv12[2].c_str(), nullptr};

    pid_t pid = fork();

    if (pid == 0)
        execvp(argv1[0], argv1);

    pid = fork();
    if (pid == 0)
        execvp(argv2[0], argv2);


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
