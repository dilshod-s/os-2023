#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    
    std::cout << "Please, type your command, my comrade \n";
    
    std::string command;
    

    while(true){
        
        std::getline(std::cin, command);

    if(command == "quit"){
        
      exit(0);
    }
    
    std::vector<std::string> args;
    std::istringstream istring(command);
    std::string temp;
    
    while (istring >> temp){
        
        args.push_back(temp);
    }
    
    char *argv[args.size() + 1];
    
    for (size_t i = 0; i < args.size(); i++){
        
        argv[i] = strdup(args[i].c_str());
    }
    
    argv[args.size()] = nullptr;
    
    pid_t pid = fork();
      
      if(pid < 0){
          
          std::cerr << "Process Creation Error!" << std::endl;
          exit(-1);
          
      }else if(pid == 0){
          
            execvp(argv[0], argv);
            std::cerr << "Process Error!" << std::endl;
            exit(-1);
            
      }else{
          
        int status;
        waitpid(pid, &status, 0);
        
        if(!WIFEXITED(status)){
            
            std::cerr << command << " Command Execution Error!"<< std::endl;
        }
        
        for (size_t i = 0; argv[i] != nullptr; ++i){
            free(argv[i]);
        }
      }
    }
}
