#include <unistd.h>
#include <stdbool.h>
#include "wordcount.h"
#include <ctype.h>

#define SPACE ' '
#define NEWLINE '\n'
#define TAB '\t'

int countWords(int file_descriptor) {
    char symbol;
    bool isAlphanumeric = false;
    int wordCount = 0;
    char previous;

    while (read(file_descriptor, &symbol, 1) > 0) {
        isAlphanumeric = isalnum(symbol);
        bool isWhitespace = (previous == SPACE || previous == NEWLINE || previous == TAB);

        if (isAlphanumeric) {
            // Word character encountered
        } else if (isWhitespace && isAlphanumeric) {
            // Word boundary encountered
            wordCount++;
        }
        previous = symbol;
    }

    if (isAlphanumeric) {
        wordCount++;
    }

    return wordCount;
}

int countLines(int file_descriptor) {
    char symbol;
    int lineCount = 0;

    lseek(file_descriptor, 0, SEEK_SET);
    while (read(file_descriptor, &symbol, 1) > 0) {
        bool isNewline = (symbol == NEWLINE);

        if (isNewline) {
            lineCount++;
        }
    }

    lseek(file_descriptor, -1, SEEK_END);
    if (read(file_descriptor, &symbol, 1) > 0 && symbol != NEWLINE) {
        lineCount++;
    }

    return lineCount;
}
