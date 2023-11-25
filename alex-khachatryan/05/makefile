CFLAGS = -Wall
OBJS = main.o

All: terminal

terminal: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f terminal $(OBJS)

