CC=gcc
FLAGS=-O3
OUT=hopbyte

all: hopbyte

hopbyte: hopbyte.c
	$(CC) $(FLAGS) -o $(OUT) hopbyte.c

debug: hopbyte.c
	$(CC) -o $(OUT).debug hopbyte.c -DDEBUG=1 -Wall -g

clean:
	rm $(OUT) $(OUT).debug
