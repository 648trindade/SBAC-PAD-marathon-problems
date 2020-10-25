#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Main program - reads parameters, generates graph
int main (int argc, char* argv[]) {

    //Checks if parameters have been passed
    if (argc < 5) {
        printf("Missing parameters.\nUsage: %s [#vertices] [#edges] [rand seed] [output file name]\n",argv[0]);
        exit(1);
    }

    //inputs
    uint32_t v, e, max_cost, seed;
    v = atoi(argv[1]);
    if (v > 100000) {
        printf("The number of vertices cannot be bigger than 10000.\n");
        exit(1);
    }
    e = atoi(argv[2]);
    if (e > (v-1)*(v-1)) {
        printf("The number of edges has to be smaller.\n");
        exit(1);
    }
    max_cost = 100;
    seed = atoi(argv[3]);
    srand(seed);

    //Tries to open the output file
    FILE* output = fopen(argv[4], "w");
    if(!output){
        printf("Could not open file \"%s\"\n",argv[5]);
        exit(1);
    }

    //Writes output file
    //First line: v (number of vertices) and e (number of edges)

    uint32_t* graph = calloc(v*v,sizeof(uint32_t));
    //Generates edges to write to file
    uint32_t source, dest, cost;
    uint32_t i, j;
    uint32_t todo=e;

    while(todo) {
        source = rand() % v;
        dest = rand() % v;
        cost = 1 + (rand() % max_cost);
        if(graph[source*v+dest] == 0) {
            graph[source*v+dest] = cost;
            --todo;
        } else if(graph[source*v+dest] > cost) {
            graph[source*v+dest] = cost;
		}
    }

    //Prints graph
    fprintf(output, "%u %u\n", v, e);

    for ( i = 0; i < v; ++i ){
        for ( j = 0; j < v; ++j ){
            if (graph[i*v+j] > 0)
                fprintf(output, "%u %u %u\n", i, j, graph[i*v+j]);
        }
    }

    fclose(output);

    return 0;
}
