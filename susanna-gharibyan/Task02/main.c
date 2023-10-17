#include "wordcount.h" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "%s", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int wordcount = Wordcount(filename);
    if (wordcount >= 0) {
        printf("%s has %d words\n", filename, wordcount);
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }

    int linecount = Linecount(filename);
    if (linecount >= 0) {
        printf("%s has %d lines\n", filename, linecount);
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}
