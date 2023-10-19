CFLAGS = -Wall
OBJS = main.o wordcount.o

all: wordcount

wordcount: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

main.o: main.c wordcount.h
	gcc $(CFLAGS) -c main.c

wordcount.o: wordcount.c wordcount.h
	gcc $(CFLAGS) -c wordcount.c

clean:
	rm -f wordcount $(OBJS)
