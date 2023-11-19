CXX = g++
CXXFLAGS = -Wall

SRC_FILES = allocator.cpp
TARGET = allocator

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
