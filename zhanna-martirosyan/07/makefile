CFLAGS = -Wall
OBJS = new_terminal.o

All: new_terminal

new_terminal: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

new_terminal.o: new_terminal.c
	gcc $(CFLAGS) -c new_terminal.c

clean:
	rm -f new_terminal $(OBJS)