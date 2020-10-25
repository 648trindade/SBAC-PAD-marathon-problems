CC=gcc
OUT=amd

all: amd

amd: amd.c
	$(CC) -o $(OUT) amd.c

debug: amd.c
	$(CC) -o $(OUT).debug amd.c -DDEBUG=1 -Wall

clean:
	rm -f $(OUT) $(OUT).debug
