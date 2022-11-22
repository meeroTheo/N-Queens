#include <iostream>

using std::cout;
using std::endl;
using std::string;

class minConflicts {
private:
    int n;                        // number of queens / board size
    int *currState = new int[n];  // state of the board
    int *conflicts = new int[n];  // number of conflicts for each queen

public:
    minConflicts(int size, int max_steps) : n(size) {
        bool solved = solve(max_steps);
    }
    bool solve(int max_steps){
        int colVariable;
        initialState(); //initial complete assignment for csp
        for (int i=1;i<max_steps;i++){
            if (isSolution()) return true;  //current state is a solution for csp
            colVariable = colPosition();    //randomly chosen conflicted variable from csp
            currState[colVariable]=minConflictPos(colVariable); //value (row) which minimizes conflicts
        }
        return false;
    }
    void initialState() {
        // modify state
    }
    int minConflictPos(int colVariable){
        //row num that has the least number of conflicts
        //call attacks and put into a list to pick min for rows in range n
                //like line 11, vconflicts
        //like line 12 get random pos min(vconflicts)
    }
    int colPosition() {
        // random column position given the position has more than 0 conflicts
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
    bool isSolution(){

    }
    void printState(){

    }
    ~minConflicts() {
        delete[] currState;
        delete[] conflicts;
    }
};

int main() {
    minConflicts(8, 10000);
}