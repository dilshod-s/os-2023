CXX = g++
CXXFLAGS = -Wall

SRC_FILES = acceleration_test_threads.cpp
TARGET = acc_threads

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm -f $(TARGET)
