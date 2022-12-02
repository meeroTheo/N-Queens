#include <algorithm>
#include <exception>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct individual {
    int fitness;
    vector<int> indiv;
    individual(int attacks, int size) : fitness(attacks), indiv(size) {
        indiv.reserve(size);
    }
    bool operator<(const individual &rhs) {
        return fitness < rhs.fitness;
    }
    bool operator==(const individual &rhs) {
        return fitness == rhs.fitness;
    }
    bool operator>(const individual &rhs) {
        return fitness > rhs.fitness;
    }
};

class genetic {
private:
    int n;
    int popS;
    vector<individual> population;
    vector<int> solution;
    int mutation_chance; // integer from 0-100

    int fitness(vector<int> &individual) {
        // number of non-attacking pairs of queens we need to maximize
        // the maximum number of non attacking pairs is n choose 2
        // In the case of n = 8, the maximum number of non-attacking pairs is 28
        // [1,1,1,2,2,2] - [1,2] => 4 clashes
        // we want the # of attacking pairs of queens to be zero in the solution
        // an individual is a list of n numbers where each number represents the row of a queen in a column as the index
        int row_freq[n] = {0};
        int diag_freq1[2 * n] = {0};
        int diag_freq2[2 * n] = {0};

        for (int i = 0; i < n; i++) {
            row_freq[individual[i]]++;
            diag_freq1[individual[i] + i]++;
            diag_freq2[n - individual[i] + i]++;
        }

        int total_attacks = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (i < n) {
                total_attacks += row_freq[i] * (row_freq[i] - 1) / 2;
                total_attacks += diag_freq1[i] * (diag_freq1[i] - 1) / 2;
                total_attacks += diag_freq2[i] * (diag_freq2[i] - 1) / 2;
            }
        }
        return total_attacks;
    }

    /*

    int attacks = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (individual[i] == individual[j]) { // checks if two queens are in the same row/column
                attacks++;
            }
            if (individual[i] == individual[j] + (j - i)) { // checks if two queens are in the same diagonal direction (top left to bottom right)
                attacks++;
            }
            if (individual[i] == individual[j] - (j - i)) { // checks if two queens are in the same diagonal direction (bottom left to top right)
                attacks++;
            }
        }
    }
    // we take the maximum number of non-attacking pairs and subtract the number of attacking pairs to get the fitness
    return attacks;
    */

    void crossover(vector<int> &indiv1, vector<int> &indiv2, vector<int> &child1, vector<int> &child2) {
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

    void mutation(vector<int> &individual) {

        int randQueen = rand() % n;
        int randPos = rand() % n;

        // if equal, regenerate new index position
        while (randQueen == randPos) {
            randPos = rand() % n;
        }

        individual[randPos] = randQueen;
    }

    void generatePopulation() {
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        for (int j = 0; j < popS; j++) {
            population.emplace_back(individual(0, n));
            for (int i = 0; i < n; i++) {
                population[j].indiv.push_back(i);
            }
            std::shuffle(population[j].indiv.begin(), population[j].indiv.end(), rng);
        }
    }

public:
    int generations = 1;

    genetic(int n, int popSize, int mc, int exp, int max) : n(n), popS(popSize), mutation_chance(mc) {
        try {
            std::default_random_engine generator;
            std::uniform_real_distribution<double> distribution(0.0,1.0);
            int ind1, ind2;
            double r,fitnessV;
            bool isSolved = false;
            population.reserve(popS);
            vector<individual> populationTemp;
            population.reserve(popS);
            for (int i = 0; i < popS; ++i) {
                populationTemp.emplace_back(individual(0, n));
            }

            generatePopulation(); // initial population
            do {
                // set weights for each individual in the population
                for (int i = 0; i < popSize; i++) {
                    fitnessV = fitness(population[i].indiv);
                    population[i].fitness = fitnessV;
                    if (fitnessV == 0) {
                        solution = population[i].indiv;
                        printBoard(population[i].indiv);
                        isSolved = true;
                        goto isSolution;
                    }
                }
                std::sort_heap(population.begin(), population.end());

                for (int i = 0; i < popSize; i += 2) {
                    ind1=popSize*(pow(distribution(generator),exp));
                    ind2=popSize*(pow(distribution(generator),exp));
                    // individual with higher fitness will have a higher prop. of reproducing
                    crossover(population[ind1].indiv, population[ind2].indiv, populationTemp[i].indiv, populationTemp[i + 1].indiv);
                }
                for (int i = 0; i < popS; i++) {
                    for (int j = 0; j < n; j++) {
                        population[i] = populationTemp[i];
                    }
                }
                generations++;
            } while (generations <= max);
        isSolution:
            populationTemp.clear();
            cout << "Generations: " << generations << std::endl;
            if (isSolved)
                cout << "solved" << endl;
            else {
                printBoard(population[0].indiv);
                cout << "not solved" << endl;
            }
        } catch (std::exception &e) {
            cout << "error: " << e.what();
        }
    }
    void printBoard(vector<int> &indiv) {
        //Create output text file
        std::ofstream outputFile("output.txt");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (indiv[j] == i) {
                   //Writing to file
                    outputFile << "Q"
                         << " ";
                } else {
                    outputFile << "-"
                         << " ";
                }
            }
            outputFile << "\n";
        }
        //Close file
        outputFile.close();
    }
};
/*
int main() {
    genetic nQueens(100, 100, 80, 4, 10000);
}
*/