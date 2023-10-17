#include <stdio.h>
#include <getopt.h>
#include "wordcount.h"

int main(int argc, char *argv[]) {
    int opt;
    int countWords = 0;
    int countLines = 0;

    while ((opt = getopt(argc, argv, "wl")) != -1) {
        switch (opt) {
            case 'w':
                countWords = 1;
                break;
            case 'l':
                countLines = 1;
                break;
        }
    }

    if (optind < argc) {
        while (optind < argc) {
            if (countWords && countLines) {
                printf("File: %s\nWords: %d\nLines: %d\n", argv[optind], WordCounter::countWordsFromFile(argv[optind]), WordCounter::countLinesFromFile(argv[optind]));
            } else if (countWords) {
                printf("File: %s\nWords: %d\n", argv[optind], WordCounter::countWordsFromFile(argv[optind]));
            } else if (countLines) {
                printf("File: %s\nLines: %d\n", argv[optind], WordCounter::countLinesFromFile(argv[optind]));
            }
            optind++;
        }
    } else {
        if (countWords && countLines) {
            printf("Words: %d\nLines: %d\n", WordCounter::countWordsFromInput(), WordCounter::countLinesFromInput());
        } else if (countWords) {
            printf("Words: %d\n", WordCounter::countWordsFromInput());
        } else if (countLines) {
            printf("Lines: %d\n", WordCounter::countLinesFromInput());
        }
    }

    return 0;
}
