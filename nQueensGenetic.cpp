#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::endl;
using std::string;

class genetic {
private:
    int n;
    int *population;

    long long nCr(int n, int r) {
        if (r > n - r)
            r = n - r; // because C(n, r) == C(n, n - r)
        long long ans = 1;
        int i;
        for (i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }
        return ans;
    }
    int fitness(int &individual) {
        // number of non-attacking pairs of queens we need to maximize
        // the maximum number of non attacking pairs is n choose 2
        // In the case of n = 8, the maximum number of non-attacking pairs is 28
        // [1,1,1,2,2,2] - [1,2] => 4 clashes
        // we want the # of attacking pairs of queens to be zero in the solution
        // an individual is a list of n numbers where each number represents the row of a queen in a column as the index
        int attacks = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (individual[&i] == individual[&j]) // checks if there are queens in the same row and column
                    attacks++;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (individual[&i] - individual[&j] == i - j) // checks if there are queens in the same diagonal
                    attacks++;
            }
        }
        // we take the maximum number of non-attacking pairs and subtract the number of attacking pairs to get the fitness
        return nCr(n, 2) - attacks;
    }
    void crossover(int &indiv1, int &indiv2, int &child1, int &child2) {
        //
    }

    void mutation(int &individual) {
        //
    }

    bool isSolution() {
        return false;
    }

    void initialState() {
    }
    void generatePopulation() {
        //
    }
    void reproduce(int &indiv1, int &indiv2) {
        //
    }

public:
    int generations;

    genetic(int n, int popSize) : n(n), population(new int[popSize]) {
        //
        int *populationTemp = new int[n];

        population = populationTemp;

        delete[] populationTemp;
    }
    void printBoard() {
    }
    ~genetic() {
        delete[] population;
    }
};

int main() {
    genetic nQueens(8,5);
}