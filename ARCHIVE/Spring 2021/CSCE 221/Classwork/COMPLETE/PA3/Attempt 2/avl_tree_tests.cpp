#include <iostream>
#include "avl_tree.h"

using std::cout, std::endl;

int main() {
    // TODO(student): write tests

    size_t num = 0;

    
    TestHeaderA("CONSTRUCTION",num);
    AVLTree<int> a;
    a.print_tree(cout);

    a.insert(10);
    a.print_tree();
    ssa();

    a.insert(12);
    a.print_tree();
    ssa();

    a.insert(17);
    a.print_tree();
    ssa();

    cout << "balance of " << a.getRoot()->getDatum()  << " "<< a.getBalance(a.getRoot()) << endl;
    cout << "height of " << a.getRoot()->getDatum()  << " "<< a.getRoot()->getHeight() << endl;
    
    a.insert(7);
    a.print_tree();
    ssa();
    a.insert(3);
    a.print_tree();
    ssa();

    a.insert(1);
    a.print_tree();
    ssa();

    a.insert(11);
    a.print_tree();
    ssa();

    a.insert(4);
    a.print_tree();
    ssa();
    a.insert(2);
    a.print_tree();
    ssa();
    a.insert(6);
    a.print_tree();
    ssa();
    

    

    
    int y = 0;
    for(int i = 0; i < 20000; ++i) {
        y = (y * i + 37) % 20000;
        cout << __LINE__ << ": inserting " << y << " iteration " << i << endl;
        a.insert(y);
    }
    for(int i = 0; i < 20000; ++i) {
        y = (y * i + 37) % 20000;
        cout << __LINE__ << ": inserting " << y << " iteration " << i << endl;
        a.insert(y);
    }
    for(int i = 0; i < 20000; ++i) {
        y = (y * i + 37) % 20000;
        testA(true, a.contains(y), "contains", "main.cpp", __LINE__);
        if(!a.contains(y)){break;}
    }
    
    a.print_tree(cout);
    
    AVLTree<int> fh = a;
    a.make_empty();
    a.remove(3);
    ssa();

    fh.print_tree(cout);
    //remove cases
    // root
    cout << "root: " << fh.getRoot()->getDatum() << endl;
    ssa();
    fh.remove(fh.getRoot()->getDatum());
    fh.print_tree(cout);
    cout << "root: " << fh.getRoot()->getDatum() << endl;
    ssa();

    //left leaf
    fh.remove(0);
    fh.print_tree(cout);
    ssa();

    //right leaf
    fh.remove(10);
    fh.print_tree(cout);
    ssa();

    
    //left w/right subtree
    fh.remove(9);
    fh.print_tree(cout);
    ssa();


    
    //right w/ right subtree
    fh.remove(132);
    fh.print_tree(cout);
    ssa();

    //right w/ left subtree
    fh.remove(150);
    fh.print_tree(cout);
    ssa();
    

   

    //right w/ two subtrees
    fh.remove(117);
    fh.print_tree(cout);
    ssa();

     //left w/ two subtrees
     fh.remove(117);
    fh.print_tree(cout);
    ssa();
    
    //left w/left subtree
    y = 0;
    for(int i = 0; i < 100; ++i) {
        y = (y * i + 37) % 200;
        cout << __LINE__ << ": removing " << y << " iteration " << i << endl;
        fh.remove(y);
    }

    fh.insert(10);
    fh.insert(11);
    fh.insert(5);
    fh.insert(2);

    fh.print_tree(cout);

    fh.remove(5);
    ssa();
    fh.print_tree(cout);
    


    a.insert(11);
    a.insert(10);
    a.insert(6);
    a.insert(12);

    a.print_tree(cout);
    ssa();
    
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
    cout << "Node balance: " << endl << a.getBalance(a.getRoot()) << endl;
    ssa();
    }

    a.remove(7);
    a.print_tree(cout);
    ssa();

    a = a;

    a.remove(2);
    a.print_tree(cout);
    ssa();

    a.remove(1);
    a.print_tree(cout);
    ssa();

    a.remove(6);
    a.print_tree(cout);
    ssa();

    a.remove(8);
    a.print_tree(cout);
    ssa();
    
    AVLTree<int> k;
    k.insert(1);
    k.insert(3);
    k.insert(2);
    k.print_tree(cout);
    cout << "Node balance: " << endl << k.getBalance(k.getRoot()) << endl;

    AVLTree<int> f;
    f.insert(3);
    f.insert(2);
    f.insert(1);
    f.print_tree(cout);
    cout << "Node balance: " << endl << f.getBalance(f.getRoot()) << endl;

    AVLTree<int> q;
    q.insert(3);
    q.insert(1);
    q.insert(2);
    q.print_tree(cout);
    cout << "Node balance: " << endl << q.getBalance(q.getRoot()) << endl;
    
    
    a.insert(10);
    a.insert(17);
    a.insert(5);
    cout << "Node balance: " << endl << a.getBalance(a.getRoot()) << endl;
    nla();

    a.print_tree(cout);

    ssa();
    
    int j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 3) % 23;
        cout << "inserting : " << j << endl;
        a.insert(j);
        a.print_tree(cout);
        cout << "Is the tree balanced?: " << a.getBalance(a.getRoot()) << endl;
        
        ssa();
    }
    cout << "{10, 17, 5 | 3, 6, 15, 2, 11, 12, /6, 22, 19, 4}" << endl;
    //a.print_tree(cout);
    nla();
    
    
    
    
    cout << "Max: " << a.find_max() << endl;
    cout << "Min: " << a.find_min() << endl;
    cout << "Contains 22: " << a.contains(22) << endl;
    cout << "Contains 34564: " << a.contains(34564) << endl;
    AVLTree<int> b(a);
    a.make_empty();
    a.print_tree(cout);
    ssa();
    try{a.find_max();}
    catch(std::invalid_argument& e){cout << e.what()<< endl;}
    try{a.find_min();}
    catch(std::invalid_argument& e){cout << e.what()<< endl;}
    
    
 
    ssa();
    b.print_tree(cout);
    ssa();
    AVLTree<int> c;
    AVLTree<int> d;
    
    a=b;//initialize new tree
    
    b=c;//erase full tree
    
    d=c;//copy empty tree to empty tree
    /////////////////////////////////////////////////////////

    a.print_tree(cout);
    cout << "Is the tree balanced?: " << a.getBalance(a.getRoot()) << endl;
    ssa();
    b.print_tree(cout);
    cout << "Is the tree balanced?: " << b.getBalance(b.getRoot()) << endl;
    ssa();
    c.print_tree(cout);
    cout << "Is the tree balanced?: " << c.getBalance(c.getRoot()) << endl;
    ssa();
    d.print_tree(cout);
    cout << "Is the tree balanced?: " << d.getBalance(d.getRoot()) << endl;

    TestFooterA();
    TestHeaderA("DESTRUCTION",num);
    
    a.print_tree(cout);
    nla();
    ssa();
    cout << "{10, 17, 5 | 3, 6, 15, 2, 11, 12, /6, 22, 19, 4}" << endl;
    j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 3) % 23;
        cout << "Removing " << j << "..." << endl;
        a.remove(j);
        
        a.print_tree(cout);
        cout << "Is the tree balanced?: " << a.getBalance(a.getRoot()) << endl;
        ssa();

    }
    
    a.print_tree(cout);
    ssa();

    a.remove(10);
    a.print_tree(cout);

    ssa();

    a.remove(5);
    a.print_tree(cout);

    ssa();

    a.remove(17);
    a.print_tree(cout);
    
    
    j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 5) % 13;
        a.insert(j);
    }

    ssa();

    a.print_tree(cout);

    ssa();

    a.remove(10);
    a.print_tree(cout);

    ssa();

    a.remove(0);
    a.print_tree(cout);

    ssa();

    a.remove(3);
    a.print_tree(cout);

    ssa();

    a.remove(12);
    a.print_tree(cout);

    a.insert(1);

    ssa();

    a.remove(2);
    a.print_tree(cout);
    TestFooterA();

    TestHeaderA("BALANCING", num);

    j = 1;
    for(int i = 0; i < 10; ++i) {
        j = (j*i + 5) % 13;
        a.insert(j);
    }
    
    ssa();
    a.print_tree(cout);
    ssa();

    cout << a.getRoot()->getHeight() << endl;
    ssa();
    for(int i = 20; i < 30; i+=3) {
        cout << "Inserting " << i << "..." << endl;
        a.insert(i);
        a.print_tree(cout);
        ssa();
    }
    for(int i = 19; i < 29; i+=3) {
        cout << "Inserting " << i << "..." << endl;
        a.insert(i);
        a.print_tree(cout);
        ssa();
    }
    
    for(int i = 18; i < 28; i+=3) {
        cout << "Inserting " << i << "..." << endl;
        a.insert(i);
        a.print_tree(cout);
        ssa();
    }

    ssa();
    a.print_tree(cout);
    ssa();
    
    ssa();
    TestFooterA();
    TestHeaderA("LARGE DATA CASE", num);
    AVLTree<int> r;
    r.insert(4);
    r.insert(5);
    r.insert(6);
    cout << "Is the tree balanced?: " << a.getBalance(a.getRoot()) << endl;
    r.print_tree(cout);

    ssa();
    r.insert(3);
    r.print_tree(cout);
    ssa();
    
    r.insert(2);
    r.print_tree(cout);
    ssa();
    
    r.insert(1);
    r.print_tree(cout);

    for(int i = 30; i < 50; i+=1) {
        cout << "Inserting " << i << "..." << endl;
        r.insert(i);
        ssa();
    }
    
    r.print_tree(cout);
    cout << "Is the tree balanced?: "<< endl << r.getBalance(r.getRoot()) << endl;
    for(int i = 10; i < 30; i+=1) {
        cout << "Inserting " << i << "..." << endl;
        r.insert(i);
        ssa();
    }
    
    //r.print_tree(cout);
    AVLTree<int> h;
    //cout << "Is the tree balanced?: "<< endl << r.getBalance(r.getRoot()) << endl;
     j = 1;
    for(int i = 0; i < 200; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i + 1 << " of 200" << endl;
        cout << "Inserting " << j << "..." << endl;
        h.insert(j);
        ssa();
    }
    h.print_tree(cout);
    cout << "Is the tree balanced?: "<< endl << h.getBalance(h.getRoot()) << endl;
    ssa();
    
    //a=k;
    
    AVLTree<int> p(a);
    cout << "Max: " << p.find_max() << endl;
    cout << "Min: " << p.find_min() << endl;
    cout << "Contains 485: " << p.contains(485) << endl;
    cout << "Contains 34564: " << p.contains(34564) << endl;
    a.make_empty();
    
    AVLTree<int> t(h);
    //t.insert(8);
    //a.insert(8);
    //a.print_tree(cout);
    t.print_tree(cout);
    ssa();
    //p.print_tree(cout);
    //ssa();

    j = 1;
    for(int i = 0; i < 100; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i + 1 << " of 100" << endl;
        cout << "removing " << j << "..." << endl;
        h.remove(j);
        ssa();
    }

    j = 1;
    for(int i = 0; i < 200; i+=1) {
        j = (i * j + 97) % 100 ;
        if(i < 100) {continue;}
        cout << "Iteration " << i << " of 100" << endl;
        cout << "removing " << j << "..." << endl;
        t.remove(j);
        ssa();
    }

    h = t;
    
    j = 1;
    for(int i = 100; i < 200; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i - 100 << " of 100" << endl;
        cout << "Inserting " << j << "..." << endl;
        t.insert(j);
        ssa();
    }
    j=1;
    for(int i = 101; i < 201; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i - 101 << " of 100" << endl;
        cout << "Inserting " << j << "..." << endl;
        h.insert(j);
        ssa();
    }

    h=h;

    j=1;
    for(int i = 150; i < 250; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i - 100 << " of 100" << endl;
        cout << "Inserting " << j << "..." << endl;
        h.insert(j);
        ssa();
    }
    j=1;
    for(int i = 150; i < 250; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i - 100 << " of 100" << endl;
        cout << "removing " << j << "..." << endl;
        h.remove(j);
        ssa();
    }

    h.print_tree(cout);
    ssa();
    
    
    j = 1;
    k.remove(1);
    k.remove(3);
    
    k.remove(2);
    k.print_tree();
    for(int i = 0; i < 100; i+=1) {
        j = (i * j + 97) % 100 ;
        cout << "Iteration " << i + 1 << " of 100" << endl;
        cout << "Removing " << j << "..." << endl;
        k.remove(j);
    }
    k.print_tree(cout);
    cout << "Is the tree balanced?: "<< endl << k.getBalance(k.getRoot()) << endl;
    ssa();
    k.print_tree();
    
    TestFooterA();
    
    
}
