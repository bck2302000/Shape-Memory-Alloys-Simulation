#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <cmath>
#include <cfloat>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

const int m = 6;
const int n = 6;

double J(int i, int j) {
    int x_1 = i/n, y_1 = i%n;
    int x_2 = j/n, y_2 = j%n;
    double r = sqrt(pow(x_2-x_1,2) + pow(y_2-y_1,2));
    
    // int r = abs(x_2 - x_1) + abs(y_2 - y_1);
    return 1 / pow(r,3);
    // return r;
}

// Simulated Annealing Parameter
const int number_modified_spin = 2;
const int max_k = 5000000;
const double temperature = 300;
const double stop_energy = -20;
const int largest_rejected = 1000000;


#endif