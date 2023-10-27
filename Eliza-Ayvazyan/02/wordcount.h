#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int count_words(int fd);
int count_lines(int fd);

#endif

