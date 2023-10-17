#include <unistd.h>
#include <ctype.h>

class WordCounter {
public:
    WordCounter(int fd) : fileDescriptor(fd) {}

    int countWords() {
        char buffer[4096];
        int bytesRead;
        int wordCount = 0;
        int inWord = 0;

        while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
            for (int i = 0; i < bytesRead; ++i) {
                if (isspace(buffer[i])) {
                    if (inWord) {
                        inWord = 0;
                        wordCount++;
                    }
                } else {
                    inWord = 1;
                }
            }
        }

        if (inWord) {
            wordCount++;
        }

        return wordCount;
    }

    int countLines() {
        char buffer[4096];
        int bytesRead;
        int lineCount = 0;

        while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] == '\n') {
                    lineCount++;
                }
            }
        }

        return lineCount;
    }

private:
    int fileDescriptor;
};
