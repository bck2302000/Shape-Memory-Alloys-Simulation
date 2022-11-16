#include "solver_2d_brute.h"

void solver_2d_brute::dfs(vector<int> &sigma, double &min_energy, int e, bool positive) {
    if (e == m*n)
        return;
    sigma[e] = (positive) ? 1 : -1;
    solver_2d_brute::dfs(sigma, min_energy, e + 1, true);

    if (e == m*n - 1) {
        double energy = 0;
        for (int i = 0; i < m * n; i++) {
            for (int j = i + 1; j < m * n; j++) {
                energy += 0.5 * J(i, j) * sigma[i] * sigma[j];
            }
        }
        if (energy < min_energy) {
            min_energy = energy;
            best_sigma = sigma;
        }
        count++;
    }
    
    solver_2d_brute::dfs(sigma, min_energy, e + 1, false);
}