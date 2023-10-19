#include <unistd.h>
#include <stdbool.h>
#include "wordcount.h"
#include <ctype.h>

int countWords(int file_descriptor) {
    char symbol;
    bool proverka = false;
    int wordCount = 0;
    char previous;

    while (read(file_descriptor, &symbol, 1) > 0) {
        if (isalnum(symbol)) {
            proverka = true;
        } else if (proverka && (previous != ' ' || previous != '\n' || previous != '\t')) {
            proverka = false;
            wordCount++;
        }
        previous = symbol;
    }

    if (proverka) {
        wordCount++;
    }

    return wordCount;
}

int countLines(int file_descriptor) {
    char symbol;
    int lineCount = 0;

    lseek(file_descriptor, 0, SEEK_SET);
    while (read(file_descriptor, &symbol, 1) > 0) {
        if (symbol == '\n') {
            lineCount++;
        }
    }

    lseek(file_descriptor, -1, SEEK_END);
    if (read(file_descriptor, &symbol, 1) > 0 && symbol != '\n') {
        lineCount++;
    }
    return lineCount;
}
