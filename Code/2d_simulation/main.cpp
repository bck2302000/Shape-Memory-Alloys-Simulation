#include "constant.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cfloat>
#include <chrono>
#include <cstdlib>


using namespace std;

class solver_2d {
public:
    vector<int> best_sigma;
    int count = 0;

    double J(int i, int j) {
        int x_1 = i/n, y_1 = i%n;
        int x_2 = j/n, y_2 = j%n;
        double r = sqrt(pow(x_2-x_1,2) + pow(y_2-y_1,2));
        
        // int r = abs(x_2 - x_1) + abs(y_2 - y_1);
        return 1 / pow(r,3);
        // return r;
    }

    void dfs(vector<int> &sigma, double &min_energy, int e, bool positive) {
        if (e == m*n)
            return;
        sigma[e] = (positive) ? 1 : -1;
        dfs(sigma, min_energy, e + 1, true);

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
        
        dfs(sigma, min_energy, e + 1, false);
    }
};

void brute_force() {
    solver_2d *solver = new solver_2d;
    vector<int> sigma(m*n, 0);
    double min_energy = DBL_MAX;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    solver->dfs(sigma, min_energy, 0, true);
    solver->dfs(sigma, min_energy, 0, false);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;
    cout << "Best Sigma Distribution: " << endl;
    for (int i = 0; i < m * n; i++) {
        cout << solver -> best_sigma[i] << " ";
        if ((i+1) % n == 0)
            cout << endl;
    }
    cout << "Minimum Energy: " << min_energy << endl;
    cout << solver->count;
}

double J(int i, int j) {
        int x_1 = i/n, y_1 = i%n;
        int x_2 = j/n, y_2 = j%n;
        double r = sqrt(pow(x_2-x_1,2) + pow(y_2-y_1,2));
        
        // int r = abs(x_2 - x_1) + abs(y_2 - y_1);
        return 1 / pow(r,3);
        // return r;
    }

void Simulated_Annealing(vector<int> &best_sigma) {
    int k = 0;
    double temp = temperature;
    double min_energy = DBL_MAX;
    vector<int> sigma(m*n, 1); 
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int rejected_count = 0;
    srand(time(NULL)); 
    while (k < max_k && min_energy > stop_energy && rejected_count < largest_rejected) {
        for (int i = 0; i < number_modified_spin; i++) {
            int changed_spin = ((m * n + 1) * rand() / (RAND_MAX + 1.0)) - 1;
            sigma[changed_spin] = (sigma[changed_spin] == 1) ? -1 : 1;
        }
        double energy = 0;
        for (int i = 0; i < m * n; i++) {
            for (int j = i + 1; j < m * n; j++) {
                energy += 0.5 * J(i, j) * sigma[i] * sigma[j];
            }
        }
        if (energy < min_energy) {
            min_energy = energy;
            best_sigma = sigma;
            rejected_count = 0;
        }
        else {
            double ac_prob = min(1.0, exp(-(energy - min_energy) / temp));
            double ra = ((double)rand() / (RAND_MAX));
            if (ra < ac_prob) {
                min_energy = energy;
                best_sigma = sigma;
                rejected_count = 0;
            }
            else {
                rejected_count++;
            }
        }
        k++;
        temp = temperature / k;
        // temp *= 0.95;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;
    cout << "Best Sigma Distribution: " << endl;
    for (int i = 0; i < m * n; i++) {
        cout << best_sigma[i] << " ";
        if ((i+1) % n == 0)
            cout << endl;
    }
    cout << "Minimum Energy: " << min_energy << endl;
    sigma.clear();
}

int main() {
    // brute_force();
    vector<int> best_sigma;
    Simulated_Annealing(best_sigma);
    return 0;
}