#include "wordcount.h"
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

int count_words(int fd) {
    char buffer[BUFFER_SIZE];
    int word_count = 0;
    int in_word = 0;
    ssize_t n;

    while ((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            if (isspace(buffer[i])) {
                in_word = 0;
            } else if (!in_word) {
                word_count++;
                in_word = 1;
            }
        }
    }

    if (n < 0) {
        perror("read");
        return -1;
    }

    return word_count;
}


int count_lines(int fd) {
    char buffer[BUFFER_SIZE];
    int line_count = 0;
    ssize_t n;

    while ((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            if (buffer[i] == '\n') {
                line_count++;
            }
        }
    }

    if (n < 0) {
        perror("read");
        return -1;
    }

    return line_count;
}

