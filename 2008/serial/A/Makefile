CC = g++
CPPFLAGS = -O3

all: median.cpp
	$(CC) $(CPPFLAGS) -o median median.cpp

run: median problem_input
	./median problem_input

clean:
	rm -f median problem_output
