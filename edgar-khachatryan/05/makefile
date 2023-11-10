CXX = g++
CXXFLAGS = -Wall

SRC_FILES = myterm.cpp
TARGET = myterm

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
