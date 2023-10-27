all: wordcount main
	gcc main.o wordcount.o -o wordcount

wordcount: 
	gcc -c wordcount.c

main: 
	gcc -c main.c

clean:
	rm -f *.o wordcount
