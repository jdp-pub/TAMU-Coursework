#ifndef COLLECTION_H
#define COLLECTION_H

#include <cstddef>
#include <iostream>

template <typename Object>
class Collection {
    size_t sizel = 0;
    size_t cap = 1;
    Object* container = nullptr;
    void resize() {
        cap *= 2;
        Object* newcontainer = new Object[cap];
        for(size_t i = 0; i < sizel; ++i) {
            newcontainer[i] = container[i];
        }
        delete[] container;
        container = newcontainer;
    }

        public:

    Collection() { 
        container = new Object[cap];
    } // constructor

    Collection(const Collection& other) {
        container = new Object[cap];
        for(size_t i = 0; i < other.size(); ++i) {
            this->insert(other.containerVal(i));
        }
    } // copy constructor

    Collection& operator=(const Collection& other) {
        delete[] this->container;

        this->container = new Object[cap];
        this->sizel = 0;

        for(size_t i = 0; i < other.size(); ++i) {
            this->insert(other.containerVal(i));
        }

        return *this;
    } // copy assignement operator

    ~Collection() {
        delete[] container;
        container = nullptr;
        sizel = 0;
    } // destructor



    size_t size() const { return sizel; } // returns number of elements
    size_t capacity() const { return cap; } // returns the current limit of elements
    bool is_empty() const {return !(sizel); } // returns true if the collection is empty
    void make_empty() {
        delete[] this->container;
        this->cap = 1;
        this->container = new Object[cap];
        sizel = 0;
    } // empty collection

    void list() { 
        if(sizel == 0) {
            std::cout << "There are no objects in this collection." << std::endl;
        } 

        for(size_t i = 0; i < sizel; ++i) {
            std::cout << "Element in location " << i << " : {" << container[i] << "}" << std::endl; 
        }
    }

    void insert(const Object& obj) { // appends an Object to the end of the collection
        container[sizel] = obj;
        sizel++;
        if (sizel >= cap) { this->resize(); } 
    }

    void remove(const Object& obj) {
        if(this->contains(obj)) {
            for(size_t i = 0; i < this->sizel; ++i) {
                if(obj == container[i]) {
                    for(size_t j = i; j < this->sizel - 1; ++j) {
                        container[j] = container[j + 1];
                    }
                    break;
                }
            }

            --this->sizel;
        }
        else {
            std::cout << "Removal of object failed. Object " << obj << " does not exist in this collection." << std::endl;
        }
    } // removes an Object in the collection
    bool contains(const Object& obj) const {
        for(size_t i = 0; i < sizel; ++i) {
            if(obj == container[i]) { return true; }
        }
        return false;
    } // returns true if the object is in the collection

   Object containerVal(const size_t Index) const { return this->container[Index]; }
};

#endif  // COLLECTION_H