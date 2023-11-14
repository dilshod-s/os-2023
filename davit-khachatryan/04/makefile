CXX = g++
CXXFLAGS = -Wall

SRC_FILES = dummyAllocator.cpp
TARGET = dummyAllocator

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
