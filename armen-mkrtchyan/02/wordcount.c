#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //simvolicheskie constanti
#include <stdbool.h> //dlya bulleanov

unsigned count_words(int fd){
    
    unsigned words = 0;
    bool inword = false;
    char buffer[1024];
    int read_status;

    while(read_status = read(fd, buffer, 1) > 0){
        
        for(int i = 0; i < read_status; ++i){
             
            if(buffer[i] == ' '|| buffer[i] == '\n' || buffer[i] == '\t'){
                
                inword = false;                
            }
            else if(!inword){
                
                inword = true;
                ++words;
            }     
        } 
        
        
    }
    return words;
}

unsigned count_lines(int fd){
    
    unsigned lines = 1;
    char buffer[1024];
    int read_status; 
    
    while(read_status = read(fd, buffer, 1) > 0){
        
        for(int i = 0; i < read_status; ++i){
            
            if(buffer[i] == '\n'){
                
                ++lines;
            }  
        }      
    }
    
    return lines;
}
