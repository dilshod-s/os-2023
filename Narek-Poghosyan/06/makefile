CFLAGS = -Wall
OBJS = hosqer.o

All: hosqer

hosqer: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

hosqer.o: hosqer.c
	gcc $(CFLAGS) -c hosqer.c

clean:
	rm -f hosqer $(OBJS)