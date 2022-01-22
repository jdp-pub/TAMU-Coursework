#include <cstddef>
#include <iostream>
#include "collection.h"

using std::cout, std::endl;

int main() {

    /* 
    FUNCTIONS TO TEST

    Collection(const Collection&); // COMPLETE
    ~Collection(); //COMPLETE
    Collection& operator=(const Collection&); // COMPLETE
    size_t size() const; //COMPLETE
    bool is_empty() const; //COMPLETE
    void make_empty(); //COMPLETE
    void insert(const Object& obj); //COMPLETE
    void remove(const Object& obj); // COMPLETE
    bool contains(const Object& obj) const; //COMPLETE

    */
    Collection<int> A;

    /*BASE EXAMPLE*/
    {
        cout << "~~~TEST 1: EXAMPLE~~~" << endl;
        cout << endl;

        A.list();
        cout << "Loading Collection of int {A}..." << endl;
        cout << endl;

        A.insert(8);
        A.insert(6);
        A.insert(7);
        A.insert(5);
        A.insert(3);
        A.insert(0);
        A.insert(9);

        A.list();
        cout << endl;

        cout << "Removing first element..." << endl;
        A.remove(8);
        cout << endl;

        A.list();
        cout << endl;

        cout << "Empty? : " << A.is_empty() << endl;
        cout << "Emptying list..." << endl;
        A.make_empty();

        cout << "Empty? : " << A.is_empty() << endl;
        A.list();
    }

    /* UNIT CASES */
    {
        cout << "~~~TEST 2: UNIT CASES~~~" << endl;
        cout << endl;

        cout << "Initializing Collection A..." << endl;
        for(size_t i = 0; i < 1000; ++i) {
            A.insert(i);
        }

        cout << "Initializing Collection B(A)..." << endl;
        Collection<int> B(A);
        Collection<int> C;

        cout << "Initializing Collection C = B..." << endl;
        C = B;

        cout << endl;

        cout << "Pointer to A : " << &A << endl;
        cout << "Pointer to B : " << &B << endl;
        cout << "Pointer to C : " << &C << endl;

        cout << endl;

        cout << "Size of A : " << A.size() << endl;
        cout << "Size of B : " << B.size() << endl;
        cout << "Size of C : " << C.size() << endl;

        cout << endl;

        cout << "Emptying A..." << endl;
        A.make_empty();

        cout << "Removing values mod 2 from B..." << endl;
        for(size_t i = 0; i < B.size(); ++i) {
            if(B.containerVal(i) % 2 == 0) {
                B.remove(B.containerVal(i));
            }
        }

        cout << endl;


        cout << "Size of A : " << A.size() << endl;
        cout << "Size of B : " << B.size() << endl;
        cout << "Size of C : " << C.size() << endl;

        cout << endl;

        cout << "Contents of A..." << endl << "Size : " << A.size() << endl << "Capacity : " << A.capacity() << endl;
        A.list();
        cout << endl;

        cout << "Contents of B..." << endl << "Size : " << B.size() << endl << "Capacity : " << B.capacity() << endl;
        for(size_t i = 0; i < 10; ++i) {
            cout << "Element in location " << i << " : {" << B.containerVal(i) << "}" << endl; 
        }

        cout << endl;
        cout << "Removing even value from B..." << endl;
        B.remove(2);
        cout << endl;

        cout << "Contents of C..." << endl << "Size : " << C.size() << endl << "Capacity : " << C.capacity() << endl;
        for(size_t i = 0; i < 10; ++i) {
            cout << "Element in location " << i << " : {" << C.containerVal(i) << "}" << endl; 
        }

        cout << endl;

    }

    cout << "~~~ALL TESTS COMPLETE~~~" << endl;

}