#include <iostream>
#include "binary_search_tree.h"

using std::cout, std::endl;

int main() {
    // TODO(student): write tests

      size_t num = 0;
    
    TestHeader("CONSTRUCTION",num);
    BinarySearchTree<int> a;
    a.insert(7);
    a.insert(3);
    a.insert(2);
    a.insert(1);
    a.insert(9);
    a.insert(8);
    a.insert(5);
    a.insert(4);
    a.insert(11);
    a.insert(10);
    a.insert(6);
    a.insert(12);

    a.print_tree(cout);
     ss();

    a.remove(7);
    a.remove(8);
    a.remove(9);
    a.remove(10);
    a.remove(11);
    a.remove(12);

    a.print_tree(cout);

    
    for(int i = 0; i < 10; ++i) {
        a.insert(i);
        a.print_tree(cout);
     ss();
    }

    a.remove(7);
    a.print_tree(cout);
     ss();

    a = a;
    a.remove(2);
    a.print_tree(cout);
     ss();

    a.remove(1);
    a.print_tree(cout);
     ss();

    a.remove(6);
    a.print_tree(cout);
     ss();

    a.remove(8);
    a.print_tree(cout);
     ss();
    
    BinarySearchTree<int> k;
    k.insert(1);
    k.insert(3);
    k.insert(2);
    k.print_tree(cout);

    BinarySearchTree<int> f;
    f.insert(3);
    f.insert(2);
    f.insert(1);
    f.print_tree(cout);

    BinarySearchTree<int> q;
    q.insert(3);
    q.insert(1);
    q.insert(2);
    q.print_tree(cout);
     ss(); 
    
    
    a.insert(10);
    a.insert(17);
    a.insert(5);
     ss();
     nl();

    a.print_tree(cout);

     ss();
    
    int j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 3) % 23;
        cout << "inserting : " << j << endl;
        a.insert(j);
        a.print_tree(cout);
         
        
         ss();
    }
    cout << "{10, 17, 5 | 3, 6, 15, 2, 11, 12, /6, 22, 19, 4}" << endl;
    //a.print_tree(cout);
    nl();
    
    
    
    
    cout << "Max: " << a.find_max() << endl;
    cout << "Min: " << a.find_min() << endl;
    cout << "Contains 22: " << a.contains(22) << endl;
    cout << "Contains 34564: " << a.contains(34564) << endl;
    BinarySearchTree<int> b(a);
    a.make_empty();
    a.print_tree(cout);
     ss();
    try{a.find_max();}
    catch(std::invalid_argument& e){cout << e.what()<< endl;}
    try{a.find_min();}
    catch(std::invalid_argument& e){cout << e.what()<< endl;}
    
    
 
     ss();
    b.print_tree(cout);
     ss();
    BinarySearchTree<int> c;
    BinarySearchTree<int> d;
    ;
    a=b;//initialize new tree
    ;
    b=c;//erase full tree
    ;
    d=c;//copy empty tree to empty tree
    /////////////////////////////////////////////////////////

    a.print_tree(cout);
     
     ss();
    b.print_tree(cout);
     ss();
    c.print_tree(cout);
     ss();
    d.print_tree(cout);

    TestFooter();
    TestHeader("DESTRUCTION",num);
    
    a.print_tree(cout);
    nl();
     ss();
    cout << "{10, 17, 5 | 3, 6, 15, 2, 11, 12, /6, 22, 19, 4}" << endl;
    j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 3) % 23;
        cout << "Removing " << j << "..." << endl;
        a.remove(j);
        
        a.print_tree(cout);
         
         ss();

    }
    a.print_tree(cout);
     ss();

    a.remove(10);
    a.print_tree(cout);

     ss();

    a.remove(5);
    a.print_tree(cout);

     ss();

    a.remove(17);
    a.print_tree(cout);
    
    
    j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 5) % 13;
        a.insert(j);
    }

     ss();

    a.print_tree(cout);

     ss();

    a.remove(10);
    a.print_tree(cout);

     ss();
    a.remove(0);
    a.print_tree(cout);

     ss();

    a.remove(3);
    a.print_tree(cout);

     ss();

    a.remove(12);
    a.print_tree(cout);

    a.insert(1);

     ss();

    a.remove(2);
    a.print_tree(cout);
    TestFooter();

    TestHeader("LARGE DATA CASE", num);
    BinarySearchTree<int> r;
    r.insert(4);
    r.insert(5);
    r.insert(6);
     
    r.print_tree(cout);

     ss();
    r.insert(3);
    r.print_tree(cout);
     ss();
    
    r.insert(2);
    r.print_tree(cout);
     ss();
    
    r.insert(1);
    r.print_tree(cout);

    for(int i = 30; i < 50; i+=1) {
        cout << "Inserting " << i << "..." << endl;
        r.insert(i);
         ss();
    }
    
    r.print_tree(cout);
    for(int i = 10; i < 30; i+=1) {
        cout << "Inserting " << i << "..." << endl;
        r.insert(i);
         ss();
    }
    
    r.print_tree(cout);
    j = 1;
    for(int i = 0; i < 100; i+=1) {
        j = (i * j + 97) % 1000 ;
        cout << "Iteration " << i + 1 << " of 100" << endl;
        cout << "Inserting " << j << "..." << endl;
        k.insert(j);
         ss();
    }
    k.print_tree(cout);
     ss();
    
    a=k;
    
    BinarySearchTree<int> p(a);
    cout << "Max: " << p.find_max() << endl;
    cout << "Min: " << p.find_min() << endl;
    cout << "Contains 485: " << p.contains(485) << endl;
    cout << "Contains 34564: " << p.contains(34564) << endl;
    a.make_empty();
    
    BinarySearchTree<int> t(a);
    t.insert(8);
    a.insert(8);
    
    a.print_tree(cout);
    t.print_tree(cout);
     ss();
    p.print_tree(cout);
     ss();

    k.print_tree(cout);
     ss();

    j = 1;
    k.remove(1);
    k.remove(3);
    
    k.remove(2);
    
    k.print_tree();
    for(int i = 0; i < 100; i+=1) {
        j = (i * j + 97) % 1000 ;
        cout << "Iteration " << i + 1 << " of 100" << endl;
        cout << "Removing " << j << "..." << endl;
        k.remove(j);
    }
    k.print_tree(cout);

    ss();

    k.print_tree();
    
    TestFooter();
    
}
