#include <iostream>

using std::cout, std::endl;

class Node {
    int data = 0;
    Node* nex = nullptr;

    Node(int d) {
        data = d;
    }

    public:
    int datums() const {return this->data;}
    Node* next() const {return this->nex;}
    void setNext(Node* n) {nex = n;}
    void setDatum(int n) {data = n;}
};


class box {

    Node* head = nullptr;
    size_t elements = 0; // keeps tack of number of pointers in linked list.

    box();
    ~box(); // in the problem these are already implemented properly

    public:

    int size() const {return elements;} //part a
    
    void print() const { //part b
    Node* cursor = head;
        for(size_t i = 0; i < elements; ++i) {
            cout << "Element " << i << " contains : " << cursor->datums() << "at position : " << cursor << endl; //print current element
            cursor = cursor->next(); // iterate through every element
        }
        cursor = nullptr; 
    }

    bool contains(int test) { //part c
        Node* cursor = head;
        for(size_t i = 0; i < elements; ++i) {
            if(test == cursor->datums()) {return true;} //returns trus if test is ever found, returns false in all other cases
            cursor = cursor->next(); // iterate through every element
        }
        return false;
        cursor = nullptr; 
    }

    void insert(int val) { //part d, assuming list is sorted with smallest element at the head node
        if(!contains(val)) {
            Node* cursor = head->next();
            Node* previous = head;
            for(size_t i = 0; i <= elements; ++i) {
                if(head == nullptr) {
                    //zero element list
                    Node* newnode;
                    newnode->setDatum(val);
                    head = newnode; //attaches node to front, repositions head
                    ++elements; //increments reported size of list
                    break;
                }
                if(cursor == nullptr && previous->datums() < val) {
                    //insert at end of one element list
                    Node* newnode;
                    newnode->setDatum(val);
                    previous->setNext(newnode);
                    ++elements; //increments reported size of list
                    break;
                }
                if(previous->datums() > val) {
                    //insert at head
                    Node* yesnode;
                    yesnode->setDatum(val);
                    yesnode->setNext(previous);
                    head = yesnode;
                    ++elements; //increments reported size of list
                    break;
                }
                if(cursor->datums() >= val && previous->datums() <= val) {
                    //insert before cursor, after previous
                    Node* nonode;
                    nonode->setDatum(val);
                    nonode->setNext(cursor);
                    previous->setNext(nonode);
                    ++elements; //increments reported size of list
                    break;
                }
                if(cursor->next() == nullptr) {
                    //insert at end
                    Node* newnode;
                    newnode->setDatum(val);
                    cursor->setNext(newnode);
                    ++elements; //increments reported size of list
                    break;
                }
                previous = cursor;
                cursor = cursor->next();
            }
            cursor = nullptr;
            previous = nullptr;
        }
    }

    void remove(int val) { // part e

        if(contains(val)) {
            Node* cursor = head->next();
                Node* previous = head;
                for(size_t i = 0; i <= elements; ++i) {
                    if(elements == 1) {
                        //one element list
                        delete head;
                        head == nullptr;
                        --elements; //increments reported size of list
                        break;
                    }
                    if(cursor->datums() == val) {
                        //delete in middle
                        previous->setNext(cursor->next());
                        delete cursor;
                        --elements; //increments reported size of list
                        break;
                    }
                    if(cursor->next() == nullptr) {
                        break; // prevents trying to read from the nullptr
                    }
                    previous = cursor;
                    cursor = cursor->next();
                }
                cursor = nullptr;
                previous = nullptr;
        }
    }

    // PROBLEM 2 A
    void printReverse() const {
        for(int i = elements; i >= 0; --i) { //establishes where the end of the list is
            Node* cursor = head; 
            for(int c = 0; c <= i; ++c) {// iterates to the end of the list
                cursor = cursor->next();
            }
            cout << "Element " << i << " contains : " << cursor->datums() << "at position : " << cursor << endl; // prints last element
        }
    }


};