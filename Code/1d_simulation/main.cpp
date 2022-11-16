#include "constant.h"
#include <iostream>
#include <climits>
#include <cmath>
#include <cfloat>
using namespace std;


int main() {
    double min_energy = DBL_MAX;
    int num_negative = 0;
    for (int i = 0; i < N; i++) {
        double energy = 0.5 * mu * pow((x - episolon_zero * (i*(-1) + (N-i)*1)), 2);
        num_negative = (energy < min_energy)? i : num_negative;
        min_energy = min(min_energy, energy);
    }
    cout << "Minumum Energy: " << min_energy << endl;
    cout << "number of negative sigma: " << num_negative;

    return 0;
}
