CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: wordcount

wordcount: main.o wordcount.o
    $(CC) $(LDFLAGS) -o $@ $^

main.o: main.c wordcount.h
    $(CC) $(CFLAGS) -c -o $@ $<

wordcount.o: wordcount.c wordcount.h
    $(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -f wordcount *.o
