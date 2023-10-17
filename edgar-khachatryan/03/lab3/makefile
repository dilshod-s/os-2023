CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_FILES = file_info.cpp
TARGET = file_info

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
