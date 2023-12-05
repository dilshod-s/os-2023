#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
   	std::string input;  
	while(true){
		std::cout << "$: ";
		std::getline(std::cin, input);

		if(input == "exit"){
			break;
		}

		pid_t pid = fork();

		if(pid == -1){
			 std::cerr << "Error creating process." << std::endl;
			 exit(1);
		}
		else if(pid == 0){
			execlp("/bin/sh", "sh", "-c", input.c_str(), (char *)NULL);

			std::cerr << "Error executing command." << std::endl;
			exit(1);
		}
		else{
			int status;
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status)) {
				std::cerr << "Command returned with error." << std::endl;
			}
		    
		}    
	} 
    
    return 0;   
}
