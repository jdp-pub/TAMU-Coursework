#include "tree_functions.h"

int main() {
    

    vector<int> b = {7, 10, 2, 4, 5, 11, 1, 8, 9, 6, 12, 3};

    Tree a(b);
    a.print(a.getRoot());

    cout << endl;

    cout << "Number of nodes : " << a.countNodes(a.getRoot()) << endl << endl;

    cout << "Number of leaves : " << a.countLeaves(a.getRoot()) << endl << endl;

    cout << "Number of full nodes : " << a.countFull(a.getRoot()) << endl << endl;
}