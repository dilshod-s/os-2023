CFLAGS = -WallCFLAGS = -Wall
OBJS = potoki.o

All: potoki

potoki: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

potoki.o: potoki.c
	gcc $(CFLAGS) -c potoki.c

clean:
	rm -f potoki $(OBJS)
