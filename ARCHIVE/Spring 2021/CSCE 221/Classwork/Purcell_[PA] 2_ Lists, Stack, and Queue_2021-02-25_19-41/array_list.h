#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <iostream>

template <typename Object>
class ArrayList {
    
    size_t capacity = 1;
    size_t head = 0;
    size_t sizel = 0;
    Object* listReserve = new Object[capacity];

    void resize() {
        
        if (sizel >= capacity) {
            this->capacity *= 2;
            Object* temp = new Object[capacity];
            for(size_t i = 0; i < sizel; ++i) {
                temp[i] = listReserve[i + head];
            }
            delete[] listReserve;
            listReserve = temp;
        }
    }

    public:
    ArrayList() {}
    explicit ArrayList(size_t newCapacity) {
        delete[] listReserve;
        capacity = newCapacity;
        listReserve = new Object[capacity];
    }

    // Rule of three
    
    
    ArrayList(const ArrayList& other) {
        delete[] listReserve;
        capacity = other.capacity;
        sizel = other.size();
        listReserve = new Object[capacity];

        for(size_t i = 0; i < other.size(); ++i) {
            listReserve[i] = other.element(i);
        }
    }
    ~ArrayList() { delete[] listReserve; }
    ArrayList& operator=(const ArrayList& other){
        if(listReserve != other.getPtr()){
        delete[] listReserve;
        capacity = other.capacity;
        sizel = other.size();
        listReserve = new Object[capacity];

        for(size_t i = 0; i < other.size(); ++i) {
            listReserve[i] = other.element(i);
        }
        }
        return *this;
    } //- assigns a copy of the given list


    //SETTERS
    Object& operator[](size_t index) { 
        try { if(index >= sizel) { throw 1; }}
        catch(int n) { throw std::out_of_range("operator[] function call, requested index out of range..."); }
        return this->listReserve[index + head]; }//- returns a reference to the element at the specified index or throws std::out_of_range if the index is out of bounds.
    void insert(size_t index, const Object& val) {
        try { if(index > sizel) { throw 1; }}
        catch(int n) { throw std::out_of_range("Insert function call, requested index out of range..."); }

        ++sizel;
        this->resize();

        for(size_t i = sizel + head - 1; i >= 0; --i) {
            listReserve[i + 1] = listReserve[i];
            if(i == index + head) {
                listReserve[i] = val;
                break;
            }
        }

     }// - insert the given object at the specified index or throws std::out_of_range if the index is out of bounds
    void remove(size_t index) { 
        try{ if(index >= sizel) {throw 1; }}
        catch(int n) { throw std::out_of_range("Remove function call, requested index out of range..."); }
        for(size_t i = index + head; i < sizel - 1; ++i) {
            listReserve[i] = listReserve[i+1];
        }
        --sizel;
    }//- remove the object at the specified index or throws std::out_of_range if the index is out of bounds


    //GETTERS
    Object element(size_t index) const { return listReserve[this->head + index]; }
    size_t size() const { return this->sizel; }
    void print() const {
        std::cout << "List Properties..." << std::endl
             << "Capacity: " << this->capacity << std::endl
             << "Size: " << this->sizel << std::endl << std::endl;
        for(size_t i = 0; i < this->sizel; ++i) {
            std::cout << "Element " << i << " : " << this->element(i) << std::endl;
        }
        std::cout << std::endl;
    }

    Object* getPtr()  const {return listReserve; }


};

#endif  // ARRAY_LIST_H