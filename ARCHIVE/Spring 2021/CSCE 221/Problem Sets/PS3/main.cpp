#include <iostream>
#include <fstream>

using std::fstream, std::endl;

// this program outputs datapoints into a txt

//these datapoints are in a format acceptable for plotting in excel

//the plots describe asymptotic behavior of various functions

int main() {

    unsigned long long int numberOfComputations = 0;
    unsigned int sum = 0;

    // fragment 1
    fstream stream;
    stream.open("Frag1.txt");

    for(unsigned int i = 1; i <= 1000; ++i) {
        sum = sum + 1;
        stream << i << endl;
    }

    stream.close();


    //fragment 2
    stream.open("Frag2.txt");

    for(unsigned int i = 1; i <= 100000; ++i) {
        for(unsigned int j = 1; j <= i; ++j) {
            sum = sum + 1;
            ++numberOfComputations;
            
        }
        stream << numberOfComputations << endl;
    }

    stream.close();

    //fragment 3
    stream.open("Frag3.txt");
    numberOfComputations = 0;

    for(unsigned int i = 1; i <= 1000; ++i) {
        for(unsigned int j = 1; j <= i*i; ++j) {
            for(unsigned int k = 1; k <= j; ++k) {
                sum = sum + 1;
                ++numberOfComputations;
                
            }
        }
        stream << numberOfComputations << endl;
    }

    stream.close();
}