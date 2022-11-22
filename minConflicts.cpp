#include <iostream>

using std::cout;
using std::endl;
using std::string;

class minConflicts {
private:
    int n;
    int *state = new int[n];
    int *conflicts = new int[n];

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
    void setConflicts() {
    }
    int attacks() {
    }
    ~minConflicts() {
        delete[] state;
        delete[] conflicts;
    }
};

int main() {
    minConflicts(8, 10000);
}