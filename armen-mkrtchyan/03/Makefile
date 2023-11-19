CC = gcc
CFLAGS = -Wall
SOURCES = file-info.c
EXECUTABLE = file-info

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
