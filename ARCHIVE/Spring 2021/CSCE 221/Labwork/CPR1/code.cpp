#include <vector>
#include <iostream>

using std::vector;

//my original code.cpp file was unfinished, uncompilable, and not turned in. 
//as an improvement, I'm turning in this one for the revision. 
//In the future I plan to submit any attempts I make even if theyre unfinished.

int find_min(vector<int> a) { //in this function, the type is int but int represents usage with any generic Comparable class or struct
                            // vector is used here for ease in accessing the element count
    int min = a.at(0);
    for(size_t i = 0; i < a.size(); ++i) {
        if(a.at(i) < min) {
            min = a.at(i);
        }
    }

    return min;
}

int main () {
    vector<int> a = {1,2,3,-4,3,2,1};

    std::cout << find_min(a) << std::endl; //outputs minimum of comparable array
}