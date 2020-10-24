CC = g++
CPPFLAGS = -O3 #-m32

all: sieve.cpp
	$(CC) $(CPPFLAGS) -o sieve sieve.cpp

run: sieve problem_input
	./sieve problem_input

clean:
	rm -f sieve problem_output
