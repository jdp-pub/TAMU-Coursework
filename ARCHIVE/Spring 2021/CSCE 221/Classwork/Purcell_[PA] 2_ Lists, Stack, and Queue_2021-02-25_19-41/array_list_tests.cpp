#include <iostream>
#include "array_list.h"

using std::cout, std::endl;

int main() {
    ArrayList<int> A;
    ArrayList<int> C;

    cout << "Initializing 3 lists..." << endl << endl;

    A.print();
    C.print();

    cout << "Testing insert..." << endl << endl;
    A.insert(0, 1);
    A.insert(0,2);
    A.insert(1, 3);
    A.insert(1, 4);
    A.insert(4, 5);
    A.print();

    try { A.insert(10, 100); }
    catch(std::out_of_range e) { cout << "Test exception caught..." << endl << endl; }

    cout << "Testing copy assingment..." << endl << endl;

    C = A;
    A=A;

    cout << "Contents of " << &A << " copied over to " << &C << endl << endl;

    C.print();

    cout << "Testing compy constructor..." << endl << endl;

    ArrayList<int> B(C);
    B.print();

    cout << "Removing elements..." << endl << endl;

    B.remove(2);
    B.print();

    B.remove(0);
    B.print();

    B.remove(2);
    B.print();

    B.remove(0);
    B.print();

    B.remove(0);
    B.print();

    try{
        B.remove(0);
        B.print();
     } 
     catch(std::out_of_range e) { cout << "Test exception caught..." << endl << endl; }

     cout << "Testing operator[]..." << endl << endl;

     cout << A[0] << endl;
     try{ A[A.size()]; } 
     catch(std::out_of_range e) { cout << "Test exception caught..." << endl << endl; }

     cout << "Large data case..." << endl;


     for(size_t i = 0; i < 10000; ++i) {
         B.insert(i % 10, i);
     }
     C = B;
     ArrayList<int> D(C);

     for(size_t i = 0; i < 10000; ++i) {
         D.remove(0);
     }

     D.print();

     cout << "ArrayLists tests complete." << endl;
}
