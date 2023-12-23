#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int main() {

  std::cout << "Type your command \n";

  while (1) {
    std::cout << "$ ";
    std::string str;

    std::getline(std::cin, str);
    if (str.size() == 0)
      continue;
    else if (str == "quit")
      return 0;
    std::vector<std::string> args;
    std::istringstream istring(str);
    std::string temp;
    while (istring >> temp)
      args.push_back(temp);
    int pipe_count = std::count(args.begin(), args.end(), "|");

    if (pipe_count) {
      pipe_count++;
      std::vector<std::string> pipe_args;
      int i = 0;
      auto it = args.begin();
      int input_fd = STDIN_FILENO;
      while (i < pipe_count) {
        std::string input_file;
        std::string output_file;
        while (it != args.end() && *it != "|") {
          pipe_args.push_back(*it);
          it++;
        }
        char *args_array[pipe_args.size() + 1];
        std::size_t j;
        for (j = 0; j < pipe_args.size(); ++j) {
          if (pipe_args[j] == "<" || pipe_args[j] == ">") {
            break;
          }
          args_array[j] = strdup(pipe_args[j].c_str());
        }
        args_array[j] = nullptr;

        int pipe_fd[2];
        if (i < pipe_count && pipe(pipe_fd) == -1) {
          std::cerr << "Error creating pipe" << std::endl;
          exit(EXIT_FAILURE);
        }
        int output_fd = STDOUT_FILENO;
        auto it2 = std::find(pipe_args.begin(), pipe_args.end(), "<");
        if (it2 != pipe_args.end())
          input_file = *(it2 + 1);

        it2 = std::find(pipe_args.begin(), pipe_args.end(), ">");
        if (i < pipe_count - 1)
          output_fd = pipe_fd[1];
        else
          output_fd = STDOUT_FILENO;

        if (it2 != pipe_args.end())
          output_file = *(it2 + 1);

        pid_t pid = fork();
        if (pid < 0) {
          std::cerr << "Error creating child process" << std::endl;
          exit(EXIT_FAILURE);
        } else if (pid == 0) {

          if (output_file.size() != 0) {
            int output_file_fd =
                open(output_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_file_fd == -1) {
              std::cerr << "Error opening output file" << std::endl;
              exit(EXIT_FAILURE);
            }
            dup2(output_file_fd, STDOUT_FILENO);
            close(output_file_fd);
          }

          else if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
          }

          if (input_file.size() != 0) {
            int input_file_fd = open(input_file.c_str(), O_RDONLY);
            if (input_file_fd == -1) {
              std::cerr << "Error opening input file" << std::endl;
              exit(EXIT_FAILURE);
            }
            dup2(input_file_fd, STDIN_FILENO);
            close(input_file_fd);
          } else if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
          }

          execvp(args_array[0], args_array);
          std::cerr << "Error executing command" << std::endl;
          exit(EXIT_FAILURE);
        } else {
          int status;
          waitpid(pid, &status, 0);
          if (WIFEXITED(status) != 0) {
            std::cout << "Command executed successfully. Exit code:  \n"
                      << WEXITSTATUS(status) << std::endl;
          } else {
            std::cout << "Command terminated with an error. \n";
          }
          if (i < pipe_count - 1) {
            input_fd = pipe_fd[0];
            close(pipe_fd[1]);
          }
          for (std::size_t z = 0; z < j; ++z)
            free(args_array[z]);
          pipe_args.clear();
          it++;
          i++;
        }
      }
    }
    if (pipe_count == 0) {
      auto it = std::find(args.begin(), args.end(), "<");
      if (it != args.end()) {
        std::cout << "input file" << std::endl;
        ++it;
        std::string file = *it;
        it--;
        const char *cstr = file.c_str();
        int fd = open(cstr, O_RDONLY);
        if (fd == -1) {
          std::cout << "File does not exist" << std::endl;
          exit(1);
        }
        dup2(fd, 0);
        close(fd);
      }

      it = std::find(args.begin(), args.end(), ">");
      if (it != args.end()) {
        std::cout << "output file" << std::endl;
        ++it;
        std::string file = *it;
        it--;
        const char *cstr = file.c_str();
        int fd = open(cstr, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd == -1) {
          std::cout << "File does not exist" << std::endl;
          exit(1);
        }
        dup2(fd, 1);
        close(fd);
      }
      char *argv[args.size() + 1];
      std::size_t i;
      for (i = 0; i < args.size(); i++) {
        if (args[i] == "<" || args[i] == ">") {
          break;
        }
        argv[i] = strdup(args[i].c_str());
      }
      argv[i] = nullptr;
      pid_t pid = fork();

      if (pid < 0)
        std::cerr << "fork error" << std::endl;
      else if (pid == 0) {
        execvp(argv[0], argv);
        std::cerr << "command didn't exist \n";
        exit(1);
      } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
          std::cout << "Command executed successfully. Exit code: "
                    << WEXITSTATUS(status) << std::endl;
        } else {
          std::cout << "Command terminated with an error. \n";
        }
        for (size_t j = 0; j < i; ++j)
          free(argv[j]);
      }
    }
  }
  return 0;
}
