#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include "heap.h"

using std::vector;

template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<typename Container::value_type>>
class PriorityQueue {
    Container container;
    Compare compare;
    

    // TODO(student): implement PriorityQueue
    /*
    x PriorityQueue() - makes an empty priority queue using the default container (std::vector) and default comparator (std::less).
    explicit PriorityQueue(const Compare&) - makes an empty priority queue using the default container (std::vector) and specified comparator.
    explicit PriorityQueue(const Container&) - makes a priority queue using the specified container (which may not be empty and is not a heap) and default comparator (std::less).
    PriorityQueue(const Compare&, const Container&) - makes a priority queue using the specified container (which may not be empty and is not a heap) and the specified comparator.
    
    Iterators
    Optional
    
    Element Access
    x typename Container::const_reference top() const - return the top of this priority queue. Throw std::invalid argument if the queue is empty.
    
    Capacity
    x bool empty() const - returns true if this priority queue is empty
    x size_t size() const - returns the number of values in this priority queue
    
    Modifiers
    x void make_empty() - remove all values from this priority queue
    x void push(const typename Container::value_type&) - insert the given lvalue reference into this priority queue
    x void pop() - remove the top of this priority queue.  Does not throw any exceptions.
    
    Visualization
    x void print_queue(std::ostream&=std::cout) const - pretty print the queue as a comma-and-space separated list of values to the specified output stream (default std::cout), prints “<empty>\n” if this priority queue is empty. E.g. 1, 2, 4, 3, 6, 5, 11
    
    Optional
    PriorityQueue(const Compare& compare, Container&& container) - move constructs a priority queue using the specified comparator and container.
    PriorityQueue(const PriorityQueue&) - constructs a copy of the specified priority queue (using same container type and comparator)
    PriorityQueue(PriorityQueue&&) - move constructs a copy of the specified priority queue (using same container type and comparator)
    PriorityQueue& operator=(const PriorityQueue&) - assigns this priority queue to be a copy of the specified priority queue (with the same container type and comparator)
    PriorityQueue& operator=(PriorityQueue&&) - move assigns this priority queue to be a copy of the specified priority queue (with the same container type and comparator)
    ~PriorityQueue() - destroys this priority queue.
    x void push(typename Container::value_type&&) - insert the given value into this priority queue using move semantics
    */
   public:
    PriorityQueue() : container(Container{}), compare(Compare{}){}// - makes an empty priority queue using the default container (std::vector) and default comparator (std::less).
    explicit PriorityQueue(const Compare& c) : container(Container{}), compare(c) {
    }// - makes an empty priority queue using the default container (std::vector) and specified comparator.
    explicit PriorityQueue(const Container& c) : container(c), compare(Compare{}) {
        heapify(container, compare);
    }// - makes a priority queue using the specified container (which may not be empty and is not a heap) and default comparator (std::less).
    PriorityQueue(const Compare& cc, const Container& cv) : container(cv), compare(cc) {
        heapify(container, compare);
    }// - makes a priority queue using the specified container (which may not be empty and is not a heap) and the specified comparator.
    

    //Iterators
    //Optional
    
    //Element Access
    typename Container::const_reference top() const{ return heap_get_min(container);}// - return the top of this priority queue. Throw std::invalid argument if the queue is empty.
    
    //Capacity
    bool empty() const{return (container.size() < 2);}// - returns true if this priority queue is empty
    size_t size() const{return container.size();}// - returns the number of values in this priority queue
    
    //Modifiers
    void make_empty(){container.clear();}// - remove all values from this priority queue
    void push(const typename Container::value_type& val){
        heap_insert(container, val, compare);
    }// - insert the given lvalue reference into this priority queue
    void pop(){
        if(empty()){return;}
        heap_delete_min(container, compare);
    }// - remove the top of this priority queue.  Does not throw any exceptions.
    //Visualization
    void print_queue(std::ostream& os = cout) const{
        if(container.size() <2){os << "<empty>\n"; return;}
        for(size_t i = 1; i < container.size(); ++i){
            os << container.at(i);
            if(i != container.size() - 1){os << ", ";}
        }
        os << endl;
    }// - pretty print the queue as a comma-and-space separated list of values to the specified output stream (default std::cout), prints “<empty>\n” if this priority queue is empty. E.g. 1, 2, 4, 3, 6, 5, 11
    
    Container getContainer() const { return container;}
    Compare getCompare() const { return compare; }
    //Optional
    PriorityQueue(const Compare& compare, Container&& container){}// - move constructs a priority queue using the specified comparator and container.
    PriorityQueue(const PriorityQueue& other) : container(other.getContainer()), compare(other.getCompare()){}// - constructs a copy of the specified priority queue (using same container type and comparator)
    PriorityQueue(PriorityQueue&&){}// - move constructs a copy of the specified priority queue (using same container type and comparator)
    PriorityQueue& operator=(const PriorityQueue&){return *this;}// - assigns this priority queue to be a copy of the specified priority queue (with the same container type and comparator)
    PriorityQueue& operator=(PriorityQueue&&){}// - move assigns this priority queue to be a copy of the specified priority queue (with the same container type and comparator)
    ~PriorityQueue(){}// - destroys this priority queue.
    void push(typename Container::value_type&& val){typename Container::value_type valt = val; push(valt);}// - insert the given value into this priority queue using move semantics

};

#endif  // PRIORITY_QUEUE_H