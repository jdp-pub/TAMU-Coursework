#include <iostream>
#include "queue.h"

int main() {
    // TODO(student): test your code
    Queue<int> A;
    
        A.enqueue(1);
        A.enqueue(2);
        A.enqueue(3);
        A.enqueue(4);
        
    
    A.print();
    std::cout << A.front() << std::endl;
    std::cout << A.dequeue() << std::endl;
    A.print();

    try{
        A.dequeue();
        A.dequeue();
        A.dequeue();
        A.dequeue();
        A.dequeue();
    }
    catch(std::out_of_range &e) { std::cout << e.what() << std::endl; }
    try{ A.front(); }
    catch(std::out_of_range &e) { std::cout << e.what() << std::endl; }
    A.enqueue(1);
        A.enqueue(2);
        A.enqueue(3);
        A.enqueue(4);

    Queue<int> B(A);

    B.print();

    Queue<int> C;
    C = B;
    C.print();
}
