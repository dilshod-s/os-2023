#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
   std::string input;  
    while(true){
    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    if(input == "exit"){
        break;
    }

    pid_t pid = fork();//Создаем новый процесс

    if(pid == -1){
         std::cerr << "Ошибка при создании процесса." << std::endl;
         exit(EXIT_FAILURE);
    }
    else if(pid == 0){//код в дочернем процессе
        execlp("/bin/sh", "sh", "-c", input.c_str(), (char *)NULL);//тут если системный вызов дает ошибку, то он идет ниже и уже печатает ошибку, ну а если не выдает ошибку то уже дальше не идет
        std::cerr << "Ошибка при выполнении команды." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{//код в родительском процессе
        int status;
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
               std::cerr << "Команда '" << input << "' завершилась с ошибкой." << std::endl;
            }
            
    }    
    } 
    
    return 0;   
}