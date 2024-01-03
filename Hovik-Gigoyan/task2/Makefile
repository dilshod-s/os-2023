CXX = g++
CXXFLAGS = -Wall -g

all: main

main: main.o ComplexNumber.o
	$(CXX) $(CXXFLAGS) -o main main.o ComplexNumber.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

ComplexNumber.o: ComplexNumber.cpp
	$(CXX) $(CXXFLAGS) -c ComplexNumber.cpp

clean:
	rm -f *.o main
