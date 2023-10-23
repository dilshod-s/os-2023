CFLAGS = -Wall
OBJS = lab3.o

All:lab3

lab3: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

lab3.o: lab3.c
	gcc $(CFLAGS) -c lab3.c

clean:
	rm -f lab3 $(OBJS)