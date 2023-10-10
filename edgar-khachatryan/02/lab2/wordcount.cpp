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

bool WordCount::isFlag(const char *str)
{
    // checking if argument is "-w"
    if (str[0] == '-' && str[1] == 'w' && str[2] == '\0')
    {
        countWords = true;
        return true;
    }

    // checking if argument is "-l"
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

    // buffer to read data
    char buffer[1024];
    ssize_t bytesRead;

    // read while input
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
                ++lineCount;

            // space, tab, or newline characters are word separators
            if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                ++wordCount;
        }
    }

    if (bytesRead == -1)
    {
        std::cerr << "Error reading file. Exiting...\n";
        exit(1);
    }

    // close the file descriptor
    close(fd);
}

void WordCount::countFromInput()
{
    char buffer[1024];
    ssize_t bytesRead;

    // read while input
    while ((bytesRead = read(0, buffer, sizeof(buffer))) > 0)
    {
        for (ssize_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
                ++lineCount;

            // space, tab, or newline characters are word separators
            if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
                ++wordCount;
        }
    }

}

/*
        Public methods
                            */

int WordCount::handleArguments(int argc, char *argv[])
{

    // example: ./wordcount (< file.txt)
    if (argc == 1)
    {
        countLines = true;
        countWords = true;
        return 0;
    }

    // example: ./wordcount sample.txt
    // or     : ./wordcount -l (< file.txt)
    if (argc == 2)
    {
        // If a flag, parse. Else check if a filename and set input type. Otherwise, invalid argument passed.
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

    // example: /wordcount -w sample.txt
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
