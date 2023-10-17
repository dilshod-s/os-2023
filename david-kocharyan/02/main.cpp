#include <iostream>
#include "wordcount.h"

int main(int argc, char* argv[])
{
    WordCount counter;

    int errorCode = counter.handleArguments(argc, argv);
    if (errorCode)
    {
        std::cerr << "Usage: " << argv[0] << " [-w] [-l] [<] <filename.txt>" << std::endl;
        return 1;
    }

    counter.startCounting();

    counter.printResults();

    return 0;
}