CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_FILES = main.cpp wordcount.cpp
HEADER_FILES = wordcount.h
TARGET = wordcount

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
