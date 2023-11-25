#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/wait.h>
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
    char *argv[args.size() + 1];
    for (size_t i = 0; i < args.size(); i++)
      argv[i] = strdup(args[i].c_str());
    argv[args.size()] = nullptr;
    pid_t pid = fork();

    if (pid < 0)
      std::cerr << "fork error" << std::endl;
    else if (pid == 0) {
      execvp(argv[0], argv);

      std::cerr << "command didn't exist \n";
      exit(1);
    } else if (pid > 0) {
      int status;
      waitpid(pid, &status, 0);

      if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if (exit_code)
          std::cerr << "returned exit code: " << exit_code << '\n';
      }
      for (size_t i = 0; argv[i] != nullptr; ++i)
        free(argv[i]);
    }
  }

  return 0;
}
