#ifndef QUEUE_H
#define QUEUE_H

#include "array_list.h"
#include <iostream>

template <typename Object>
class Queue {
    // TODO(student): implement Queue
    ArrayList<Object> snakeLine = {};

    public:
    Queue() {}// - makes an empty stack
    //Rule of Three
    Queue(const Queue& other) {
        if(other.getSnake().size() == 0) {}
        else{
            snakeLine = other.getSnake();
        }
    }// - constructs a copy of the given queue
    ~Queue() {}// - destroys this queue
    Queue& operator=(const Queue& other) {
        if(other.getSnake().size() == 0) {}
        else{
            snakeLine = other.getSnake();
        }
        return *this;
    }// - assigns a copy of the given queue
    void enqueue(const Object& item) {snakeLine.insert(snakeLine.size(), item);}// - add the given object to the back of the queue
    Object dequeue() {Object temp = snakeLine[0]; snakeLine.remove(0); return temp;}// - remove and return the front element from the queue, or throw std::out_of_range if the queue is empty.
    Object& front() {return snakeLine[0];}// - return a reference to the element at the front of the queue or throw std::out_of_range if the queue is empty.

    ArrayList<Object> getSnake() const { return snakeLine; }
    void print() { 
      for(size_t i = 0; i < snakeLine.size(); ++i) {
         std::cout << snakeLine[i] << std::endl;
      }
    }
};

#endif  // QUEUE_H
