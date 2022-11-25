#include <iostream>
#include <random>

using std::cout;
using std::endl;
using std::string;

class genetic {
private:
    int n;
    int popS;
    int **population;
    int *weights;
    long long nCrValue;
    int *solution;

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
    int fitness(int *individual) {
        // number of non-attacking pairs of queens we need to maximize
        // the maximum number of non attacking pairs is n choose 2
        // In the case of n = 8, the maximum number of non-attacking pairs is 28
        // [1,1,1,2,2,2] - [1,2] => 4 clashes
        // we want the # of attacking pairs of queens to be zero in the solution
        // an individual is a list of n numbers where each number represents the row of a queen in a column as the index
        int attacks = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (individual[i] == individual[j]) // checks if there are queens in the same row and column
                    attacks++;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (individual[i] - individual[j] == i - j) // checks if there are queens in the same diagonal
                    attacks++;
            }
        }
        // we take the maximum number of non-attacking pairs and subtract the number of attacking pairs to get the fitness
        return nCrValue - attacks;
    }
    void crossover(int *indiv1, int *indiv2, int *child1, int *child2) {
        //
    }

    void mutation(int *individual) {

        // seed for random number
        srand((unsigned int)time(NULL));
        float randNum = (float)rand() / RAND_MAX;

        // mutation probability
        float mutProb = 0.2;

        if (randNum < mutProb) {
            int randQueen = rand() % (n) + 1;
            int randPos = rand() % (n) + 1;

            // if equal, regenerate new index position
            while (randQueen = randPos) {
                randPos = rand() % (n) + 1;
            }

            individual[randPos] = randQueen;
            individual[randQueen] = randPos;
        }
    }

    void generatePopulation() {
        //
    }

public:
    int generations = 0;

    genetic(int n, int popSize, int max) : n(n), popS(popSize), population(new int *[popSize]) {
        int **populationTemp = new int *[popSize];
        int *child1, *child2;
        int fitnessV;
        weights = new int[popSize];
        nCrValue = nCr(n, 2);

        generatePopulation(); // initial population
        do {
            // set weights for each individual in the population
            for (int i = 0; i < popSize; i++) {
                fitnessV = fitness(population[i]);
                if (fitnessV == nCrValue) {
                    solution = population[i];
                    goto isSolution;
                }
                weights[i] = fitnessV;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::discrete_distribution<int> d(weights, weights + popSize);

            for (int i = 0; i < popSize / 2; i++) {
                // individual with higher fitness will have a higher prop. of reproducing
                crossover(population[d(gen)], population[d(gen)], child1, child2);
                populationTemp[i] = child1;
                populationTemp[i + 1] = child2;
            }

            population = populationTemp;
            generations++;
        } while (generations <= max);
    isSolution:
        delete[] populationTemp;
    }
    void printBoard() {
    }
    ~genetic() {
        for (int i = 0; i < popS; i++)
            delete[] population[i];
        delete[] population;
        delete[] weights;
    }
};

int main() {
    genetic nQueens(8, 5, 10000);
}