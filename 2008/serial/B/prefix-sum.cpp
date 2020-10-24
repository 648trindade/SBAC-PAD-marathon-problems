#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <vector>

typedef unsigned int uint;

// Gets the input value from the input file
void get_values(char* filename, std::vector<uint>& values)
{
    std::fstream infile(filename);
    uint val;
    // The first value is the number of elements
    infile >> val;
    values.reserve(val);
    values.clear();
    // Read the elements
    while (infile >> val)
    {
        values.push_back(val);
    }
    infile.close();
}

int main(int argc, char* argv[])
{
    struct timeval timevalA;
    struct timeval timevalB;
    if (argc == 2)
    {
        std::vector<uint> values;
        get_values(argv[1], values);
        // Open the output file
        std::ofstream outfile("problem_output");
        // Start processing
        gettimeofday(&timevalA, NULL);
        uint n = values.size();
        uint prefix = 0;
        for (uint i = 0; i < n; ++i)
        {
            prefix += values[i];
            outfile << prefix << std::endl;
        }
        gettimeofday(&timevalB, NULL);
        outfile.close();

        std::cout << "time="
                  << timevalB.tv_sec - timevalA.tv_sec +
                         (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000
                  << std::endl;
    }
    else
    {
        std::cout << "Usage: ./prefix-sum problem_input \n";
    }
}
