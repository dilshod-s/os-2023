#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "wordcount.h"
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 3 && argc != 2) {
        fprintf(stderr, "%s\n", argv[0]);
        return 1;
    }

    if(argc == 2){
        const char *option = argv[1];
        if (strcmp(option, "-l") == 0) {
            int file_descriptor = 0;

            int lineCount = countLines(file_descriptor);
            printf("Number of lines: %d\n", lineCount);
        }
        else if (strcmp(option, "-w") == 0) {
            int file_descriptor = 0;

            int wordCount = countWords(file_descriptor);
            printf("Number of words: %d\n", wordCount);
        }
        else{
            fprintf(stderr, "%s\n", argv[0]);
            return 1;
        }
    }
    else if (argc == 3) {
        const char *option = argv[1];
        const char *name = argv[2];

        if (strcmp(option, "-l") == 0) {
            int file_descriptor = open(name, O_RDONLY);

            if (file_descriptor == -1) {
                perror("Error opening file");
                return 1;
            }

            int lineCount = countLines(file_descriptor);
            printf("Number of lines in %s: %d\n", name, lineCount);
            close(file_descriptor);
        }
        else if (strcmp(option, "-w") == 0) {
            int file_descriptor = open(name, O_RDONLY);

            if (file_descriptor == -1) {
                perror("Error opening file");
                return 1;
            }

            int wordCount = countWords(file_descriptor);
            printf("Number of words in %s: %d\n", name, wordCount);
            close(file_descriptor);
        }
        else{
            fprintf(stderr, "%s\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
