#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int count_lines(int fd) {
    int lines = 0;
    char buffer;
    int read_status;

    while ((read_status = read(fd, &buffer, 1)) > 0) {
        if (buffer == '\n') {
            lines++;
        }
    }

    if (read_status < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return lines;
}

int count_words(int fd) {
    int words = 0;
    char buffer[4096];

    int read_status;
    int word_started = 0;

    while ((read_status = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < read_status; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                word_started = 0;
            } else if (!word_started) {
                words++;
                word_started = 1;
            }
        }
    }

    if (read_status < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return words;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* filename = argv[1];
    int fd = open(filename, O_RDONLY);

    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int lines = count_lines(fd);
    int words = count_words(fd);

    close(fd);

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);

    return 0;
}
