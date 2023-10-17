CXX = gcc
CXXFLAGS = -Wall

SRC_FILES = main.c wordcount.c
TARGET = wordcount

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
