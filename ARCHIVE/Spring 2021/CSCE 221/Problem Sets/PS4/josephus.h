#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>

using std::chrono::high_resolution_clock;

int josephus(size_t n, size_t m) {
    std::vector<int> ring;
    size_t turn = 0;
    size_t delta = 0;
    if(m == 0) {return n;} 

    //std::fstream stream1;
    //std::fstream stream2;
   //stream1.open("skipalloc.txt", std::ios_base::app);
   //stream2.open("iterate.txt", std::ios_base::app);

    for(size_t i = 1; i <= n; ++i) {
        ring.push_back(i);
    }
    //high_resolution_clock::time_point start1 = high_resolution_clock::now();
    while(ring.size() > 1) {
            std::vector<int> newring;
            //high_resolution_clock::time_point start2 = high_resolution_clock::now();
            if(turn >= ring.size()) {
                turn = 0;
            }
            else {
                while(turn < ring.size()) {
                    if(delta >= m) { 
                        ++turn;
                        delta = 0; 
                        }
                        if(turn >= ring.size()) {break;}
                     newring.push_back(ring.at(turn));
                    ++turn;
                    ++delta;
                    
                    
                }
                ring = newring;
            }
            //high_resolution_clock::time_point end2 = high_resolution_clock::now();
            //std::chrono::duration<double> delta2 = std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2);
            //stream2 << delta2.count() << endl;
    }
    //high_resolution_clock::time_point end1 = high_resolution_clock::now();

    //std::chrono::duration<double> delta1 = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);
    //stream1 << delta1.count() << endl;

    return ring.at(0);
}