#include <iostream>
#include "wordcount.h"

int main(int argc, char* argv[])
{
    WordCounter counter;

    int error = counter.handleArguments(argc, argv);
    if (error)
    {
        std::cerr << "Usage: " << argv[0] << " [-w] [-l] [<] <filename.txt>" << std::endl;
        return 1;
    }

    counter.startCounting();
    counter.printResults();

    return 0;
}

