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
    int *rowCount = new int[n]();
    int *diagCount = new int[2 * n - 1]();
    int *antiDiagCount = new int[2 * n - 1]();
    int numConflicts = 0;

public:
    minConflicts(int size, int max_steps) : n(size) {
        clock_t start, end;
        start = clock();
        bool solved = solve(max_steps);
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        if (solved) {
            cout << "Solved board of size " << n << " in: " << time_taken << " seconds\n";
            cout << "Printing time: ";
            start = clock();
            printBoard();
            end = clock();
            cout << double(end - start) / double(CLOCKS_PER_SEC) << " seconds\n";
        } else

            cout << "could not solve: " << time_taken << " seconds\n";
    }
    bool solve(int max_steps) {
        int colVariable, rowVariable;
        initialState(); // initial complete assignment for csp
        for (int i = 1; i < max_steps; i++) {
            if (numConflicts == 0)
                return true;                           // current state is a solution for csp
            colVariable = colPosition();               // randomly chosen conflicted variable from csp
            rowVariable = minConflictPos(colVariable); // value (row) which minimizes conflicts
            updateConflicts(currState[colVariable], rowVariable, colVariable);
        }
        return false;
    }

    void updateConflicts(int oldRow, int newRow, int col) {
        rowCount[currState[col]]--;
        diagCount[col + currState[col]]--;
        antiDiagCount[col - currState[col] + n - 1]--;

        currState[col] = newRow;
        rowCount[currState[col]]++;
        diagCount[col + currState[col]]++;
        antiDiagCount[col - currState[col] + n - 1]++;
        numConflicts = 0;
        for (int i = 0; i < n; i++) {
            numConflicts += rowCount[currState[i]] - 1 + diagCount[i + currState[i]] - 1 + antiDiagCount[i - currState[i] + n - 1] - 1;
        }
    }
    void initialState() {
        // modify state
        for (int i = 0; i < n; i++) {
            currState[i] = i;
        }
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        std::shuffle(currState, currState + n, rng);
        setConflicts();
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
        int pos = rand() % n,count=0;
        while (attacks(currState[pos], pos) <= 0) {
            pos = rand() % n;
            count++;
            if (count >n){
                for (int i=0;i<n;i++){
                    if (attacks(currState[i], i) > 0)
                        return i;
                }
            }
        }
        return pos;
    }
    void setConflicts() {
        // set of conflicted variables
        // number of attacks
        // store the number of queens in each column, diagonal, and anti-diagonal

        // count the number of queens
        for (int i = 0; i < n; i++) {
            rowCount[currState[i]]++;
            diagCount[i + currState[i]]++;
            antiDiagCount[i - currState[i] + n - 1]++;
        }
        // count the number of conflicts
        for (int i = 0; i < n; i++) {
            numConflicts += rowCount[currState[i]] - 1 + diagCount[i + currState[i]] - 1 + antiDiagCount[i - currState[i] + n - 1] - 1;
        }
    }
    int attacks(int row, int col) {
        return rowCount[row] - 1 + diagCount[col + row] - 1 + antiDiagCount[col - row + n - 1] - 1;
        ;
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
        delete[] rowCount;
        delete[] diagCount;
        delete[] antiDiagCount;
    }
};

int main() {
    minConflicts temp(8, 100000);
}
