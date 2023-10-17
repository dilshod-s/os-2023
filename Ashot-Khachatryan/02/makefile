CXX = g++
CXXFLAGS = -Wall

CPP_FILES = main.cpp wordcount.cpp
FILE = wordcount
HEADER_FILES = wordcount.h


all: $(FILE)

$(FILE): $(CPP_FILES) $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) $(CPP_FILES) -o $(FILE)

clean:
	rm -f $(FILE)
