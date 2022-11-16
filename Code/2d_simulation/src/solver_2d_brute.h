#ifndef SOLVER_2D_BRUTE_H_
#define SOLVER_2D_BRUTE_H_

#include "constant.h"

class solver_2d_brute {
public:
    vector<int> best_sigma;
    int count = 0;

    void dfs(vector<int> &sigma, double &min_energy, int e, bool positive);
};


#endif