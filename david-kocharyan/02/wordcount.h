#ifndef WORDCOUNT_WORDCOUNT_H
#define WORDCOUNT_WORDCOUNT_H


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>

class WordCount
{
private:
    std::string fileName;
    int wordCount;
    int lineCount;

    bool countWords;
    bool countLines;
    bool inputType;
    bool isFileTxt(const char* name);
    bool isFlag(const char* str);

    void countFromFile();
    void countFromInput();

public:
    WordCount();

    int handleArguments(int argc, char* argv[]);
    void startCounting();
    void printResults() const;

};


#endif