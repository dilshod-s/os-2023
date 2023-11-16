CFLAGS = -Wall
OBJS = terminal.o

All: terminal

terminal: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

terminal.o: terminal.c
	gcc $(CFLAGS) -c terminal.c

clean:
	rm -f terminal $(OBJS)