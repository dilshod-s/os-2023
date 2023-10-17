#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string>

class WordCounter {
public:
    static int countLinesFromFile(std::string filename);

    static int countWordsFromFile(std::string filename);

    static int countLinesFromInput();

    static int countWordsFromInput();
};

#endif
