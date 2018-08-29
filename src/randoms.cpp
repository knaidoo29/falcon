#include "../include/falcon.h"

#include <iostream>
#include <time.h>
#include <cmath>

// Array Randoms

void get_randoms(float rands[], int size){
    // Change initial random seed, which is based on the time.
    srand( (unsigned)time( NULL ) );
    // Assign random floats between 0 and 1 to the x and y arrays.
    for (int i = 0; i < size; i++)
    {
        rands[i] = (float) rand()/RAND_MAX;
    }
}

void get_randoms(double rands[], int size){
    // Change initial random seed, which is based on the time.
    srand( (unsigned)time( NULL ) );
    // Assign random floats between 0 and 1 to the x and y arrays.
    for (int i = 0; i < size; i++)
    {
        rands[i] = (double) rand()/RAND_MAX;
    }
}

// Vector Randoms

void get_randoms(vector<float> &rands, int size){
    // Change initial random seed, which is based on the time.
    srand( (unsigned)time( NULL ) );
    for (int i = 0; i != size; i++)
    {
        rands[i] = ((float) rand())/RAND_MAX;
    }
}

void get_randoms(vector<double> &rands, int size){
    // Change initial random seed, which is based on the time.
    srand( (unsigned)time( NULL ) );
    for (int i = 0; i != size; i++)
    {
        rands[i] = ((double) rand())/RAND_MAX;
    }
}
