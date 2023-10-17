#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "wordcount.h"

int 
main(int argc, char *argv[]) 
{
    int count_lines = 0;
    int count_words = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-l] [-w] [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            count_lines = 1;
        } else if (strcmp(argv[i], "-w") == 0) {
            count_words = 1;
        } else {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            if (count_lines && !count_words) {
                int lines = count_lines_in_file(fd);
                printf("Line count: %d\n", lines);
            } else if (count_words && !count_lines) {
                int words = count_words_in_file(fd);
                printf("Word count: %d\n", words);
            } else {
                fprintf(stderr, "You must specify either -l or -w, but not both.\n");
                exit(EXIT_FAILURE);
            }

            close(fd);
        }
    }

    return 0;
}

