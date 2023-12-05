#include <iostream>
#include <string>
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

    pid_t pid = fork();
      
      if(pid < 0){
          
          std::cerr << "Process Creation Error!" << std::endl;
          exit(-1);
          
      }else if(pid == 0){
          
            execlp("/bin/sh", "/sh" , "-c", command.c_str(), (char*)NULL);
            std::cerr << "Process Error!" << std::endl;
            exit(-1);
            
      }else{
          
        int status;
        waitpid(pid, &status, 0);
        
        if(!WIFEXITED(status)){
            
            std::cerr << command << " Command Execution Error!"<< std::endl;
        }
      }
    }
}