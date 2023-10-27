#include "wordcount.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-w/-l] <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-w") == 0) {
        printf("Word count: %d\n", count_words(fd));
    } else if (strcmp(argv[1], "-l") == 0) {
        printf("Line count: %d\n", count_lines(fd));
    } else {
        fprintf(stderr, "Invalid option.\n");
    }

    close(fd);
    return 0;
}
