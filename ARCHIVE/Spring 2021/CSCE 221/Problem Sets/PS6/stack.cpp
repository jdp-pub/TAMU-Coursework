#include <iostream>
#include <list>

using std::cout, std::endl;

struct Node {
    int d = 0;
    Node* next = nullptr;
};

struct box {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* cursor = nullptr;

    int size = 0;


};

struct stack {
    Node* A[100] = {nullptr};
    box l1 = {};
    box l2 = {};
    box l3 = {};

    stack(){}
    ~stack(){
        for(size_t i = 0; i < 100; ++i) {
            delete A[i];
        }
    }

    void push1(int v) { 
        size_t i = 0;
        while(A[i] != nullptr) { ++i; } //something to iterate to the end of the list to store nodes
        
        A[i] = new Node;
        A[i]->d = v;
        if(l1.size == 0) {
            
            l1.head = A[i];
            l1.tail = A[i];
            ++l1.size;
            
        }   
        else {
            l1.tail->next = A[i];
            l1.tail = A[i];
            ++l1.size;
        }
        
    }
    void push2(int v) { size_t i = 0;
        while(A[i] != 0) { ++i; } //something to iterate to the end of the list to store nodes
        A[i] = new Node;
        A[i]->d = v;
        if(l2.size == 0) {
            l2.head = A[i];
            l2.tail = A[i];
            ++l2.size;
        }
        else {
            l2.tail->next = A[i];
            l2.tail = A[i];
            ++l2.size;
        }}

         void push3(int v) { size_t i = 0;
        while(A[i] != 0) { ++i; } //something to iterate to the end of the list to store nodes
        A[i] = new Node;
        A[i]->d = v;
        if(l3.size == 0) {
            l3.head = A[i];
            l3.tail = A[i];
            ++l3.size;
        }
        else {
            l3.tail->next = A[i];
            l3.tail = A[i];
            ++l3.size;
        }}

        void print() {
            for(size_t i =0; i < 100; ++i) {
                if(A[i] != 0) {
                    cout << A[i]->d << endl;
                }
            }
        }

        void print1() {
            l1.cursor = l1.head;
            for(size_t i=0; i < l1.size; ++i) {
                cout << l1.cursor->d << endl;
                l1.cursor = l1.cursor->next;
            }
        }

        void print2() {
            l2.cursor = l2.head;
            for(size_t i=0; i < l2.size; ++i) {
                cout << l2.cursor->d << endl;
                l2.cursor = l2.cursor->next;
            }
        }

        void print3() {
            l3.cursor = l3.head;
            for(size_t i=0; i < l3.size; ++i) {
                cout << l3.cursor->d << endl;
                l3.cursor = l3.cursor->next;
            }
        }
    
};

int main() {

    stack stuff;
    stuff.push1(1);
    stuff.push2(2);
    stuff.push3(10);
    stuff.push3(8);
    stuff.push1(4);
    stuff.push2(2);

    stuff.print();
    cout << endl << "contents of list 1" << endl;
    stuff.print1();

    cout << endl << "contents of list 2" << endl;
    stuff.print2();

    cout << endl << "contents of list 3" << endl;
    stuff.print3();
}