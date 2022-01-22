#include <iostream>
#include "binary_search_tree.h"

using std::cout, std::endl;

void nl() {cout << endl; }
void TestHeader(std::string name, size_t& number){
    cout << "~~~BEGIN TEST SEQUENCE " << number << " : " << name << "~~~" << endl;
    ++number;
    nl();
}
void TestFooter(){ cout << "~~~SEQUENCE COMPLETE~~~" << endl; }

template<typename Comparable>
void test(Comparable expected, Comparable testing, std::string name, std::string file, size_t line) {
    std::string RESULT;
    if(expected == testing) { RESULT = "PASS"; }
    else{ RESULT = "FAIL"; }
    cout << name << " : " << file << " line " << line << " : " << RESULT << endl
         << "EXPECTED " << expected << " : ACTUAL " << testing << endl;
         nl();

}

int main() {
    // TODO(student): write tests
    size_t num = 1;

    TestHeader("CONSTRUCTOR", num);
    BinarySearchTree<int> a;
    a.insert(2);
    a.insert(3);
    a.insert(1);
    test(2, a.getRoot()->getDatum(), "constructor, insert(), getters", "main.cpp", __LINE__);
    test(3, a.getRoot()->getRight()->getDatum(), "constructor, insert(), getters", "main.cpp", __LINE__);
    test(1, a.getRoot()->getLeft()->getDatum(), "constructor, insert(), getters", "main.cpp", __LINE__);

    BinarySearchTree<int> b(a);
    test(2, b.getRoot()->getDatum(), "copy constructor", "main.cpp", __LINE__);
    test(3, b.getRoot()->getRight()->getDatum(), "copy constructor", "main.cpp", __LINE__);
    test(1, b.getRoot()->getLeft()->getDatum(), "copy constructor", "main.cpp", __LINE__);

    BinarySearchTree<int> d;
    d = b;
    b = a;
    //cout << d.getRoot() << endl;
    test(3, d.getRoot()->getRight()->getDatum(), "operator=", "main.cpp", __LINE__);

    TestFooter();
    nl();

    

    TestHeader("PRINTING", num);
    b.print_tree(cout);
    nl();
    TestFooter();

    TestHeader("QUERY", num);
    test(1, b.find_min(), "find min", "main.cpp", __LINE__);
    test(3, b.find_max(), "find max", "main.cpp", __LINE__);

    try{
        BinarySearchTree<int> c;
        c.find_min();
    }
    catch(std::exception& e) { cout << e.what() << endl; }
    try{
        BinarySearchTree<int> c;
        c.find_max();
    }
    catch(std::exception& e) { cout << e.what() << endl; }
    nl();

    test(true, b.contains(3), "contains", "main.cpp", __LINE__);
    test(false, b.contains(9), "contains", "main.cpp", __LINE__);

    cout << "testing insertion {2,1,3,5,4,8,6,7,9}: " << endl;

    b.insert(5);
    b.insert(4);
    b.insert(8);
    b.insert(6);
    b.insert(7);
    b.insert(9);

    b.print_tree(cout);

    TestHeader("REMOVE", num);
    
    int n = 4;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    //cout <<"test" << endl;
    b.print_tree(cout);
    nl();
    
    n=8;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    //t();
    b.print_tree(cout);
    nl();
    
    n=5;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    //cout << b.getRoot()->getRight()->getRight()->getLeft()->getDatum() << endl;
    nl();
    
    n=9;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();
    
    n=2;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=3;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=1;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    cout << "reloading tree to seft left side {3,2,1,4,5}..." << endl;
    b.insert(3);
    b.insert(2);
    b.insert(1);
    b.insert(4);
    b.insert(5);

    b.print_tree(cout);

    n=2;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=1;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=3;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=6;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();


    
    n=4;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=5;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    b.print_tree(cout);
    nl();

    n=7;
    cout << "Removing " << n << "..." << endl;
    b.remove(n);
    //t();
    b.print_tree(cout);
    nl();

    TestFooter();

    
    

}
