#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int Wordcount(int fd) {
    int wordcount = 0;
    int symb = 0;
    char ch;
    ssize_t bytes_read;
    while ((bytes_read = read(fd, &ch, sizeof(char))) > 0) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            symb = 0;
        } else if (!symb) {
            wordcount++;
            symb = 1;
        }
    }
    return wordcount;
}

int Linecount(int fd) {
    int linecount = 0;
    char ch;
    ssize_t bytes_read;
    while ((bytes_read = read(fd, &ch, 1)) > 0) {
        if (ch == '\n') {
            linecount++;
        }
    }
    return linecount;
}
