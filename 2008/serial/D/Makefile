CC =g++
CPPFLAGS = -g #-m32

all: main.o puzzle.o 
	$(CC) $(CPPFLAGS) -o bbound main.o puzzle.o

main: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

puzzle: puzzle.cpp puzzle.h
	$(CC) $(CPPFLAGS) -c puzzle.cpp

run: bbound problem_input
	./bbound problem_input

clean:
	rm -f *.o bbound problem_output
