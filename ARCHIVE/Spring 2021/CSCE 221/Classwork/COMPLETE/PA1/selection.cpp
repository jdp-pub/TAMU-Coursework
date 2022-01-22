#include <stdexcept>
#include <iostream>
#include "selection.h"

int select(size_t k, const int* list, size_t N) {
    
    try {
        if(k < 1 || k > N) { throw 1; }
        if(N < 1) { throw 1; }
        if(list == nullptr) { throw 1; }
    }
    catch(int n) {
        if(n == 1) {
            throw std::invalid_argument("int select(size_t, const int*, size_t): Requested index out of range.");
        }
    }

    // copy array
    int* A = new int[N];
    for(size_t i = 0; i < N; ++i) {
        A[i] = list[i];
    }

    //sort copied array (bubble sort)
    bool sorting = true;
    while(sorting) {
        sorting = false;
        for(size_t i = 0; i < N-1; ++i) {
            if(A[i] < A[i + 1]) {
                sorting = true;
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }

    int n = A[k - 1];
    delete[] A;
    //return kth index of new array
    return n;
}


