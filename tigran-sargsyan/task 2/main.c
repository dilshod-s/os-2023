#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "wordcount.h"

void usage() {
    printf("Usage: wordcount [-w] [-l] [file]\n");
}

int main(int argc, char *argv[]) {
    int opt, fd;
    Counters cnt = {0, 0};
    int count_words = 0, count_lines = 0;
    while ((opt = getopt(argc, argv, "wl")) != -1) {
        switch (opt) {
            case 'w':
                count_words = 1;
                break;
            case 'l':
                count_lines = 1;
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }
    if (count_words == 0 && count_lines == 0) {
        count_words = 1;
        count_lines = 1;
    }
    if (optind < argc) {
        if ((fd = open(argv[optind], O_RDONLY)) == -1) {
            perror(argv[optind]);
            exit(EXIT_FAILURE);
        }
        if (count_words) {
            cnt = count_words(fd);
            printf("%d ", cnt.words);
        }
        if (count_lines) {
            cnt = count_lines(fd);
            printf("%d ", cnt.lines);
        }
        close(fd);
    } else {
        cnt = count_words(STDIN_FILENO);
        if (count_words) {
            printf("%d ", cnt.words);
        }
        if (count_lines) {
            cnt = count_lines(STDIN_FILENO);
            printf("%d ", cnt.lines);
        }
    }
    printf("\n");
    return 0;
}
