CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=c11

main: main.o memory.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o main
