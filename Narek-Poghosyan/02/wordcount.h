#ifndef WORDCOUNT_WORDCOUNTER_H
#define WORDCOUNT_WORDCOUNTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>

class WordCounter
{
private:
    std::string fileName;
    int wordCount;
    int lineCount;

    bool countWords;
    bool countLines;

    // false: input, true: file
    bool inputType;

    // Check if the given value is a .txt format filename and get it in data member fileName
    bool isTxtFile(const char* name);
    // Check if given value is a valid flag and update flag according to it
    bool isFlag(const char* str);

    void countFromFile();
    void countFromInput();

public:
    WordCounter();

    int handleArguments(int argc, char* argv[]);
    void startCounting();
    void printResults() const;
};

#endif //WORDCOUNT_WORDCOUNTER_H

