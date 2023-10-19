#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int count_lines_in_file(int fd) {
    char buffer[BUFFER_SIZE];
    int lines = 0;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                lines++;
            }
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return lines;
}

int count_words_in_file(int fd) {
    char buffer[BUFFER_SIZE];
    int words = 0;
    int in_word = 0;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE) > 0)) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                in_word = 0;
            } else if (in_word == 0) {
                in_word = 1;
                words++;
            }
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return words;
}

