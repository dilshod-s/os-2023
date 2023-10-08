#ifndef WORDCOUNT_WORDCOUNT_H
#define WORDCOUNT_WORDCOUNT_H


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>


class WordCount
{
private:
    std::string fileName;
    int wordCount;
    int lineCount;

    bool countWords;
    bool countLines;

    // false: file, true: std input
    bool inputType;

    // check if the given value is a .txt format filename and get it in data member fileName
    bool isFileTxt(const char* name);
    // check if given value is a valid flag and update flag according to it
    int parseFlag(const char* str);

    void countFromFile();
    void countFromInput();

public:
    WordCount();

    int handleArguments(int argc, char* argv[]);
    void startCounting();
    void printResults() const;

};


#endif //WORDCOUNT_WORDCOUNT_H