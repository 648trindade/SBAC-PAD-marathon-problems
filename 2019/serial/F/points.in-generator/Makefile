FLAGS=-O3 -std=c++11 -mcmodel=large
EXEC=input-gen

all: $(EXEC)

closest-pair:
	$(CXX) $(FLAGS) closest-pair.cpp -c -o closest-pair.o
	$(CXX) $(FLAGS) closest-pair.o -o closest-pair

input-gen:
	$(CXX) $(FLAGS) input-gen.cpp -c -o input-gen.o
	$(CXX) $(FLAGS) input-gen.o -o input-gen

clean:
	rm -rf $(EXEC) *.o
