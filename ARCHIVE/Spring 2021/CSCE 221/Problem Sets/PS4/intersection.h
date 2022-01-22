#include <vector>
#include <iostream>

using std::vector, std::cout, std::endl;


vector<int> intersection(vector<int> a, vector<int> b) {
    vector<int> c;
    for(size_t i = 0; i < a.size(); ++i) {
        for(size_t k = 0; k < b.size(); ++k) {
            if(a.at(i) == b.at(k)) {
                c.push_back(b.at(k));
            }
        }
    }
   

    return c;
}