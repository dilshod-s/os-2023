#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include "wordcount.h"
int main(int argc,char* argv[]){
    bool countline = false;
    bool countword= false;

    for(int i = 1;i<argc;++i){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'l'){
                countline= true;
            }
            else if(argv[i][1] == 'w'){
                countword= true;
            }
        }
    }
    int fd = open(argv[argc-1],O_RDONLY);

    if(fd == -1) {
        printf("Error\n");
    }
     else if(countline){
        printf("%d\n",countLines(fd));
    }
     else if(countword){
        printf("%d\n",countWords(fd));
    }    
    
}