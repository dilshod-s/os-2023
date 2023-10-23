# Makefile

CC = gcc
CFLAGS = -Wall -Wextra

all: wordcount

wordcount: main.o wordcount.o
 $(CC) $(CFLAGS)  main.o wordcount.o -o wordcount

main.o: main.c 
 $(CC) $(CFLAGS) -c main.c

wordcount.o: wordcount.c 
 $(CC) $(CFLAGS) -c wordcount.c

clean:
 rm *.o wordcount
