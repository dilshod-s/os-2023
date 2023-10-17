#include "wordcount.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "%s: argument should be passed\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    int fd = 0;

    if (argc == 3)
    {
        fd = open(argv[2], O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "%s: error opening file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    

    if (strcmp(argv[1], "-l") == 0)
    {
        int linecount = Linecount(fd);
        if (linecount >= 0) {
            printf("Lines: %d\n", linecount);
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(argv[1], "-w" )== 0)
    {
        int wordcount = Wordcount(fd);
        if (wordcount >= 0) {
            printf("Words: %d\n", wordcount);
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "%s: invalid argument passed\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    

    if (argc == 3)
        close(fd);
}
