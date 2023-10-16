#include "wordcount.h"
#include <iostream>

#include <fcntl.h>
#include <unistd.h>


int WordCounter::countLinesFromFile(const std::string filename) {
    int fileDescriptor = open(filename.c_str(), O_RDONLY);
    if (fileDescriptor == -1) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    int lineCount = 0;
    char buffer[1];
    char prevChar = '\0';

    while (read(fileDescriptor, buffer, 1) > 0) {
        if (buffer[0] == '\n' && prevChar != '\n') {
            lineCount++;
        }
        prevChar = buffer[0];
    }

    close(fileDescriptor);
    return lineCount;
}

int WordCounter::countWordsFromFile(std::string filename) {
    int fileDescriptor = open(filename.c_str(), O_RDONLY);
    if (fileDescriptor == -1) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    int wordCount = 0;
    char buffer[1];
    char prevChar = ' ';

    while (read(fileDescriptor, buffer, 1) > 0) {
        if (isspace(prevChar) && !isspace(buffer[0])) {
            wordCount++;
        }
        prevChar = buffer[0];
    }

    close(fileDescriptor);
    return wordCount;
}

int WordCounter::countLinesFromInput() {
    int lineCount = 0;
    char buffer[1];
    char prevChar = '\0';

    while (read(STDIN_FILENO, buffer, 1) > 0) {
        if (buffer[0] == '\n' && prevChar != '\n') {
            lineCount++;
        }
        prevChar = buffer[0];
    }

    return lineCount;
}

int WordCounter::countWordsFromInput() {
    int wordCount = 0;
    char buffer[1];
    char prevChar = ' ';

    while (read(STDIN_FILENO, buffer, 1) > 0) {
        if (isspace(prevChar) && !isspace(buffer[0])) {
            wordCount++;
        }
        prevChar = buffer[0];
    }

    return wordCount;
}
