FLAGS=-O3 -std=c++11 -mcmodel=large
EXEC=closest-pair

all: $(EXEC)

$(EXEC):
	$(CXX) $(FLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(FLAGS) $(EXEC).o -o $(EXEC)

clean:
	rm -rf $(EXEC) *.o
