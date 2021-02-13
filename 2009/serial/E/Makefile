FLAGS=-O2 -std=c++11

CC=g++

RM=rm -f

EXEC=tool

all: $(EXEC)

$(EXEC):
	$(CC) $(FLAGS) tool.cpp -c -o tool.o
	$(CC) $(FLAGS) tool.o -o $(EXEC)

run:
	./$(EXEC)

clean:
	$(RM) tool.o $(EXEC)