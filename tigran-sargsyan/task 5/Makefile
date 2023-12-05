CC=g++
CFLAGS=-std=c++11 -pthread

all: exec_command

exec_command: exec_command.cpp
    $(CC) $(CFLAGS) -o exec_command exec_command.cpp

clean:
    rm -f exec_command
