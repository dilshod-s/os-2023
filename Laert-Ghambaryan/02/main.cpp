#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "wordcount.cpp"

const int BUFFER_SIZE = 4096;

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        write(STDERR_FILENO, "Usage: ./wordcount -l/-w [<path to file>]\n", 43);
        return 1;
    }

    std::string option = argv[1];
    std::string filePath;

    // Check if a file path is provided as the third argument
    if (argc == 3) {
        filePath = argv[2];
    }

    int fd;

    if (argc == 2) {
        // Read from stdin
        fd = STDIN_FILENO;
    } else {
        // Open the file
        fd = open(filePath.c_str(), O_RDONLY);
        if (fd == -1) {
            write(STDERR_FILENO, "Error opening the file.\n", 24);
            return 1;
        }
    }

    WordCounter wordCounter(fd);
    int result;

    if (option == "-l") {
        result = wordCounter.countLines();
    } else if (option == "-w") {
        result = wordCounter.countWords();
    } else {
        write(STDERR_FILENO, "Invalid option. Use -l for line count or -w for word count.\n", 59);
        if (fd != STDIN_FILENO) {
            close(fd);
        }
        return 1;
    }

    char outputBuffer[100]; // Buffer for output
    int outputLength = snprintf(outputBuffer, sizeof(outputBuffer), "Result: %d\n", result);
    write(STDOUT_FILENO, outputBuffer, outputLength);

    if (fd != STDIN_FILENO) {
        close(fd);
    }

    return 0;
}
