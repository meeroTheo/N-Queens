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

    int fitness(int &individual) {
        //
        return 0;
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