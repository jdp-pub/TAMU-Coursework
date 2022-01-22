#include <iostream>
#include "doubly_linked_list.h"

using std::cout, std::endl;

int main() {
    // TODO(student): test your code
    DoublyLinkedList<int> A;
    {
        cout << "Insert test..." << endl;

        
        A.insert(0, 1);
        A.print();
        A.insert(1, 2);
        A.print();
        A.insert(0, 3);
        A.print();
        A.insert(1, 4);
        A.print();
        A.insert(4, 5);
        A.print();
        A.insert(3, 6);
        A.print();

        try{ A.insert(10000, 5); }
        catch(std::out_of_range e) { cout << e.what() << endl;}
    } // TEST INSERT

    {
        cout << "Copy constructor test..." << endl;
        
        DoublyLinkedList<int> B(A);

        B.insert(0, 7);
        B.print();
        A.print();
    } //TEST COMPY CONSTRUCTOR

    {
        cout << "testing operator[]..." << endl;

        cout << A.size() << endl;
        
        for(size_t i = 0; i < A.size(); ++i) { cout <<"Element at position " << i << " : " <<  A[i] << endl; }
        try{ cout << A[100] << endl; }
        catch(std::out_of_range e) { cout << e.what() << endl; }

        for(size_t i = 0; i < A.size(); ++i) { 
            Node<int> newnode;
            newnode.setDatum(A[i]);
            cout <<"Element at position " << i << " : " << newnode.getDatum() << endl; 
        }
    }//operator[] tests

    {
        cout << "testing remove..." << endl;

        A.remove(0);
        A.print();
        A.remove(1);
        A.print();
        A.remove(2);
        A.print();
        A.remove(2);
        A.print();
        A.remove(0);
        A.print();
        A.remove(0);

        try{A.remove(0); }
        catch(std::out_of_range e) {cout << e.what() << endl; }
    } //rempve() tests

    {
        cout << "testing operator=..." << endl;
        DoublyLinkedList<int> B;
        B.insert(0, 3);
        B.insert(0, 2);
        B.insert(0, 1);

        B.print();

        A = B; //create list

        A.print();

        DoublyLinkedList<int> C;
        B = C; // erase a list
        B.print();
        C = B; // copy empty list
        C.print();

        B.insert(0, 3);
        B.insert(0, 2);
        B.insert(0, 1);

        C.insert(0, 4);
        C.insert(0, 4);
        C.insert(0, 4);

        A.insert(0,9);
        A.insert(0,8);
        A.insert(0,7);
        A.insert(0,6);
        A.insert(0,5);

        A.print();

        C = A; // smaller to larger
        C.print();
        A = B; // larger to smaller
        A.print();

        DoublyLinkedList<int> D = D;
        DoublyLinkedList<int> F(F);

        A = A;

    }
}