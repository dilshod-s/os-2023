CXX = g++
CXXFLAGSE = -std=c++17 -Wall

all: main.o filecheck.o
	$(CXX) $(CXXFLAGSE) main.o filecheck.o -o fileinfo

main.o: main.cpp
	-g++ -c main.cpp

filecheck.o: filecheck.cpp
	-g++ -c filecheck.cpp
clean:
	rm -f *.o fileinfo