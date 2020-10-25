CXX=g++
CC=gcc
FLAGS=-O3
all: problem

problem: problem.cpp
	$(CXX) $(FLAGS) problem.cpp -o problem

generator: generator.c
	$(CC) generator.c -o generator

clean:
	rm problem generator
