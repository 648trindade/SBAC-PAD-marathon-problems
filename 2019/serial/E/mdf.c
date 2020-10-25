#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#define STABILITY 1.0f/sqrt(3.0f)


void mdf_heat(double ***  __restrict__ u0, 
              double ***  __restrict__ u1, 
              const unsigned int npX, 
              const unsigned int npY, 
              const unsigned int npZ,
              const double deltaH,
              const double deltaT,
              const double inErr,
              const double boundaries){
    register double alpha = deltaT / (deltaH * deltaH);
    register int continued = 1;
    register unsigned int steps = 0;
    while (continued){
      steps++;
              for (unsigned int i = 0; i < npZ; i++){
                for (unsigned int j = 0; j < npY; j++){
                  for (unsigned int k = 0; k < npX; k++){
                      register double left   = boundaries;
                      register double right  = boundaries;
                      register double up     = boundaries;
                      register double down   = boundaries;
                      register double top    = boundaries;
                      register double bottom = boundaries;
                      
                      if ((k > 0) && (k < (npX - 1))){
                        left  = u0[i][j][k-1];
                        right = u0[i][j][k+1];
                      }else if (k == 0) right = u0[i][j][k+1];
                      else left = u0[i][j][k-1];
                      
                      if ((j > 0) && (j < (npY - 1))){
                        up  = u0[i][j-1][k];
                        down = u0[i][j+1][k];
                      }else if (j == 0) down = u0[i][j+1][k];
                      else up = u0[i][j-1][k];
                      
                      if ((i > 0) && (i < (npZ - 1))){
                        top  = u0[i-1][j][k];
                        bottom = u0[i+1][j][k];
                      }else if (i == 0) bottom = u0[i+1][j][k];
                      else top = u0[i-1][j][k];
                      
                      
                      u1[i][j][k] =  alpha * ( top + bottom + up + down + left + right  - (6.0f * u0[i][j][k] )) + u0[i][j][k];
    
                  
                  }
                }
              } 
              
              double ***ptr = u0;
              u0 = u1;
              u1 = ptr;
              
              double err = 0.0f;
              double maxErr = 0.0f;
              for (unsigned int i = 0; i < npZ; i++){
                for (unsigned int j = 0; j < npY; j++){
                  for (unsigned int k = 0; k < npX; k++){
                    err = fabs(u0[i][j][k] - boundaries);
                    if (err > inErr)
                      maxErr = err;
                    else
                      continued = 0;
                  }
                }
              }
      
    }
  
    fprintf(stdout, "%u\n", steps);
    
                
}
int main (int ac, char **av){
  double ***u0;
  double ***u1;
  double deltaT = 0.0f; //0.01;
  double deltaH =0.0f;  //0.25f;
  double sizeX = 0.0f;  //1.0f;
  double sizeY = 0.0f;  //1.0f;
  double sizeZ = 0.0f;  //1.0f;
 
  fscanf(stdin, "%lf", &deltaT);
  fscanf(stdin, "%lf", &deltaH);
  fscanf(stdin, "%lf", &sizeZ);
  fscanf(stdin, "%lf", &sizeY);
  fscanf(stdin, "%lf", &sizeX);
  
  unsigned int npX = (unsigned int) (sizeX / deltaH); //Number of points in X axis
  unsigned int npY = (unsigned int) (sizeY / deltaH);
  unsigned int npZ = (unsigned int) (sizeZ / deltaH);
  
  
  //printf("p(%u, %u, %u)\n", npX, npY, npZ);
  //Allocing memory
  u0 = (double***) malloc (npZ * sizeof(double**));
  u1 = (double***) malloc (npZ * sizeof(double**));
  
  for (unsigned int i = 0; i < npZ; i++){
    u0[i] = (double**) malloc (npY * sizeof(double*));
    u1[i] = (double**) malloc (npY * sizeof(double*));
  }
  
  
  for (unsigned int i = 0; i < npZ; i++){
    for (unsigned int j = 0; j < npY; j++){
      double *aux0 = (double *) malloc (npX * sizeof(double));
      double *aux1 = (double *) malloc (npX * sizeof(double));
      //initial condition - zero in all points
      memset(aux0, 0x00, npX * sizeof(double));
      memset(aux1, 0x00, npX * sizeof(double));
      u0[i][j] = aux0;
      u1[i][j] = aux1;
    }
  }

  
  mdf_heat(u0, u1, npX, npY, npZ, deltaH, deltaT, 1e-15, 100.0f);
  //mdf_print(u1,  npX, npY, npZ);
  
  //Free memory
  for (unsigned int i = 0; i < npZ; i++){
    for (unsigned int j = 0; j < npY; j++){
      free(u0[i][j]);
      free(u1[i][j]);
    }
  }
  
  for (unsigned int i = 0; i < npZ; i++){
    free(u0[i]);
    free(u1[i]);
  }
  
  free(u0);
  free(u1);
  
  
  return EXIT_SUCCESS;
}
