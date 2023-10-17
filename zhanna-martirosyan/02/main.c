#include <stdio.h>
#include <fcntl.h>
#include "wordcount.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", argv[0]);
        return 1;
    }

    const char *name = argv[1];
    int file_descriptor = open(name, O_RDONLY);

    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    int wordCount = countWords(file_descriptor);
    int lineCount = countLines(file_descriptor);

    printf("%d\n %d\n", wordCount, lineCount);

    close(file_descriptor);
    return 0;
}
