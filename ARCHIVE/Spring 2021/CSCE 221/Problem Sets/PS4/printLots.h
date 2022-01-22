#include <vector>
#include <iostream>

using std::vector, std::cout, std::endl;

void printLots(vector<int> a, vector<int> b) {
    for(size_t i = 0; i < b.size(); ++i) { // O(N)
        cout << a.at(b.at(i)) << endl;
    }
}