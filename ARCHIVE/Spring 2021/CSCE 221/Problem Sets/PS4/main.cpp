#include "printLots.h"
#include "intersection.h"
#include "josephus.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using std::chrono::high_resolution_clock;

int main() {
    /*
    vector<int> a = {1,2,3,4,6,8,11,112};
    vector<int> b = {2,3,4,11,110,112};

    //printLots(a,b);

    vector<int> c = intersection(a,b);

    for(size_t i = 0; i < c.size(); ++i) {
        cout << "intersection list position " << i << ": " << c.at(i) << endl;
    }
    */

   std::fstream stream;
   stream.open("win.txt");

   //high_resolution_clock delta;


   for(size_t i = 1; i < 10000; ++i) {
    //high_resolution_clock::time_point start = high_resolution_clock::now();
    int placeholde = josephus(i,1);
    stream << placeholde << endl;
    //high_resolution_clock::time_point end = high_resolution_clock::now();

    //std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    //stream << delta.count() << endl;
   }

}