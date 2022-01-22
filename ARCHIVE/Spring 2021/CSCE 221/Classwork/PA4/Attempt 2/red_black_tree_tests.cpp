#include "red_black_tree.h"

using std::cout, std::endl;

int main() {  
    // TODO(student): write at least 1000 lines of test
//int x;
    /* UNIT TEST TODO LIST
        RED BLACK TREE 

        Constructors
        RedBlackTree() COMPLETE
        RedBlackTree(const RedBlackTree&) TEST
        ~RedBlackTree() COMPLETE
        RedBlackTree& operator=(const RedBlackTree&) TEST
        //////////////////////////////////////////////////////////

        Element Access
        N/A
        ////////////////////////////////////////////

        Iterators
        Optional
        /////////////////////////////////////////////////////////

        Capacity
        Optional
        /////////////////////////////////////////////////////////

        Modifiers
        void insert(const Comparable&) COMPLETE
        void remove(const Comparable&) 
        /////////////////////////////////////////////////////////////

        Lookup
        bool contains(const Comparable&) const COMPLETE
        const Comparable& find_min() const COMPLETE
        const Comparable& find_max() const COMPLETE
        Node* find_max(Node* cursor) const COMPLETE
        Node* find_min(Node* cursor) const COMPLETE
        Node* find(const Comparable& val) const COMPLETE
        Node* findNextSmallest(Node* pin) COMPLETE
        Node* findNextLargest(Node* pin) CPMPLETE
        Node* findParent(Node* pin) LEGACY::REFACTOR FOR DELETION
        /////////////////////////////////////////////////////////////

        Visualization
        Optional, but strongly recommended.
        ////////////////////////////////////////////////////////////////////

        For Testing
        int color(const Node* node) const 
        const Node* get_root() const 
        const Node* getRoot() const COMPLETE
        Node* getDummy() const COMPLETE
        /////////////////////////////////////////////////////////////////////

        Optional
        RedBlackTree(RedBlackTree&&) - move constructs a copy of the given (rvalue) tree
        RedBlackTree& operator=(RedBlackTree&&) - move assigns a copy of the given (rvalue) tree
        bool is_empty() const - returns Boolean true if the tree is empty
        void empty(Node* cursor) COMPLETE
        void make_empty() 350:COMPLETE
        void print_tree(std::ostream&=std::cout) const COMPLETE
        void reverse_inorder(std::ostream& os, Node* cursor, size_t indent) const COMPLETE
        void inorder() COMPLETE
        void LL(Node* pin) right rotation//MAY RETHREAD IMPROPERLY IN CERTAIN CASES, REQUIRES MORE TESTING
        void RR(Node* pin) left rotation //MAY RETHREAD IMPROPERLY IN CERTAIN CASES, REQUIRES MORE TESTING
        void rebalance(Node* pin) INCORRECT COLOR ASSIGNMENT
        void init_copy(Node* CursorSelf, Node* CursorOther)
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        NODE

        Node(){}
        Node(Comparable x)
        Node(Node& x)
        Node& operator=(const Node other)
        ~Node()

        //setters
        void setRight(Node* right)
        void setLeft(Node* left)
        void setParent(Node* p)
        void setDatum(const Comparable x)
        void flipColor()
        void setColor(Color c)
        void setLeftT(bool T)
        void setRightT(bool T)
        void setLeaf()
        

        //getters
        Node* getRight()  const
        Node* getLeft() const
        Node* getParent() const
        Color getColor() const
        bool getLeftT() const
        bool getRightT() const
        Comparable getDatum() const
        Comparable& getDatum()
    */

    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
 {   
     /*
    RedBlackTree<int> a; //initial thread testing, preparing for iterative tree traversal. establishes bst
    int x = 0;
    a.insert(10);

    a.nodeInfo(a.getDummy());
    a.nodeInfo(a.getRoot());
    a.print_tree();
    cout << "dfsdfsdf" << endl;
    a.insert(12);
    a.nodeInfo(a.find(12));
    a.nodeInfo(a.getDummy());
    a.nodeInfo(a.getRoot());

    a.insert(11);
    a.insert(13);
    a.insert(14);
    a.insert(9);
    a.insert(8);
    a.insert(5);
    a.insert(4);
    a.insert(3);
    a.insert(2);
    
    a.find(12)->setColor(RedBlackTree<int>::BLACK);
    a.find(10)->setColor(RedBlackTree<int>::RED);
    a.insert(14);
    */

/*
    cout << "root info: " << endl;
    cout << a.getRoot()->getDatum() << endl;
    cout << a.getRoot()->getLeft() << endl;
    cout << a.getRoot()->getLeftT() << endl;
    cout << a.getRoot()->getRight() << endl;
    cout << a.getRoot()->getRightT() << endl;
    cout << a.getRoot()->getParent() << endl;

    a.insert(5);
    a.nodeInfo(a.find(5));
    a.print_tree();
    cout << "5 info: " << endl;
    cout << "Left child: " << a.find(x)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.find(x)->getLeftT() << endl;
    cout << "Right child: " << a.find(x)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.find(x)->getRightT() << endl;
    cout << "Parent: " << a.find(x)->getParent()->getDatum() << endl;
    cout << endl;

    cout << "~~~~~~~~~~~~~~~~~~" << endl;

    cout << "root info: " << endl;
    cout << "Left child: " << a.getRoot()->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.getRoot()->getLeftT() << endl;
    cout << "Right child: " << a.getRoot()->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.getRoot()->getRightT() << endl;
    cout << "Parent: " << a.getRoot()->getParent()->getDatum() << endl;

    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    x=15;
    a.insert(x);
    cout << "15 info: " << endl;
    cout << "Left child: " << a.find(x)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.find(x)->getLeftT() << endl;
    cout << "Right child: " << a.find(x)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.find(x)->getRightT() << endl;
    cout << "Parent: " << a.find(x)->getParent()->getDatum() << endl;
    cout << endl;

    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    x=11;
    a.insert(x);
    cout << "11 info: " << endl;
    cout << "Left child: " << a.find(x)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.find(x)->getLeftT() << endl;
    cout << "Right child: " << a.find(x)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.find(x)->getRightT() << endl;
    cout << "Parent: " << a.find(x)->getParent()->getDatum() << endl;
    cout << endl;

    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    x=6;
    a.insert(x);
    cout << "6 info: " << endl;
    cout << "Left child: " << a.find(x)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.find(x)->getLeftT() << endl;
    cout << "Right child: " << a.find(x)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.find(x)->getRightT() << endl;
    cout << "Parent: " << a.find(x)->getParent()->getDatum() << endl;
    cout << endl;

    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    x=3;
    a.insert(x);
    cout << "3 info: " << endl;
    cout << "Left child: " << a.find(x)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << a.find(x)->getLeftT() << endl;
    cout << "Right child: " << a.find(x)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << a.find(x)->getRightT() << endl;
    cout << "Parent: " << a.find(x)->getParent()->getDatum() << endl;
    cout << endl;

    a.print_tree();
    a.inorder();

    int j = 1;
    for(int i = 0; i < 100 ; ++i){
        j = (j * i + 97) % 200;
        a.insert(j);
    }
    for(int i = 0; i < 100 ; ++i){
        a.insert(i);
    }
    */
    //a.print_tree();
    //a.inorder();
}
    
   {
      /* RedBlackTree<int> e;
       e.insert(6);
       e.insert(4);
       e.insert(2);
       e.insert(8);
       e.insert(10);

       cout << e.contains(4) << endl;
       cout << e.contains(7) << endl;

        e.print_tree();
        e.inorder();
       e.remove(4);

       e.print_tree();
        e.inorder();

        RedBlackTree<int> d(e);
        d.remove(10);
        
        e.nodeInfo(e.get_root());
        e.print_tree();
        e.inorder();

        d.nodeInfo(d.get_root());
        d.print_tree();
        d.inorder();

        e = d;

        e.nodeInfo(e.get_root());
        e.print_tree();
        e.inorder();

        d.nodeInfo(d.get_root());
        d.print_tree();
        d.inorder();
        */
   }

   /*
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    
   
    size_t num = 1;
    TestHeader("RED BLACK INSERTION", num);
    RedBlackTree<int> b;
    int y = 4;
    b.insert(y);
        y = 8;
    b.insert(y);
    y = 10;
    b.insert(y);
    
    b.find(4)->setColor(RedBlackTree<int>::Color::BLACK);
    y=9;
    b.insert(y);

    y = 10;
    cout << "10 info: " << endl;
    cout << "Left child: " << b.find(y)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << b.find(y)->getLeftT() << endl;
    cout << "Right child: " << b.find(y)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << b.find(y)->getRightT() << endl;
    cout << "Parent: " << b.find(y)->getParent()->getDatum() << endl;
    cout << "Color: " << b.find(y)->getColor() << endl;

     ss();

    y = 8;
    cout << "8 info: " << endl;
    cout << "Left child: " << b.find(y)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << b.find(y)->getLeftT() << endl;
    cout << "Right child: " << b.find(y)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << b.find(y)->getRightT() << endl;
    cout << "Parent: " << b.find(y)->getParent()->getDatum() << endl;
    cout << "Color: " << b.find(y)->getColor() << endl;
    
     ss();

    y = 4;
    cout << "4 info: " << endl;
    cout << "Left child: " << b.find(y)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << b.find(y)->getLeftT() << endl;
    cout << "Right child: " << b.find(y)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << b.find(y)->getRightT() << endl;
    cout << "Parent: " << b.find(y)->getParent()->getDatum() << endl;
    cout << "Color: " << b.find(y)->getColor() << endl;

    ss();

    y = 9;
    cout <<  b.find(y)->getDatum() << " info: " << endl;
    cout << "Left child: " << b.find(y)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << b.find(y)->getLeftT() << endl;
    cout << "Right child: " << b.find(y)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << b.find(y)->getRightT() << endl;
    cout << "Parent: " << b.find(y)->getParent()->getDatum() << endl;
    cout << "Color: " << b.find(y)->getColor() << endl;
    

    b.print_tree();
    b.inorder();

    */
   {
    RedBlackTree<int> c;
    c.insert(76);
    
c.print_tree();
    ss();
    c.insert(19);
    
c.print_tree();
    ss();
    c.insert(30);
    
    
c.print_tree();
    ss();
    c.insert(58);
    
c.print_tree();
    ss();
    c.insert(65);
    
c.print_tree();
    ss();

    
    c.insert(92);

    c.insert(23);
    c.insert(31);

c.print_tree();
    ss();
    c.insert(33);
    
    c.insert(84);

    c.insert(21);

c.print_tree();
    ss();
    c.insert(81);

    c.insert(96);
    c.insert(24);

    c.insert(6);
    c.insert(52);

    c.insert(13);

    c.insert(79);
 
    c.insert(45);

    c.insert(87);

    c.insert(47);
 
    c.insert(37);

    c.insert(85);
    c.insert(97);
 
    c.insert(100);
    c.insert(25);
    c.insert(82);
 
    c.insert(71);
    c.insert(43);
    c.insert(36);

    c.print_tree();
    ss();

    //c.remove(58);
    //c.remove(43);
    //c.remove(92);
    c.print_tree();
    c.inorder();
    
    /*
    c.make_empty();

    c.print_tree();
    cout << c.get_root() << endl;
    cout << c.getDummy() << endl;

    c.make_empty();
    */
   /*
    ss();
    RedBlackTree<int> d(c);
    d.print_tree();
    u = 65;
    cout <<  c.find(u)->getDatum() << " info: " << endl;
    cout << "Left child: " << c.find(u)->getLeft()->getDatum() << endl;
    cout << "Left thread? " << c.find(u)->getLeftT() << endl;
    cout << "Right child: " << c.find(u)->getRight()->getDatum() << endl;
    cout << "Right threaded? " << c.find(u)->getRightT() << endl;
    cout << "Parent: " << c.find(u)->getParent()->getDatum() << endl;
    cout << "Color: " << c.find(u)->getColor() << endl;

    c.inorder();
    d.inorder();

    d.make_empty();

    c.inorder();
    d.inorder();
    cout << "minimum: " << c.find_min() << endl;
    cout << "maximum: " << c.find_max() << endl;

    d = c;
    c=d;
    d.print_tree();
    c.insert(6);
    c.insert(6);
    c.insert(6);
    c.print_tree();
    c.inorder();
    d.inorder();
    c.make_empty();
    try{ c.find_min();}
    catch(std::invalid_argument e){cout << e.what() << endl;}
    try{ c.find_max();}
    catch(std::invalid_argument e){cout << e.what() << endl;}

    d = c;
    
    d.print_tree();
    */
    }
    
   /*
    {//red node deletion
        RedBlackTree<int> e;
        e.insert(6);
        e.insert(4);
        e.insert(2);
        e.insert(8);
        e.insert(10);

        e.insert(13);

        e.print_tree();
        ss();
        e.find(6)->setColor(RedBlackTree<int>::RED);
        e.remove(6);//no subtrees right
        e.print_tree();
        ss();

        e.remove(8); //right subtree right
        ss();
        e.insert(3);
        e.find(2)->setColor(RedBlackTree<int>::RED);
        e.remove(2); // no subtrees left
        e.print_tree();
        ss();
        cout << e.find(3)->getLeft()->getDatum() << "||||" << e.find(3)->getRight()->getDatum() << endl;
        cout << e.find(3)->getLeftT() << "||||" << e.find(3)->getRightT() << endl;
        cout << e.find(3)->getParent()->getDatum() << endl;
        e.insert(2);
        e.print_tree();
        e.remove(4); //right subtree right
        ss();
        e.insert(5);
        e.print_tree();

        e.remove(13);
        e.find(10)->setColor(RedBlackTree<int>::RED);
        e.remove(10);//left subtree right
        ss();
        e.print_tree();
        ss();
        e.insert(1);

        e.print_tree();
        ss();

        e.find(2)->setColor(RedBlackTree<int>::RED);
        e.remove(2);//left subtree left

        e.find(5)->setColor(RedBlackTree<int>::RED);
        int j = 1;
        for(int i = 0; i < 100; ++i) { 
            j = (j * i + 71) % 200;
            e.insert(j);
        }
        e.print_tree();
        ss();
        j = 1;
        for(int i = 0; i < 54; ++i) { 
            j = (j * i + 71) % 200;
            //cout << " e.remove(: " << j << endl;
            cout << i << endl;
            e.nodeInfo(e.find(j));
            if(e.find(j)->getColor() == RedBlackTree<int>::RED){e.remove(j);}
            //e.nodeInfo(e.find(j));
            //e.print_tree();
            //e.inorder();
            ss();
            
        for(int i = 0; i < 100; ++i) { 
            j = (j * i + 71) % 200;
            e.insert(j);
        }
        
        e.print_tree();
            e.inorder();
        }
    }
    */
   /*
   {
    RedBlackTree<int> e;

    e.insert(76);
    e.insert(19);
    e.insert(30);
    e.insert(58);

    e.insert(65);

    e.insert(92);
    e.insert(23);
    e.insert(31);

    e.insert(33);
    e.insert(84);

    e.insert(21);

    e.insert(81);
    e.insert(96);
    e.insert(24);

    e.insert(6);
    e.insert(52);

    e.insert(13);

    e.insert(79);
    e.insert(45);

    e.insert(87);

    e.insert(47);
    e.insert(37);

    e.insert(85);
    e.insert(97);
    e.insert(100);
    e.insert(25);
    e.insert(82);
    e.insert(71);
    e.insert(43);
    e.insert(36);
    
    e.print_tree();
    e.inorder();

    ////LEAF NODE
    //PARENT IS LEFT CHILD
    e.remove(23);
    e.nodeInfo(e.find(24));
    e.remove(25);
    e.nodeInfo(e.find(24));


    //PARENT IS RIGHT CHILD
    e.remove(43);
    e.nodeInfo(e.find(37));
    e.remove(36);
    e.nodeInfo(e.find(37));
    //// END LEAF NODE


    ////TWO CHILDREN
    // full right subtree
    e.remove(92);
    e.nodeInfo(e.find(96));
    e.nodeInfo(e.find(87));
    e.nodeInfo(e.find(97));
    
    e.remove(84);
    e.remove(96);
    e.remove(52);
    e.remove(45);
    e.remove(37);
    e.remove(100);
    e.remove(71);
    
    e.print_tree();
    e.inorder();
   }
   */

  {
      RedBlackTree<int> e;
/*
    e.insert(14);
    e.insert(8);
    e.insert(55);
    e.insert(332);
    e.insert(6);
    e.insert(4);
    e.insert(10);
      e.insert(7);
      e.insert(11);
      e.insert(12);

    e.print_tree();
    e.inorder();

    e.remove(14); //CASE 2: DELETE RED, BLACK REPLACEMENT
    e.print_tree();
    e.inorder();

    e.remove(6);
    e.print_tree();
    e.inorder();

    e.make_empty();

    e.insert(14);
    e.insert(8);
    e.insert(55);
    e.insert(332);
    e.insert(6);
    e.insert(4);
    e.insert(10);
    e.insert(7);
    e.insert(11);
    e.insert(12);

    e.print_tree();
    e.inorder();

    e.remove(10);

        e.print_tree();
    e.inorder();

    e.remove(8);

    e.print_tree();
    e.inorder();

    x = 11;
    e.nodeInfo(e.find(x));
    x =14;
    e.nodeInfo(e.find(x));
    x = 12;
    e.nodeInfo(e.find(x));
    x = 15;
    e.nodeInfo(e.find(x));
    x = 15;
    e.nodeInfo(e.find(x));
    x = 6;
    e.nodeInfo(e.find(x));

    e.remove(6);//CASE 1: RED DEL, RED REPLACEMENT two subtrees, deleted node is red left child leaf 
    e.print_tree();
    e.inorder();

    e.print_tree();
    e.inorder();

    e.remove(8);//CASE 3:  node is right child with right subtree
    e.print_tree();
    e.inorder();
    

    x = 7;
    e.nodeInfo(e.find(x));
    x = 4;
    e.nodeInfo(e.find(x));
    x = 10;
    e.nodeInfo(e.find(x));
    x = 14;
    e.nodeInfo(e.find(x));

    e.insert(9);
    e.print_tree();
    e.inorder();

    e.remove(10); // CASE 3 : node is right child with left subtree
    e.print_tree();
    e.inorder();

    x = 7;
    e.nodeInfo(e.find(x));
    x = 4;
    e.nodeInfo(e.find(x));
    x = 9;
    e.nodeInfo(e.find(x));
    x = 14;
    e.nodeInfo(e.find(x));

    e.insert(11);
    e.insert(13);

    e.print_tree();
    e.inorder();

    e.remove(11); // CASE 3 : node is right child with two subtree
    e.print_tree();
    e.inorder();

    e.insert(3);    
    e.remove(4);//CASE 3 : node is left child, left subtree    
    
    e.print_tree();
    e.inorder();

    e.insert(4);    
    e.remove(3);//CASE 3 : node is left child, right subtree    

    e.print_tree();
    e.inorder();

    e.insert(3);
    e.insert(5);

    e.print_tree();
    e.inorder();

    e.remove(4);//CASE 3: node is left child 2 subtrees

    e.print_tree();
    e.inorder();

    x = 3;
    e.nodeInfo(e.find(x));
    x = 5;
    e.nodeInfo(e.find(x));
    x = 7;
    e.nodeInfo(e.find(x));
    x = 14;
    e.nodeInfo(e.find(x));

    
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    int j = 1;
    for(int i = 0; i < 50; ++i){
        j = (j * i + 97) % 100;
        e.insert(j);
    }
    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> delta = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

    cout << "1M insertions took " << delta.count() << "seconds" << endl;

    start = std::chrono::high_resolution_clock::now();
    RedBlackTree<int> d(e);
    stop = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "copy construction took " << delta.count() << "seconds" << endl;
    e.print_tree();
    ss();
    d.print_tree();

d.make_empty();
    start = std::chrono::high_resolution_clock::now();
    d = e;
    stop = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
    cout << "copy assignment took " << delta.count() << "seconds" << endl;

    e.print_tree();
    ss();
    d.print_tree();

    
    start = std::chrono::high_resolution_clock::now();
    j = 1;
    for(int i = 0; i < 100; ++i){
        j = (j * i + 97) % 200;
        e.contains(j);
    }
    stop = std::chrono::high_resolution_clock::now();

    delta = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

    cout << "1M queries took " << delta.count() << " seconds" << endl;
    RedBlackTree<int> f(e);
    e.print_tree();
    e.inorder();
    f.print_tree();
    f.inorder();

    start = std::chrono::high_resolution_clock::now();
    j = 1;
    for(int i = 0; i < 1000; ++i){
        j = (j * i + 907) % 2000;
        //cout << "iteration : " << i << " : removing " << j << endl;
        e.remove(j);
    }
    stop = std::chrono::high_resolution_clock::now();

    delta = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

    cout << "1M deletions took " << delta.count() << "seconds" << endl;
  */  
  }
  
    return 0;
}