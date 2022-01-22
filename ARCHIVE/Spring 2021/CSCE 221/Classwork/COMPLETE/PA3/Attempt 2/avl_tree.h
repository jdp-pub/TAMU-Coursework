#ifndef AVL_TREE_H
#define AVL_TREE_H



#include <iostream>
using std::cout, std::endl;
void nla() {cout << endl; }
void ssa() {cout << "~~~~~~~~~~~~~~~" << endl;}
void TestHeaderA(std::string name, size_t& number){
    cout << "~~~BEGIN TEST SEQUENCE " << number << " : " << name << "~~~" << endl;
    ++number;
    nla();
}

int log2(int num) {
    int iteration = -1;
    while (num) {
        iteration++;
        num >>= 1;//right bitshift assigment operator  
        // divides num by 2 (2^1) until it is assigned zero with integer division
        // the logarithm comes from number of times 2 can be wholly taken from num
    }
    return iteration;
}

void TestFooterA(){ cout << "~~~SEQUENCE COMPLETE~~~" << endl; }

template<typename Comparable>
void testA(Comparable expected, Comparable testing, std::string name, std::string file, size_t line) {
    std::string RESULT;
    if(expected == testing) { RESULT = "PASS"; }
    else{ RESULT = "FAIL"; }
    cout << name << " : " << file << " line " << line << " : " << RESULT << endl
         << "EXPECTED " << expected << " : ACTUAL " << testing << endl;
         ssa();
         nla();

}

template<typename Comparable>
Comparable max(Comparable lhs, Comparable rhs) {
    return (lhs >= rhs) ? lhs : rhs;
}

template <typename Comparable>
class NodeA {
    Comparable datum = {};
    int height = 0;
    int subnodes = 0;

    NodeA* leftChild = nullptr;
    NodeA* rightChild = nullptr;

    public:
    NodeA() {}
    NodeA(Comparable x) {datum = x;}
    NodeA(Comparable& x) {datum = x;}
    NodeA(Comparable&& x) {datum = x;}
    NodeA(const NodeA& x) {datum = x.getDatum();}
    ~NodeA(){}

    NodeA& operator=(const NodeA& x){datum = x.getDatum(); return *this;}

    void setRight(NodeA* right){ rightChild = right; }
    void setLeft(NodeA* left){ leftChild = left; }
    void setDatum(const Comparable x){ datum = x; }

    NodeA* getRight() {return rightChild;}
    NodeA* getLeft() {return leftChild;}
    Comparable getDatum() const {return datum;}
    Comparable& getDatum() {return datum;}
    int getSubnodes() {return subnodes;}
    void addSubnodes(int x){subnodes += x;}
    std::string children() {
        std::string num = "none";
        if(leftChild != nullptr && rightChild == nullptr){num = "left";}
        if(leftChild == nullptr && rightChild != nullptr){num = "right";}
        if(leftChild != nullptr && rightChild != nullptr){num = "both";}

        return num;
    }
    void resetHeight(){ height =  (int)(log2(subnodes+1)-1);}
    void setHeight(int x){ height = x;}
    int getHeight() const{ return height; }
};

template <typename Comparable>
class AVLTree {
    NodeA<Comparable>* root = nullptr;

    public:
    // TODO(student): implement AVLTree
    AVLTree();//C - makes an empty tree
    AVLTree(const AVLTree&);//C - constructs a copy of the given tree
    ~AVLTree();//C - destructs this tree
    AVLTree& operator=(const AVLTree&);//C - assigns a copy of the given tree
    bool contains(const Comparable&) const;//C - returns Boolean true if the specified value is in the tree
    void insert(const Comparable&);//C - insert the given value into the tree
    void remove(const Comparable&);//C - remove the specified value from the tree (use minimum of right child tree when value has two children)
    const Comparable& find_min() const;// - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    const Comparable& find_max() const;// - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    void print_tree(std::ostream& os) const;//C - pretty print the tree (rotated 90 degrees to the left, two spaces per level; see example below) to the specified output stream (default std::cout).  Print “<empty>\n” if the tree is empty.
    void print_tree() const;

    //Optional
    //AVLTree(AVLTree&&);// - move constructs a copy of the given (rvalue) tree
    //AVLTree& operator=(AVLTree&&);// - move assigns a copy of the given (rvalue) tree
    bool is_empty() const;// - returns Boolean true if the tree is empty
    void insert(Comparable&&);// - insert the given rvalue into the tree using move semantics
    void make_empty();// - remove all values from the tree

    //helpers
    NodeA<Comparable>* getRoot() const; //returns tree location
    NodeA<Comparable>* find(const Comparable&) const; //finds a value or the closest thing to it
    void reverse_inorder(std::ostream&, NodeA<Comparable>*, size_t) const; //recursive reverse inorder NodeA traversal
    void empty(NodeA<Comparable>*); //recursive NodeA deletion
    void init_copy(NodeA<Comparable>*, NodeA<Comparable>*); //recursive initialization
    void rebalance_insert(NodeA<Comparable>*); //rotates necessary values to create a balanced tree
    void LL(NodeA<Comparable>*); //left rotation
    void RR(NodeA<Comparable>*); // right rotation
    void LR(NodeA<Comparable>*);
    void RL(NodeA<Comparable>*);
    int updateSubtreeHeight(NodeA<Comparable>*); //recounts all of the heights of all of the nodes in the tree
    int getBalance(NodeA<Comparable>*);
};

    template <typename Comparable>
    AVLTree<Comparable>::AVLTree(){}
    template <typename Comparable>
    AVLTree<Comparable>::AVLTree(const AVLTree& other){ //O(N)
        if(other.getRoot() == nullptr){ make_empty();}
        else{
            make_empty();
            root = new NodeA<Comparable>;
            root->setDatum(other.getRoot()->getDatum());
            init_copy(root, other.getRoot());
        }
    }
    template <typename Comparable>
    AVLTree<Comparable>::~AVLTree(){ if(root != nullptr) {empty(root);}} //O(N)
    template <typename Comparable>
    bool AVLTree<Comparable>::contains(const Comparable& val) const{
        if(root == nullptr){return false;}
        Comparable test = find(val)->getDatum();
        return (val == test);
    }
    template <typename Comparable>
    AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree& other){//2O(N)
        if(other.getRoot() == root){return *this;}//O(1)
        if(!is_empty()){empty(root);}//O(N)
        if(other.is_empty()){empty(root); return *this;}//O(N)
        this->root = new NodeA<Comparable>;
        root->setDatum(other.getRoot()->getDatum());
        init_copy(root, other.getRoot());//O(N)
        return *this;
    }
    template <typename Comparable>
    void AVLTree<Comparable>::insert(const Comparable& val){//O(N)
        if(contains(val)){ return; }//O(log N)

        NodeA<Comparable>* newNodeA = new NodeA<Comparable>;
        newNodeA->setDatum(val);
        if(root == nullptr) {root = newNodeA; return;}
        
        NodeA<Comparable>* cursor = find(val);//O(log N)
        if(cursor->getDatum() < val) { cursor->setRight(newNodeA); }
        else if(cursor->getDatum() > val) { cursor->setLeft(newNodeA); }
        root->setHeight(updateSubtreeHeight(root));
        rebalance_insert(root);//O(N)
        return;
    }
    template <typename Comparable>
    void AVLTree<Comparable>::remove(const Comparable& val){//O(N) due to rebalance function
    
        if(!contains(val)){return;}//O(log N)
        NodeA<Comparable>* cursor = root;
        NodeA<Comparable>* parent = root;
        NodeA<Comparable>* pin = find(val);//O(log N)

        cursor = find(val);//O(log N)

        if(cursor->children() == "both") {
            cursor = bottomLeft(cursor->getRight());
            parent = findParent(cursor, root);
            if(parent->getLeft() == cursor){parent->setLeft(cursor->getRight());}
            if(parent->getRight() == cursor){parent->setRight(cursor->getRight());}

            pin->setDatum(cursor->getDatum());
            delete cursor;
            root->setHeight(updateSubtreeHeight(root));
            rebalance_insert(root);

            return;
        }
        else if(cursor->children() == "none") { 
            
            if(val == root->getDatum()) { empty(root); return;}
            parent = findParent(cursor, root);
            if(parent != nullptr) {
                if(parent->getLeft() == cursor){parent->setLeft(cursor->getLeft());}
                if(parent->getRight() == cursor){parent->setRight(cursor->getLeft());}
            }
            delete cursor;
            root->setHeight(updateSubtreeHeight(root));
            rebalance_insert(root);
            return;
        }
        else if(cursor->children() == "left") {
            if(cursor == root) {root = cursor->getLeft(); delete cursor; return;}
            parent = findParent(cursor, root);
            if(parent != nullptr) {
                if(parent->getLeft() == cursor){parent->setLeft(cursor->getLeft());}
                if(parent->getRight() == cursor){parent->setRight(cursor->getLeft());}
            }
            delete cursor;
            root->setHeight(updateSubtreeHeight(root));
            rebalance_insert(root);
            return;
        }
        else if(cursor->children() == "right") {
            if(cursor == root) {root = cursor->getRight(); delete cursor; return;}
            parent = findParent(cursor, root);
            if(parent != nullptr) {
                if(parent->getLeft() == cursor){parent->setLeft(cursor->getRight());}
                if(parent->getRight() == cursor){parent->setRight(cursor->getRight());}
            }
            delete cursor;
            root->setHeight(updateSubtreeHeight(root));
            rebalance_insert(root);
            return;
        }
        
    }
    template <typename Comparable>
    const Comparable& AVLTree<Comparable>::find_min() const{//O(log N)
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        NodeA<Comparable>* cursor = root;
        while(cursor->getLeft() != nullptr){cursor = cursor->getLeft();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    const Comparable& AVLTree<Comparable>::find_max() const{//O(log N)
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_max() of empty tree.");}
        NodeA<Comparable>* cursor = root;
        while(cursor->getRight() != nullptr){cursor = cursor->getRight();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    void AVLTree<Comparable>::print_tree(std::ostream& os) const{//O(N)
        if(root == nullptr) {os << "<empty>\n"; return;}
        reverse_inorder(os, root, 0);
    }
    template <typename Comparable>
    void AVLTree<Comparable>::print_tree() const{
        if(root == nullptr) {cout << "<empty>\n"; return;}
        reverse_inorder(cout, root, 0);
    }
    template <typename Comparable>
    bool AVLTree<Comparable>::is_empty() const{return !(root);}//O(1)
    template <typename Comparable>
    void AVLTree<Comparable>::insert(Comparable&& val){ Comparable temp = val; insert(temp);}
    template <typename Comparable>
    void AVLTree<Comparable>::make_empty() {if(root != nullptr) {empty(root);}}//O(N)
    template <typename Comparable>
    NodeA<Comparable>* AVLTree<Comparable>::getRoot() const{return root;}
    template <typename Comparable>
    NodeA<Comparable>* AVLTree<Comparable>::find(const Comparable& val) const{//O(log N)
        if(root == nullptr){return nullptr;}
        NodeA<Comparable>* cursor = root;
        while(cursor != nullptr) {
        if((cursor->getDatum() < val) && (cursor->getRight() != nullptr)) {cursor = cursor->getRight();}
        if((cursor->getDatum() > val) && (cursor->getLeft() != nullptr)) {cursor = cursor->getLeft();}
        if(cursor->getDatum() == val) {return cursor;}
        
        if((cursor->getDatum() < val) && (cursor->getRight() == nullptr)) {return cursor;}
        if((cursor->getDatum() > val) && (cursor->getLeft() == nullptr)) {return cursor;}
        }

        return cursor;
    }
    template <typename Comparable>
    void AVLTree<Comparable>::reverse_inorder(std::ostream& os, NodeA<Comparable>* cursor, size_t indent) const{
        if(cursor->getRight() != nullptr) {reverse_inorder(os, cursor->getRight(), indent + 2);}

        for(size_t i = 0; i < indent; ++i) { os << " "; }
        os << cursor->getDatum() << endl;

        if(cursor->getLeft() != nullptr) {reverse_inorder(os, cursor->getLeft(), indent + 2);}
    }
    template <typename Comparable>
    void AVLTree<Comparable>::empty(NodeA<Comparable>* cursor){
        if(!is_empty()){
            if(cursor->getLeft() != nullptr){empty(cursor->getLeft());}
            if(cursor->getRight() != nullptr){empty(cursor->getRight());}
            if(cursor == root){root = nullptr;}
            delete cursor;
        }
        
    }
    template <typename Comparable>
    void AVLTree<Comparable>::init_copy(NodeA<Comparable>* CursorSelf, NodeA<Comparable>* CursorOther) {
        if(CursorOther->getLeft() != nullptr) { 
            NodeA<Comparable>* temp = new NodeA<Comparable>;
            temp->setDatum(CursorOther->getLeft()->getDatum());
            CursorSelf->setLeft(temp);
            init_copy(temp, CursorOther->getLeft());
        }
        if(CursorOther->getRight() != nullptr) { 
            NodeA<Comparable>* temp = new NodeA<Comparable>;
            temp->setDatum(CursorOther->getRight()->getDatum());
            CursorSelf->setRight(temp);
            init_copy(temp, CursorOther->getRight());
        }

    }
    template <typename Comparable>
    void AVLTree<Comparable>::LL(NodeA<Comparable>* pin){
        NodeA<Comparable>* cursor = pin->getRight();
        pin->setRight(cursor->getLeft());
        cursor->setLeft(pin);

        NodeA<Comparable>* parent = findParent(pin, root);
        if(pin == root) {root = cursor;}
        else if(pin == parent->getLeft()) {parent->setLeft(cursor);}
        else if(pin == parent->getRight()) {parent->setRight(cursor);}
    }
    template <typename Comparable>
    void AVLTree<Comparable>::RR(NodeA<Comparable>* pin){
        NodeA<Comparable>* cursor = pin->getLeft();
        pin->setLeft(cursor->getRight());
        cursor->setRight(pin);

        NodeA<Comparable>* parent = findParent(pin, root);
        if(pin == root) {root = cursor;}
        else if(pin == parent->getLeft()) {parent->setLeft(cursor);}
        else if(pin == parent->getRight()) {parent->setRight(cursor);}
    }
    template <typename Comparable>
    void AVLTree<Comparable>::RL(NodeA<Comparable>* pin){
        NodeA<Comparable>* cursor = pin->getLeft();
        LL(cursor);
        RR(pin);
    }
    template <typename Comparable>
    void AVLTree<Comparable>::LR(NodeA<Comparable>* pin){
        NodeA<Comparable>* cursor = pin->getRight();
        RR(cursor);
        LL(pin);
        }
    template <typename Comparable>
    void AVLTree<Comparable>::rebalance_insert(NodeA<Comparable>* cursor){
       if(cursor->getLeft() != nullptr) {rebalance_insert(cursor->getLeft());}
        if(cursor->getRight() != nullptr) {rebalance_insert(cursor->getRight());}
        

        
            int balance = getBalance(cursor);
            if(balance > 1){
                if(getBalance(cursor->getLeft()) < 0){ RL(cursor); cursor->setHeight(updateSubtreeHeight(cursor)); return;}
                else{ RR(cursor); cursor->setHeight(updateSubtreeHeight(cursor)); return;}
            }
            else if(balance < -1){
                if(getBalance(cursor->getRight()) > 0){ LR(cursor); cursor->setHeight(updateSubtreeHeight(cursor)); return;}
                else{ LL(cursor); cursor->setHeight(updateSubtreeHeight(cursor)); return;}
            }
    }
    template <typename Comparable>
    int AVLTree<Comparable>::updateSubtreeHeight(NodeA<Comparable>* cursor) {
        int lheight = 0;
        int rheight = 0;
        if(cursor->getLeft() != nullptr) {lheight = updateSubtreeHeight(cursor->getLeft());}
        if(cursor->getRight() != nullptr) {rheight = updateSubtreeHeight(cursor->getRight());}
        if(cursor != root){cursor->setHeight(max(lheight, rheight));}
        return max(lheight, rheight)+1;
    }
    template <typename Comparable>
    int AVLTree<Comparable>::getBalance(NodeA<Comparable>* cursor) {
        int balance = 0;
        if(cursor == nullptr){ return balance;}
        
        if(cursor->children() == "none"){return balance;}
        if(cursor != nullptr) {
            int lh = -1;
            int rh = -1;
            if(cursor->getLeft() != nullptr) {lh = cursor->getLeft()->getHeight();}
            if(cursor->getRight() != nullptr) {rh = cursor->getRight()->getHeight();}
            
            balance = lh - rh;
        }
        return balance;
    }
    template <typename Comparable>
    NodeA<Comparable>* findParent(NodeA<Comparable>* pin, NodeA<Comparable>* head) {
        NodeA<Comparable>* parent = head;
        if(parent != pin){
            while((parent->getLeft() != pin) && (parent->getRight() != pin)){
                if(pin->getDatum() > parent->getDatum()) {parent = parent->getRight();}
                else if(pin->getDatum() < parent->getDatum()) {parent = parent->getLeft();}
            }
        }
        return parent;
    }
    template <typename Comparable>
    NodeA<Comparable>* bottomLeft(NodeA<Comparable>* subtree) {
        while(subtree->getLeft() != nullptr) { subtree = subtree->getLeft();}
        return subtree;
    }
#endif