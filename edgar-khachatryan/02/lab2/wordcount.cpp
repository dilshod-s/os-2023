#include "wordcount.h"

WordCount::WordCount() : wordCount(0), lineCount(0), countWords(false),
                         countLines(false), inputType(false), fileName{} {}



/*
        Private methods
                            */

bool WordCount::isFileTxt(const char *name)
{
    int i = 0;
    // go to the end of the string
    for (; name[i] != '\0'; ++i){}

    // check if last 4 symbols are ".txt"
    i -= 4;
    if (i <= 0)
        return false;

    if (name[i] != '.' || name[i + 1] != 't'
        || name[i + 2] != 'x' || name[i + 3] != 't')
        return false;

    // convert file name to string
    std::string copyToString(name);
    fileName = copyToString;

    return true;
}

int WordCount::parseFlag(const char *str)
{
    // checking if argument is "-w"
    if (str[0] == '-' && str[1] == 'w' && str[2] == '\0')
    {
        // case -w -w
        if (countWords)
            return 1;

        countWords = true;
        return 0;
    }

    // checking if argument is "-l"
    if (str[0] == '-' && str[1] == 'l' && str[2] == '\0')
    {
        // case -l -l
        if (countLines)
            return 1;

        countLines = true;
        return 0;
    }

    return 1;
}


void WordCount::countFromFile()
{
    // open file
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    // this part counts lines and words in the given file
    std::string line;
    while (std::getline(file, line))
    {
        ++lineCount;
        std::istringstream stream(line);
        std::string word;

        while (stream >> word)
            ++wordCount;
    }

    file.close();
}

void WordCount::countFromInput()
{
    std::cout << "Type here your text (/exit in new line to stop): " << std::endl;
    std::string line;

    // get line from standard input and count words and lines, exit when ends
    while (std::getline(std::cin, line))
    {
        if (line == "/exit")
            return;

        ++lineCount;

        std::istringstream stream(line);
        std::string word;

        while (stream >> word)
            ++wordCount;
    }
}

/*
        Public methods
                            */

int WordCount::handleArguments(int argc, char *argv[])
{
    // example: /wordcount sample.txt
    if (argc == 2)
    {
        if (!isFileTxt(argv[1]))
        {
            if (argv[1][0] != '-' || argv[1][1] != '\0')
                return 1;
            inputType = true;
        }
        countLines = true;
        countWords = true;
        return 0;
    }

    // example: /wordcount -w sample.txt
    if (argc == 3)
    {
        if (parseFlag(argv[1]))
            return 1;
        if (!isFileTxt(argv[2]))
        {
            if (argv[2][0] != '-' || argv[2][1] != '\0')
                return 1;
            inputType = true;
        }
        return 0;
    }

    // example: /wordcount -w -l sample.txt
    if (argc == 4)
    {
        if (parseFlag(argv[1]))
            return 1;
        if (parseFlag(argv[2]))
            return 1;
        if (!isFileTxt(argv[3]))
        {
            if (argv[3][0] != '-' || argv[3][1] != '\0')
                return 1;
            inputType = true;
        }
        return 0;
    }

    return 1;
}


void WordCount::startCounting()
{
    if (!inputType)
        countFromFile();
    else
        countFromInput();
}

void WordCount::printResults() const
{
    if (countWords)
        std::cout << "Word count: " << wordCount << std::endl;

    if (countLines)
        std::cout << "Line count: " << lineCount << std::endl;
}