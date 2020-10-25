#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Reads the application information (communication graph) from an input */
uint32_t* read_application(uint32_t* processes){
    uint32_t* application;
    //Reads input
    //First line: v (number of vertices) and e (number of edges)
    uint32_t v, e;
    fscanf(stdin, "%u %u", &v, &e);
    *processes = v;

    //Allocates empty communication matrix
    application = malloc(v*v*sizeof(uint32_t));
    memset(application, 0, v*v*sizeof(uint32_t));

    //Reads edges from stdin and sets them in the communication matrix
    uint32_t i, source, dest, bytes;
    for(i = 0; i < e; ++i){
        fscanf(stdin, "%u %u %u", &source, &dest, &bytes);
        application[source*v+dest] = bytes;
#if DEBUG
        printf("Application communication: source = %u,\tdestination = %u\tbytes = %u\n", source,dest, application[source*v+dest]);
#endif
    }

    return application;
}

/* Reads the topology information (in the format of a tree) from an input */
uint32_t** read_topology(uint32_t* processors, uint32_t* height){
    uint32_t** topology;
    //Reads input
    //First line: number of leaves in the tree and height of the tree
    fscanf(stdin, "%u %u", processors, height);

    //Allocates an empty topology and the root node
    topology = malloc((*height)*sizeof(uint32_t*));
    topology[0] = malloc(sizeof(uint32_t));
    topology[0][0] = 0;    //for completeness

    //Allocates each remaining level of the topology
    //and sets the correct parent node for all
    uint32_t parent_size, parent_degree, current_size;
    parent_size = 1;
    uint32_t i, p, d;
    for(i = 1; i < (*height); ++i){
        //Reads the parent degree and computes the number of nodes in this level
        fscanf(stdin, "%u", &parent_degree);
        current_size = parent_size * parent_degree;

        //Allocates memory for the level
        topology[i] = malloc(current_size*sizeof(uint32_t));

        //Sets the parent of each node
        for(p = 0; p < parent_size; ++p){
            for(d = 0; d < parent_degree; ++d){
                topology[i][p*parent_degree+d] = p;
#if DEBUG
                printf("Topology: level %u,\t node %u\t has parent %u\n", i, p*parent_degree+d, topology[i][p*parent_degree+d]);
#endif
            }
        }

        //Prepares data for next iteration
        parent_size = current_size;
    }

    return topology;
}

/* Reads the mapping information (processes to processors) from an input */
uint32_t* read_mapping(uint32_t processes, uint32_t processors){
    uint32_t* mapping;
    //Reads input
    //First line: n (number of processes) and m (number of processors)
    uint32_t n, m;
    fscanf(stdin, "%u %u", &n, &m);

    //Checks if the numbers match with what was previously read
    if(n != processes){
        printf("Number of processes in input do not match.\n");
        exit(1);
    }
    if(m != processors){
        printf("Number of processors in input do not match.\n");
        exit(1);
    }

    //Allocates an empty mapping
    mapping = malloc(n*sizeof(uint32_t*));

    //Reads the mapping from stdin
    uint32_t i, process, processor;
    for(i = 0; i < n; ++i){
        fscanf(stdin, "%u %u", &process, &processor);
        mapping[process] = processor;
#if DEBUG
        printf("Mapping: process %u\t mapped to processor %u\n", process, mapping[process]);
#endif
    }

    return mapping;
}

/* Computes the number of hops between two leaf nodes in the topology */
uint32_t find_hops(uint32_t first_node, uint32_t second_node, uint32_t** topology, uint32_t height){
    // Number of levels searched to find the common parent (or common node)
    uint32_t common_level = 0;
    uint32_t current_level = height-1;
    // If the nodes are different, searches for their common parent
    while(first_node != second_node){
        // Move one level closer to the root
        first_node = topology[current_level][first_node];
        second_node = topology[current_level][second_node];
        ++common_level;
        --current_level;
    }
    //In a tree, we have two hops for each level that we go in the direction of the root
    return common_level*2;
}

/* Computes the hopbyte metric for the mapping */
uint64_t hopbyte(uint32_t* mapping, uint32_t* application, uint32_t processes, uint32_t** topology, uint32_t height){
    uint64_t total = 0;

    uint32_t i, j, bytes, hops;
    //For all pairs of processors
    for(i = 0; i < processes; ++i){
        for(j = 0; j < processes; ++j){
            //Gets the number of bytes sent from i to j
            bytes = application[i*processes+j];
            //Gets the number of hops between the processors where i and j are mapped
            hops = find_hops(mapping[i], mapping[j], topology, height);
            //Adds their product to the hopbyte total
            total+= bytes*hops;
        }
    }

    return total;
}

// Main program - reads input, computes hopbyte, prints output
int main (int argc, char* argv[]){

    uint32_t *application, **topology, *mapping;
    uint32_t processes, processors, height;

    //Tries to read the first input (application)
    application = read_application(&processes);
    //Tries to read the second input (topology)
    topology = read_topology(&processors, &height);
    //Tries to read the third input (mapping)
    mapping = read_mapping(processes, processors);

    //Computes and outputs the hopbyte metric of the mapping
    printf("%lu\n",hopbyte(mapping, application, processes, topology, height));

    return 0;
}
