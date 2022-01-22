#include <iostream>
#include "stack.h"

int main() {
    // TODO(student): test your code
    Stack<int> A;
    {
        A.push(1);
        A.push(2);
        A.push(3);
        A.push(4);
        
    }
    A.print();
    std::cout << A.top() << std::endl;
    A.pop();
    A.print();

    try{
        A.pop();
        A.pop();
        A.pop();
        A.pop();
        A.pop();
    }
    catch(std::out_of_range &e) { std::cout << e.what() << std::endl; }
    try{ A.top(); }
    catch(std::out_of_range &e) { std::cout << e.what() << std::endl; }
    A.push(1);
        A.push(2);
        A.push(3);
        A.push(4);

    Stack<int> B(A);

    B.print();

    Stack<int> C;
    C = B;
    C.print();
}
