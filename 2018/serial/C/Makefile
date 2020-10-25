CFLAGS=-O3 -Wall
CC=gcc
RM=rm -f
EXEC=himeno

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(CFLAGS) $(EXEC).o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
