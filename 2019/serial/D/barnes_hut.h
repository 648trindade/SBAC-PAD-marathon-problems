/*
 * File: barnes_hut.h: header file for barnes_hut.c
 */

#ifndef Barnes_Hut_barnes_hut_h
#define Barnes_Hut_barnes_hut_h
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

/*
 * Struct that represents a node of the Barnes Hut quad tree.
 */
struct node_t {
    int particle;
    int has_particle;
    int has_children;
    double min_x, max_x, min_y, max_y, total_mass, c_x, c_y;
    struct node_t *children;
};

//Function for producing a random number between two double values.
double frand(double xmin, double xmax);

//Prints the time between two clocks in seconds
void print_time(clock_t s, clock_t e);

//OpenGL method for displaying the particles
void display(void);

//Calculates the positions of a time step
void time_step(void);

//If a particle moves beyond any of the boundaries then bounce it back
void bounce(double *x, double *y, double *u, double *v);

//Functions for handling the placement of particles in the tree
void put_particle_in_tree(int new_particle, struct node_t *node);
void place_particle(int particle, struct node_t *node);
void set_node(struct node_t *node);
void free_node(struct node_t *node);
void display_tree(struct node_t *node);

//Functions for calculating the mass and centre of mass of the tree
double calculate_mass(struct node_t *node);
double calculate_center_of_mass_x(struct node_t *node);
double calculate_center_of_mass_y(struct node_t *node);

//Functions for the force calculations
void update_forces();
void update_forces_help(int particle, struct node_t *node);
void calculate_force(int particle, struct node_t *node, double r);

#endif
