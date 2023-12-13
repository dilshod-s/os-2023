CC = gcc
CFLAGS = -Wall
OBJS = n3.o

all: n3

n3: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

n3.o: n3.c
	$(CC) $(CFLAGS) -c n3.c

clean:
	rm -f n3 $(OBJS)

run: n3
	./n3
