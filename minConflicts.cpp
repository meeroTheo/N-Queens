#include <iostream>

using std::cout;
using std::endl;
using std::string;

class minConflicts {
private:
    int n;
    int *currState = new int[n];
    int *conflicts = new int[n];

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
    void setConflicts() {
    }
    int attacks() {
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