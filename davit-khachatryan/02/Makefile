target = complex_program
srcs = main.cpp ComplexNumbers.cpp
headers = ComplexNumbers.h

objs = $(srcs:.cpp=.o)
all: $(target)
$(target): $(objs)
	g++ -std=c++11 -Wall -o $@ $(objs)

%.o: %.cpp $(headers)
	g++ -std=c++11 -Wall -c $< -o $@

clean: 
	rm -rf $(target) $(objs)