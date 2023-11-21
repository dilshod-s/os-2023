CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_FILES = terminal.cpp
TARGET = terminal

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
