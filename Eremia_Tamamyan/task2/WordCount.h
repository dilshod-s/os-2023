#ifndef WORDCOUNT_WORDCOUNT_H
#define WORDCOUNT_WORDCOUNT_H
 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
 
class WordCount
{
private:
    std::string file;
    std::size_t line_c;
    std::size_t word_c;
 
    bool countwords;
    bool countlines;
    bool input;
 
    bool isTxT(const char* name);
    bool isFlag(const char* str);
 
    
 
public:
    WordCount();

    void count();
    int Prestart(int argc, char* argv[]);
    void print();
 
};
 
#endif //WORDCOUNT_WORDCOUNT_H
