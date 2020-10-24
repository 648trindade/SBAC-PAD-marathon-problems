#include "puzzle.h"
#include <iostream>
#include <queue>
#include <stdio.h>
#include <sys/time.h>
#include <vector>

typedef std::priority_queue<Puzzle, std::vector<Puzzle>, std::greater<Puzzle>>
    PuzzleQueue;

int main(int argc, char* argv[])
{
    struct timeval timevalA;
    struct timeval timevalB;

    char blah;
    int count = 0;
    if (argc == 2)
    {
        gettimeofday(&timevalA, NULL);
        // Loads puzzle
        Puzzle p(argv[1]);
        // Initialize Priority queue
        PuzzleQueue pq;
        pq.push(p);
        do
        {
            // Gets the most promising partial solution
            p = pq.top();
            pq.pop();
            ++count;
            if (p.cost == 0)
            {
                // It is our solution!
                p.print_solution();
                break;
            }
            else
            {
                // Tests for each possible movement and
                // adds it to the queue
                for (int i = 1; i <= 4; ++i)
                {
                    Puzzle p2 = p;
                    if (p2.move(i))
                    {
                        pq.push(p2);
                    }
                }
            }
        } while (true);
        gettimeofday(&timevalB, NULL);
        std::cout << "time="
                  << timevalB.tv_sec - timevalA.tv_sec +
                         (timevalB.tv_usec - timevalA.tv_usec) / (double)1000000
                  << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Usage: ./bbound input_file\n";
    }
}
