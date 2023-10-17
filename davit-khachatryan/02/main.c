#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "wordcount.h"

int main(int argc, char *argv[]) {
    int opt;
    int fd;
    int line_count = 0;
    int word_count = 0;
    int use_lines = 0;
    int use_words = 0;
    int use_file = 0;

    while ((opt = getopt(argc, argv, "lw")) != -1) {
        switch (opt) {
            case 'l':
                use_lines = 1;
                break;
            case 'w':
                use_words = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-w] [file]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        use_file = 1;
        fd = open(argv[optind], O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    if (!use_lines && !use_words) {
        use_lines = 1;
        use_words = 1;
    }

    if (use_lines) {
        line_count = count_lines(fd);
        printf("Lines: %d\n", line_count);
    }
    if (use_words) {
        word_count = count_words(fd);
        printf("Words: %d\n", word_count);
    }

    if (use_file) {
        close(fd);
    }

    return 0;
}
