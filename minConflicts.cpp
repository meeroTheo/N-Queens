#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using std::cout;
using std::endl;
using std::string;

class minConflicts {
private:
    int n;                       // number of queens / board size
    int *currState = new int[n]; // state of the board
    int *conflicts = new int[n]; // number of conflicts for each queen

public:
    minConflicts(int size, int max_steps) : n(size) {
        bool solved = solve(max_steps);
        cout << solved << '\n';
        printBoard();
    }
    bool solve(int max_steps) {
        int colVariable;
        initialState(); // initial complete assignment for csp
        for (int i = 1; i < max_steps; i++) {
            setConflicts();
            if (isSolution())
                return true;                                      // current state is a solution for csp
            colVariable = colPosition();                          // randomly chosen conflicted variable from csp
            currState[colVariable] = minConflictPos(colVariable); // value (row) which minimizes conflicts
        }
        return false;
    }
    void initialState() {
        // modify state
        for (int i = 0; i < n; i++) {
            currState[i] = i;
        }
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        std::shuffle(currState, currState + n, rng);
    }
    int minConflictPos(int colVariable) {
        int *rowConflicts = new int[n], val;
        std::vector<int> temp;
        int min = attacks(0, colVariable), newVal, minCount = 1, pos = 0;
        rowConflicts[0] = min;
        for (int i = 1; i < n; i++) {
            newVal = attacks(i, colVariable);
            rowConflicts[i] = newVal; // array containing all the conflicts at each row at colVariable
            if (newVal < min) {       // find min element
                min = newVal;
                minCount = 1;
                pos = i;
            } else if (newVal == min)
                minCount++;
        }
        val = pos;
        // push all min elements to temp vector
        if (minCount != 1) {
            for (int i = 0; i < n; i++) {
                if (rowConflicts[i] == min)
                    temp.push_back(i);
            }
            // shuffle vector
            if (temp.size() != 1) {
                auto rd = std::random_device{};
                auto rng = std::default_random_engine{rd()};
                std::shuffle(temp.begin(), temp.end(), rng);
            }
            val = temp[0];
        }
        delete[] rowConflicts;
        temp.clear();
        return val;
    }

    int colPosition() {
        // random column position given the position has more than 0 conflicts
        int pos = rand() % n;
        while (conflicts[pos] <= 0) {
            pos = rand() % n;
        }
        return pos;
    }
    void setConflicts() {
        // set of conflicted variables
        // number of attacks
        // store the number of queens in each column, diagonal, and anti-diagonal
        int colCount[n] = {0};
        int diagCount[2 * n - 1] = {0};
        int antiDiagCount[2 * n - 1] = {0};

        // count the number of queens
        for (int i = 0; i < n; i++) {
            colCount[currState[i]]++;
            diagCount[i + currState[i]]++;
            antiDiagCount[i - currState[i] + n - 1]++;
        }
        // count the number of conflicts
        for (int i = 0; i < n; i++) {
            conflicts[i] = colCount[currState[i]] - 1 + diagCount[i + currState[i]] - 1 + antiDiagCount[i - currState[i] + n - 1] - 1;
        }
    }
    int attacks(int row, int col) {

        // return the total number of attacks
        // return colCount[row] + diagCount[col + row] + antiDiagCount[col - row + n - 1];

        int attacks = 0;
        for (int i = 0; i < n; i++) {
            if (i != col) {
                if (currState[i] == row || abs(i - col) == abs(currState[i] - row)) {
                    attacks++;
                }
            }
        }
        return attacks;
    }
    bool isSolution() {
        // setConflicts();
        //  Checks if there are no conflicts found under the given # of iterations
        for (int i = 0; i < n; i++)
            if (conflicts[i] != 0)
                return false;
        return true;
    }
    void printState(int n) {
        // Prints the state in an array form where each index represents board index
        // Each value represents the row the queen is on
        for (int i = 0; i < n; i++) {
            cout << currState[i] << " ";
        }
        cout << "\n";
    }

    void printBoard() {
        // Create output text file
        std::ofstream outputFile("output.txt");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (currState[j] == i) {
                    // Writing to file
                    outputFile << "Q"
                               << " ";
                } else {
                    outputFile << "-"
                               << " ";
                }
            }
            outputFile << "\n";
        }
        // Close file
        outputFile.close();
    }
    ~minConflicts() {
        delete[] currState;
        delete[] conflicts;
    }
};

int main() {
    minConflicts temp(100, 100000);
}
