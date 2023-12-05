CFLAGS = -Wall
OBJS = thread.o

All: thread

thread: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

thread.o: thread.c
	gcc $(CFLAGS) -c thread.c

clean:
	rm -f thread $(OBJS)