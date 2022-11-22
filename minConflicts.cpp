#include <iostream>

using std::cout;
using std::endl;
using std::string;

class minConflicts {
private:
    int n;                       // number of queens
    int *state = new int[n];     // state of the board
    int *conflicts = new int[n]; // number of conflicts for each queen

public:
    minConflicts(int size, int max_steps) : n(size) {
        ; // group
    }
    void initialState() {
        // modify state
    }
    int colPosition() {
        // random column position
    }
    void setConflicts(int var) {
        // set of conflicted variables
        for (int i = 0; i < n; i++) {            // for each variable
            conflicts[i] = attacks(state[i], i); // set conflicts based on attacks, state[i] is the row position
        }
    }
    int attacks(int row, int col) {
        // number of attacks
        int attacks = 0;
        for (int i = 0; i < n; i++) {
            if (i != col) {
                if (state[i] == row || abs(i - col) == abs(state[i] - row)) {
                    attacks++;
                }
            }
        }
        return attacks;
    }
    ~minConflicts() {
        delete[] state;
        delete[] conflicts;
    }
};

int main() {
    minConflicts(8, 10000);
}