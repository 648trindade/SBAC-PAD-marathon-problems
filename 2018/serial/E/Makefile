
CXXFLAGS=-O3 -std=c++11 -Wall
RM=rm -f
EXEC=mandelbrot

all: $(EXEC)

$(EXEC):
	$(CXX) $(CXXFLAGS) $(EXEC).cpp -c -o $(EXEC).o
	$(CXX) $(CXXFLAGS) $(EXEC).o -o $(EXEC)

clean:
	$(RM) $(EXEC).o $(EXEC)
