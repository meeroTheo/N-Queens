#include <algorithm>
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
    }
    int minConflictPos(int colVariable) {
        int *rowConflicts = new int[n], val;
        std::vector<int> temp;
        int val;
        for (int i = 0; i < n; i++)
            rowConflicts[i] = attacks(i, colVariable); // array containing all the conflicts at each row at colVariable
        // find min element
        int min = rowConflicts[0];
        for (int i = 1; i < n; i++) {
            if (rowConflicts[i] < min)
                min = rowConflicts[i];
        }
        // push all min elements to temp vector
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
        delete[] rowConflicts;
        temp.clear();
        return val;
    }
    int colPosition() {
        int randCol;
        // random column position given the position has more than 0 conflicts
        for (int i = 0; i < n-1; i++){
            if (conflicts[i] == 0) {
                randCol = random.choice(n-1);
            }
        }
        return randCol;
    }
    void setConflicts() {
        // set of conflicted variables
        for (int i = 0; i < n; i++) {                // for each variable
            conflicts[i] = attacks(currState[i], i); // set conflicts based on attacks, state[i] is the row position
        }
    }
    int attacks(int row, int col) {
        // number of attacks
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
        setConflicts();
        //Checks if there are no conflicts found under the given # of iterations
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

    void printBoard(int currState) {
        // Prints the board for visualizing and verifying correctness
        for (int i = 0; i < (sizeof(n) / sizeof(int)); i++) {
            for (int n = 0; n < 8; n++) {
                if (n == i) {
                    cout << "Q"
                         << " ";
                } else {
                    cout << "X"
                         << " ";
                }
            }
            cout << "\n";
        }
    }
    ~minConflicts() {
        delete[] currState;
        delete[] conflicts;
    }
};

int main() {
    minConflicts(8, 10000);
}
