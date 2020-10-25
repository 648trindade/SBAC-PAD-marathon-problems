CFLAGS=-O3 -Wall
LDFLAGS = -lm
CC=gcc

RM=rm -f

EXEC=cholesky

all: $(EXEC)

$(EXEC):
	$(CC) $(CFLAGS) $(EXEC).c -c -o $(EXEC).o
	$(CC) $(CFLAGS) $(EXEC).o -o $(EXEC) $(LDFLAGS)

run:
	./$(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
