CFLAGS = -Wall
OBJS = term.o

All: term

term: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

term.o: term.c
	gcc $(CFLAGS) -c term.c

clean:
	rm -f term $(OBJS)



