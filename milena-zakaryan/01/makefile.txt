CC = gcc
CFLAGS = -Wall -Wextra

all: wordcount

wordcount: main.o wordcount.o
	$(CC) $(CFLAGS) -o wordcount main.o wordcount.o

main.o: main.c wordcount.h
	$(CC) $(CFLAGS) -c main.c

wordcount.o: wordcount.c wordcount.h
	$(CC) $(CFLAGS) -c wordcount.c

clean:
	rm -f wordcount main.o wordcount.o