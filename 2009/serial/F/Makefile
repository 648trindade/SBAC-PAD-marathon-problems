FLAGS=-O2

CC=gcc

RM=rm -f

EXEC=fib

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) fib.c -c -o fib.o
	$(CC) $(FLAGS) fib.o -o $(EXEC)

run:
	./$(EXEC) < input

clean:
	$(RM) fib.o $(EXEC)
