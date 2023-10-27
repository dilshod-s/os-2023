#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFSIZE 4096

typedef struct {
    int words;
    int lines;
} Counters;

Counters count_words(int fd) {
    Counters cnt = {0, 0};
    char buf[BUFSIZE];
    int n, i, in_word = 0;
    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        for (i = 0; i < n; i++) {
            if (isspace(buf[i])) {
                in_word = 0;
            } else {
                if (!in_word) {
                    cnt.words++;
                    in_word = 1;
                }
            }
            if (buf[i] == '\n') {
                cnt.lines++;
            }
        }
    }
    if (in_word) {
        cnt.lines++;
    }
    return cnt;
}

Counters count_lines(int fd) {
    Counters cnt = {0, 0};
    char buf[BUFSIZE];
    int n, i;
    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        for (i = 0; i < n; i++) {
            if (buf[i] == '\n') {
                cnt.lines++;
            }
        }
    }
    if (cnt.lines == 0) {
        cnt.lines = 1;
    }
    return cnt;
}
