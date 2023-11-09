CFLAGS = -Wall
OBJS = allocator.o

All:allocator

allocator: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

allocator.o: allocator.c
	gcc $(CFLAGS) -c allocator.c

clean:
	rm -f allocator $(OBJS)