#include <algorithm>
#include <exception>
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
    int mutation_chance; // integer from 0-100

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
        // determines a random crossover point between 1 to n
        int crosspoint = rand() % n, mutation_score;

        // creates children
        for (int i = 0; i < n; i++) {
            if (i > crosspoint) {
                child1[i] = indiv2[i];
                child2[i] = indiv1[i];
            } else {
                child1[i] = indiv1[i];
                child2[i] = indiv2[i];
            }
        }

        // mutates children if applicable
        for (short child = 1; child <= 2; child++) {
            mutation_score = rand() % 100 + 1;
            if (mutation_score <= mutation_chance) {
                if (child == 1) {
                    mutation(child1);
                } else {
                    mutation(child2);
                }
            }
        }
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
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        for (int j = 0; j < popS; j++) {
            population[j] = new int[n];
            for (int i = 0; i < n; i++) {
                population[j][i] = i;
            }
            std::shuffle(population[j], population[j] + n, rng);
        }
    }

public:
    int generations = 0;

    genetic(int n, int popSize, int mc,int max) : n(n), popS(popSize), mutation_chance(mc) ,population(new int *[popSize]) {
        try {
            int **populationTemp = new int *[popSize];
            int fitnessV;
            bool isSolved = false;
            weights = new int[popSize];
            nCrValue = nCr(n, 2);

            generatePopulation(); // initial population
            do {
                // set weights for each individual in the population
                for (int i = 0; i < popSize; i++) {
                    fitnessV = fitness(population[i]);
                    if (fitnessV == nCrValue) {
                        solution = population[i];
                        printBoard(population[i]);
                        isSolved = true;
                        goto isSolution;
                    }
                    weights[i] = fitnessV;
                }

                std::random_device rd;
                std::mt19937 gen(rd());
                std::discrete_distribution<int> d(weights, weights + popSize);
                int *child1 = new int[n], *child2 = new int[n];
                for (int i = 0; i < popSize / 2; i++) {
                    // individual with higher fitness will have a higher prop. of reproducing
                    crossover(population[d(gen)], population[d(gen)], child1, child2);
                    populationTemp[i] = child1;
                    populationTemp[i + 1] = child2;
                }

                population = populationTemp;
                populationTemp = new int *[popSize];
                generations++;
                printBoard(population[0]);
            } while (generations <= max);
        isSolution:
            cout << generations << std::endl;
            if (isSolved)
                cout << "solved" << endl;
            delete[] populationTemp;
        } catch (std::exception &e) {
            cout << "error: " << e.what();
        }
    }
    void printBoard(int *indiv) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (indiv[j] == i) {
                    cout << "Q"
                         << " ";
                } else {
                    cout << "-"
                         << " ";
                }
            }
            cout << "\n";
        }
    }
    ~genetic() {
        for (int i = 0; i < popS; i++)
            delete[] population[i];
        delete[] population;
        delete[] weights;
    }
};

int main() {
    genetic nQueens(20, 10,80, 100000);
}