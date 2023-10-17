#include "wordcount.h"

WordCounter::WordCounter() : wordCount(0), lineCount(0), countWords(false),
                         countLines(false), inputType(false), fileName{} {}

bool WordCounter::isTxtFile(const char* name)
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

bool WordCounter::isFlag(const char* str)
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

void WordCounter::countFromFile()
{
    const char* cstrFileName = fileName.c_str();
    int fd = open(cstrFileName, O_RDONLY);

    if (fd == -1)
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    char buffer[1024];
    ssize_t bytesRead;

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
        std::cerr << "Error reading file. Exiting..." << std::endl;
        exit(1);
    }

    close(fd);
}

void WordCounter::countFromInput()
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

int WordCounter::handleArguments(int argc, char* argv[])
{
    // Example: ./wordcount (< file.txt)
    if (argc == 1)
    {
        countLines = true;
        countWords = true;
        return 0;
    }

    // Example: ./wordcount sample.txt
    // or     : ./wordcount -l (< file.txt)
    if (argc == 2)
    {
        // If a flag, parse. Else check if a filename and set input type. Otherwise, invalid argument passed.
        if (isFlag(argv[1]))
            return 0;
        else if (isTxtFile(argv[1]))
        {
            inputType = true;
            countLines = true;
            countWords = true;
            return 0;
        }
        else
            return 1;
    }

    // Example: /wordcount -w sample.txt
    if (argc == 3)
    {
        if (!isFlag(argv[1]))
            return 1;

        if (isTxtFile(argv[2]))
        {
            inputType = true;
            return 0;
        }
        else
            return 1;
    }

    return 1;
}

void WordCounter::startCounting()
{
    if (inputType)
        countFromFile();
    else
        countFromInput();
}

void WordCounter::printResults() const
{
    std::string message{};

    if (countWords)
        message += "Word count: " + std::to_string(wordCount) + '\n';

    if (countLines)
        message += "Line count: " + std::to_string(lineCount) + '\n';

    const char* cstrMessage = message.c_str();
    write(STDOUT_FILENO, cstrMessage, message.length());
}

