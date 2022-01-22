#include <iostream>
#include <cmath>
#include "./nth_root.h"

int main() {
    double number; 
    double root;
        
    //iterates over a nontrivial amount of number combinations
    for (number = -10.0; number <= 10.0; ++number)
    {
        for (root = -10.0; root <= 10.0; root += 0.5)
        {
            int test = number;
        
            // ignores out of domain root/number combinations
            try {
                nth_root(test, root);
            }
            catch(std::domain_error& error)
            {
                continue;
            }

            // if test passed (within domain), executes function, outputs current place in loop
            nth_root(test, root);
            double actual = nth_root(test, root);
            std::cout << "nth_root(" << test << ", " << root << ") = " << actual << std::endl;

            //compares accuracy of function, assuming that pow() outputs the correct value, 
            //only passes if the difference between actual and expected are negligible
            double expected = std::pow(test, 1.0 / root);
            if (std::fabs(actual - expected) > 0.00005) {
                std::cout << "[FAIL] (" << test << ", " << root << ")" <<  std::endl;
                std::cout << "  expected nth_root(" << test << ", " << root << ") to be " << expected << std::endl;
                std::cout << "  got " << actual << std::endl;
            } else {
                std::cout << "[PASS] (" << test << ", " << root << ")" << std::endl;
            }

            //EOF
        }
    }
}
