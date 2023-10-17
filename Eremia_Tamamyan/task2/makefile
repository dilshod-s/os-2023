CXX = g++
CXXFLAGS = -std = c++17 -Wall
 

all: main.o WordCount.o
	$(CXX)$(CXXFLAGS) main.o WordCount.o -o wordcount

main.o:	main.cpp
	$(CXX) -c main.cpp
	
WordCount.o: WordCount.cpp
	$(CXX) -c WordCount.cpp

clean:
	rm *.o wordcount
