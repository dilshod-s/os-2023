CXX = g++
CXXFLAGS = -Wall

SRC_FILES = redirection.cpp
TARGET = redirection

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
