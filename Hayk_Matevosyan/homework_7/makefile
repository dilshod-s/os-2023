CFLAGS = -Wall
OBJS = term_new.o

All: term_new

term_new: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

term_new.o: term_new.c
	gcc $(CFLAGS) -c term_new.c

clean:
	rm -f term_new $(OBJS)
