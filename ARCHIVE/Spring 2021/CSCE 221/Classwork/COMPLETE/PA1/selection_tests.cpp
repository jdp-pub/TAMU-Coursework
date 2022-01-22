#include <stdexcept>
#include <iostream>
#include "selection.h"

int main() {
    size_t num = 10;
    int* list = new int[num];

    /* POSITIVE ONLY */
    {
        std::cout << "~~~TEST 1: POSITIVES ONLY~~~" << std::endl;

        list[0] = 9;
        list[1] = 6;
        list[2] = 13;
        list[3] = 7;
        list[4] = 8;
        list[5] = 3;
        list[6] = 5;
        list[7] = 2;
        list[8] = 0;
        list[9] = 15;

        std::cout << std::endl;
        std::cout << "element 1: " << select(1, list, num) << std::endl; // 15
        std::cout << "element 2: " << select(2, list, num) << std::endl; // 13
        std::cout << "element 3: " << select(3, list, num) << std::endl; // 9
        std::cout << "element 4: " << select(4, list, num) << std::endl; // 8
        std::cout << "element 5: " << select(5, list, num) << std::endl; // 7
        std::cout << "element 6: " << select(6, list, num) << std::endl; // 6
        std::cout << "element 7: " << select(7, list, num) << std::endl; // 5
        std::cout << "element 8: " << select(8, list, num) << std::endl; // 3
        std::cout << "element 9: " << select(9, list, num) << std::endl; // 2
        std::cout << "element 10: " << select(10, list, num) << std::endl; // 0
        try{
            std::cout << select(0, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
        try{
            std::cout << select(11, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
    }
    std::cout << std::endl;

    /* POSITIVES AND NEGATIVE */
    {
        std::cout << "~~~TEST 2: POSITIVES AND NEGATIVES~~~" << std::endl;

        list[0] = 9;
        list[1] = 6;
        list[2] = -13;
        list[3] = 7;
        list[4] = -8;
        list[5] = -3;
        list[6] = -5;
        list[7] = 8;
        list[8] = 0;
        list[9] = -15;

        std::cout << std::endl;
        std::cout << "element 1: " << select(1, list, num) << std::endl; // 9
        std::cout << "element 2: " << select(2, list, num) << std::endl; // 8
        std::cout << "element 3: " << select(3, list, num) << std::endl; // 7
        std::cout << "element 4: " << select(4, list, num) << std::endl; //6
        std::cout << "element 5: " << select(5, list, num) << std::endl; // 0
        std::cout << "element 6: " << select(6, list, num) << std::endl; // -3
        std::cout << "element 7: " << select(7, list, num) << std::endl; // -5
        std::cout << "element 8: " << select(8, list, num) << std::endl; // -8
        std::cout << "element 9: " << select(9, list, num) << std::endl; // -13
        std::cout << "element 10: " << select(10, list, num) << std::endl; // -15
        try{
            std::cout << select(0, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
        try{
            std::cout << select(11, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
    }
    std::cout << std::endl;
    
    /* NEGATIVE ONLY */
    {
        std::cout << "~~~TEST 3: NEGATIVE ONLY~~~" << std::endl;

        list[0] = -9;
        list[1] = -6;
        list[2] = -13;
        list[3] = -7;
        list[4] = -8;
        list[5] = -3;
        list[6] = -5;
        list[7] = -11;
        list[8] = -1;
        list[9] = -15;

        std::cout << std::endl;
        std::cout << "element 1: " << select(1, list, num) << std::endl; // -1
        std::cout << "element 2: " << select(2, list, num) << std::endl; // -3
        std::cout << "element 3: " << select(3, list, num) << std::endl; // -5
        std::cout << "element 4: " << select(4, list, num) << std::endl; // -6
        std::cout << "element 5: " << select(5, list, num) << std::endl; // -7
        std::cout << "element 6: " << select(6, list, num) << std::endl; // -8
        std::cout << "element 7: " << select(7, list, num) << std::endl; // -9
        std::cout << "element 8: " << select(8, list, num) << std::endl; // -11
        std::cout << "element 9: " << select(9, list, num) << std::endl; // -13
        std::cout << "element 10: " << select(10, list, num) << std::endl; // -15
        try{
            std::cout << select(0, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
        try{
            std::cout << select(11, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
    }
    std::cout << std::endl;
    
    /* POSITIVE AND NEGATIVE REPEATED VALUES */
    {
        std::cout << "~~~TEST 4: POSITIVES AND NEGATIVES REPEATED VALUES~~~" << std::endl;

        list[0] = 9;
        list[1] = 8;
        list[2] = -13;
        list[3] = 8;
        list[4] = -8;
        list[5] = -3;
        list[6] = -5;
        list[7] = 8;
        list[8] = -8;
        list[9] = -5;

        std::cout << std::endl;
        std::cout << "element 1: " << select(1, list, num) << std::endl; // 9
        std::cout << "element 2: " << select(2, list, num) << std::endl; // 8
        std::cout << "element 3: " << select(3, list, num) << std::endl; // 8
        std::cout << "element 4: " << select(4, list, num) << std::endl; // 8
        std::cout << "element 5: " << select(5, list, num) << std::endl; // -3
        std::cout << "element 6: " << select(6, list, num) << std::endl; // -5
        std::cout << "element 7: " << select(7, list, num) << std::endl; // -5
        std::cout << "element 8: " << select(8, list, num) << std::endl; // -8
        std::cout << "element 9: " << select(9, list, num) << std::endl; // -8
        std::cout << "element 10: " << select(10, list, num) << std::endl; // -13
        try{
            std::cout << select(0, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
        try{
            std::cout << select(11, list, num) << std::endl;
        }
        catch(std::invalid_argument e) {std::cout << e.what() << std::endl;}
    }
    std::cout << std::endl;

    /* EMPTY LIST */
    {
        //not sure what to do here, if N is 0 throws exception. No way to detect whether list is initialized if fed bad size.
    }

    /* ONE VALUE */
    {
        int* B = new int[1];
        B[0] = 7;
        std::cout << "~~~TEST 5: ONE VALUE~~~" << std::endl;
        std::cout << "element 1: " << select(1, B, 1) << std::endl; // 7
        delete[] B;
    }
    std::cout << std::endl;

    /* 10,000 LARGE NUMBERS, 10 SELECTIONS */
    {
        std::cout << "~~~TEST 6: LARGE VALUES~~~" << std::endl;

        int* C = new int[1000];
        for(int i = 0; i < 1000; ++i) {
            int temp = i * 4982372 + 11;
            if(temp < 0) { temp *= -1; }
            C[i] = temp;
        }

        C[610] = 0;
        C[133] = 1;
        C[232] = 2;
        C[665] = 3;
        C[454] = 4;
        C[567] = 5;
        C[343] = 6;
        C[554] = 7;
        C[111] = 8;
        C[2] = 9;

        std::cout << std::endl;
        std::cout << "element 1: " << select(1000, C, 1000) << std::endl; // 0
        std::cout << "element 2: " << select(999, C, 1000) << std::endl; // 1
        std::cout << "element 3: " << select(998, C, 1000) << std::endl; // 2
        std::cout << "element 4: " << select(997, C, 1000) << std::endl; // 3
        std::cout << "element 5: " << select(996, C, 1000) << std::endl; // 4
        std::cout << "element 6: " << select(995, C, 1000) << std::endl; // 5
        std::cout << "element 7: " << select(994, C, 1000) << std::endl; // 6
        std::cout << "element 8: " << select(993, C, 1000) << std::endl; // 7
        std::cout << "element 9: " << select(992, C, 1000) << std::endl; // 8
        std::cout << "element 10: " << select(991, C, 1000) << std::endl; // 9
        std::cout << "largest number: " << select(1, C, 1000) << std::endl; // something big

        delete[] C;
    }

    delete[] list;

}