#include "tree_functions.h"

void nl(){ std::cout << std::endl;}

int main() {

    //start with a list in a specific order to warrant a double rotation
    vector<int> a = {3,1,2};

    //load list
    Tree b(a);
    b.print(b.getRoot()); // proof of a properly loaded binary tree

    nl();

    //since the purpose is to demonstrate the use of a rotation, a complete AVL tree is not implemented
    //this is a task specific function as an example of what an AVL tree would call under certain circumstances
    //this function also ignores balance, since the balance of this tree is known at the time of the function call
    //the "getRoot()" function would be a pointer to whichever node needed this rotation
    b.LR(b.getRoot()); 
    b.print(b.getRoot()); //proof of a proper LR rotation
}