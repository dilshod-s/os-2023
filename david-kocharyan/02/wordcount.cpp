#include "wordcount.h"


WordCount::WordCount() : wordCount(0), lineCount(0), countWords(false),
                         countLines(false), inputType(false), fileName{} {}


bool WordCount::isFileTxt(const char *name)
{
    int i = 0;

    for (; name[i] != '\0'; ++i){}

    i -= 4;
    if (i <= 0)
        return false;

    if (name[i] != '.' || name[i + 1] != 't'
        || name[i + 2] != 'x' || name[i + 3] != 't')
        return false;

    std::string copyToString(name);
    fileName = copyToString;

    return true;
}

bool WordCount::isFlag(const char *str)
{
    if (str[0] == '-' && str[1] == 'w' && str[2] == '\0')
    {
        countWords = true;
        return true;
    }

    if (str[0] == '-' && str[1] == 'l' && str[2] == '\0')
    {
        countLines = true;
        return true;
    }

    return false;
}


void WordCount::countFromFile()
{
    // open file
    const char* cstrFileName = fileName.c_str();
    int fd = open(cstrFileName, O_RDONLY);

    if (fd == -1)
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    char buffer[1024];
    ssize_t bytesRead;

    // read while input
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
                ++lineCount;


            if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                ++wordCount;
        }
    }

    if (bytesRead == -1)
    {
        std::cerr << "Error reading file. Exiting...\n";
        exit(1);
    }


    close(fd);
}

void WordCount::countFromInput()
{
    char buffer[1024];
    ssize_t bytesRead;


    while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
                ++lineCount;


            if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                ++wordCount;
        }
    }

}


int WordCount::handleArguments(int argc, char *argv[])
{

    // example: ./wordcount (< file.txt)
    if (argc == 1)
    {
        countLines = true;
        countWords = true;
        return 0;
    }


    if (argc == 2)
    {

        if (isFlag(argv[1]))
            return 0;
        else if (isFileTxt(argv[1]))
        {
            inputType = true;
            countLines = true;
            countWords = true;
            return 0;
        }
        else
            return 1;
    }


    if (argc == 3)
    {
        if (!isFlag(argv[1]))
            return 1;

        if (isFileTxt(argv[2]))
        {
            inputType = true;
            return 0;
        }
        else
            return 1;
    }

    return 1;
}


void WordCount::startCounting()
{
    if (inputType)
        countFromFile();
    else
        countFromInput();
}

void WordCount::printResults() const
{
    std::string message{};

    if (countWords)
        message += "Word count: " + std::to_string(wordCount) + "\n";

    if (countLines)
        message += "Line count: " + std::to_string(lineCount) + "\n";

    const char* cstrMessage = message.c_str();
    write(STDOUT_FILENO, cstrMessage, message.length());
}