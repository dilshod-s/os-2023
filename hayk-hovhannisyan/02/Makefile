all: wordcount

wordcount: main.o wordcount.o
	gcc main.o wordcount.o -o wordcount


main.o: main.c
	gcc -c main.c


wordcount.o: wordcount.c
	gcc -c wordcount.c

clean:
	rm -f *.o wordcount
