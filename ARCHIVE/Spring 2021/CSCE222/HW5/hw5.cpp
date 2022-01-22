#include <iostream>
int main() {
    int j = 50000;
    for(int i = 0; i < 8; ++i) {
        j = 1.05 * j + 1000;
        std::cout << "year " << 2018 + i << " : " << j << std::endl;
    }
    
}