#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*countLines)(const char* filename);
    int (*countWords)(const char* filename);
    int (*countLinesFromInput)();
    int (*countWordsFromInput)();
} WordCounter;

int countLinesFromFile(const char* filename) {
    int lines = 0;
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    int c;
    int prevChar = '\n';

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lines++;
        }
        prevChar = c;
    }

    fclose(file);
    return lines;
}

int countWordsFromFile(const char* filename) {
    int words = 0;
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("fopen");
        return -1;
    }

    int c;
    int inWord = 0;

    while ((c = fgetc(file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            inWord = 0;
        } else if (!inWord) {
            words++;
            inWord = 1;
        }
    }

    fclose(file);
    return words;
}

int countLinesFromInput() {
    return countLinesFromFile(stdin);
}

int countWordsFromInput() {
    return countWordsFromFile(stdin);
}

#endif
