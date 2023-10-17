#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int Wordcount(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        const char* error_message = "Error: Failed to open file ";
        write(STDERR_FILENO, error_message, strlen(error_message));
        write(STDERR_FILENO, filename, strlen(filename));
        write(STDERR_FILENO, "\n", 1);
        return -1;
    }

    int wordcount = 0;
    int symb = 0;
    char ch;
    ssize_t bytes_read;
    while (bytes_read = read(fd, &ch, sizeof(char)) > 0) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            symb = 0;
        } else if (!symb) {
            wordcount++;
            symb = 1;
        }
    }
    close(fd);
    return wordcount;
}

int Linecount(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        const char* error_message = "Error: Failed to open file ";
        write(STDERR_FILENO, error_message, strlen(error_message));
        write(STDERR_FILENO, filename, strlen(filename));
        write(STDERR_FILENO, "\n", 1);
        return -1;
    }

    int linecount = 0;
    char ch;
    ssize_t bytes_read;
    while ((bytes_read = read(fd, &ch, 1)) > 0) {
        if (ch == '\n') {
            linecount++;
        }
    }
    close(fd);
    return linecount;
}
