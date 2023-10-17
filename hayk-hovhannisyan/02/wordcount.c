#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
int countWords(int fd){
    int count_words = 0;
    char buff[1024];
    bool inword = false;
    ssize_t   readbytes; 
    while(readbytes = read(fd,buff,1) > 0){
        for(int i = 0;i<readbytes;++i){
            if(buff[i] == ' '|| buff[i] == '\n' || buff[i] == '\t'){
                inword = false;                
            }
            else if(!inword){
                inword = true;
                ++count_words;
            }     
        }      
    }
    return count_words;
}


int countLines(int fd){
    int count_lines = 1;
    char buff[1024];
    int   readbytes; 
    while(readbytes = read(fd,buff,1) > 0){
        for(int i = 0;i<readbytes;++i){
            if(buff[i] == '\n'){
                ++count_lines;
            }  
        }      
    }
    return count_lines;
}
