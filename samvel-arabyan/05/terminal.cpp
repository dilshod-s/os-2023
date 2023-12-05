#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
    std::string command;

    while(true){
        std::getline(std::cin, command);

    if(command == "exit"){
      exit(0);
    }

    pid_t pid = fork();
      
      if(pid == -1){
          std::cerr<<"Process Error!"<<std::endl;
          exit(-1);
      }
      else if (pid ==0){
            execlp("/bin/sh", "/sh" , "-c", command.c_str(), (char*)NULL);
            std::cerr<<"Process Error!"<<std::endl;
            exit(-1);
      }
      else{
        int status;
        waitpid(pid, &status, 0);
        if(!WIFEXITED(status)){
std::cerr<<"Error occurred while "<<command<< " command!"<<std::endl;
        }
      }
    }
}