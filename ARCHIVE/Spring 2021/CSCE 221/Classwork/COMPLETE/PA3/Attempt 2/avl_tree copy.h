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
    std::string children() {
        std::string num = "none";
        if(leftChild != nullptr && rightChild == nullptr){num = "left";}
        if(leftChild == nullptr && rightChild != nullptr){num = "right";}
        if(leftChild != nullptr && rightChild != nullptr){num = "both";}

        return num;
    }
    int updateHeight() {
        int count = 0;
        if(children() == "none") {return 0;}
        if(children() == "right") {count += getRight()->updateHeight();}
        if(children() == "left") {count += getLeft()->updateHeight();}
        if(children() == "both") {count += max(getRight()->updateHeight(), getLeft()->updateHeight());}
        return count + 1;
    }
    void recountHeight() { height = updateHeight();}
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
    void rebalance(NodeA<Comparable>*); //rotates necessary values to create a balanced tree
    void LL(NodeA<Comparable>*); //left rotation
    void RR(NodeA<Comparable>*); // right rotation
    void LR(NodeA<Comparable>*);
    void RL(NodeA<Comparable>*);
    void updateNodeHeights(NodeA<Comparable>*); //updates all of the heights along a single subtree
    bool get_balance(NodeA<Comparable>*);// checks the balance of a single node
};

    template <typename Comparable>
    AVLTree<Comparable>::AVLTree(){}
    template <typename Comparable>
    AVLTree<Comparable>::AVLTree(const AVLTree& other){
        if(other.getRoot() == nullptr){ make_empty();}
        else{
            make_empty();
            root = new NodeA<Comparable>;
            root->setDatum(other.getRoot()->getDatum());
            init_copy(root, other.getRoot());
        }
    }
    template <typename Comparable>
    AVLTree<Comparable>::~AVLTree(){ if(root != nullptr) {empty(root);}}
    template <typename Comparable>
    bool AVLTree<Comparable>::contains(const Comparable& val) const{
        if(root == nullptr){return false;}
        Comparable test = find(val)->getDatum();
        return (val == test);
    }
    template <typename Comparable>
    AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree& other){
        if(other.getRoot() == root){return *this;}
        if(!is_empty()){empty(root);}
        if(other.is_empty()){empty(root); return *this;}
        this->root = new NodeA<Comparable>;
        root->setDatum(other.getRoot()->getDatum());
        init_copy(root, other.getRoot());
        return *this;
    }
    template <typename Comparable>
    void AVLTree<Comparable>::insert(const Comparable& val){
        if(contains(val)){ return; }

        NodeA<Comparable>* newNodeA = new NodeA<Comparable>;
        newNodeA->setDatum(val);
        if(root == nullptr) {root = newNodeA; return;}
        
        NodeA<Comparable>* cursor = find(val);
        if(cursor->getDatum() < val) { cursor->setRight(newNodeA); }
        else if(cursor->getDatum() > val) { cursor->setLeft(newNodeA); 
        }
        rebalance(root);
        return;
    }
    template <typename Comparable>
    void AVLTree<Comparable>::remove(const Comparable& val){
        if(!contains(val)){return;}
        NodeA<Comparable>* cursor = root;
        NodeA<Comparable>* parent = root;
        NodeA<Comparable>* pin = find(val);

        cursor = find(val);

        if(cursor->children() == "both") {
            cursor = bottomLeft(cursor->getRight());
            parent = findParent(cursor, root);
            if(parent->getLeft() == cursor){parent->setLeft(cursor->getRight());}
            if(parent->getRight() == cursor){parent->setRight(cursor->getRight());}

            pin->setDatum(cursor->getDatum());
            delete cursor;

            rebalance(root);

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
            rebalance(root);
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
            rebalance(root);
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
            rebalance(root);
            return;
        }
    }
    template <typename Comparable>
    const Comparable& AVLTree<Comparable>::find_min() const{
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        NodeA<Comparable>* cursor = root;
        while(cursor->getLeft() != nullptr){cursor = cursor->getLeft();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    const Comparable& AVLTree<Comparable>::find_max() const{
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_max() of empty tree.");}
        NodeA<Comparable>* cursor = root;
        while(cursor->getRight() != nullptr){cursor = cursor->getRight();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    void AVLTree<Comparable>::print_tree(std::ostream& os) const{
        if(root == nullptr) {os << "<empty>\n"; return;}
        reverse_inorder(os, root, 0);
    }
    template <typename Comparable>
    void AVLTree<Comparable>::print_tree() const{
        if(root == nullptr) {cout << "<empty>\n"; return;}
        reverse_inorder(cout, root, 0);
    }
    template <typename Comparable>
    bool AVLTree<Comparable>::is_empty() const{return !(root);}
    template <typename Comparable>
    void AVLTree<Comparable>::insert(Comparable&& val){ Comparable temp = val; insert(temp);}
    template <typename Comparable>
    void AVLTree<Comparable>::make_empty() {if(root != nullptr) {empty(root);}}
    template <typename Comparable>
    NodeA<Comparable>* AVLTree<Comparable>::getRoot() const{return root;}
    template <typename Comparable>
    NodeA<Comparable>* AVLTree<Comparable>::find(const Comparable& val) const{
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
    void AVLTree<Comparable>::rebalance(NodeA<Comparable>* cursor){
        if(cursor != nullptr) {
            if(cursor->getLeft() != nullptr) {rebalance(cursor->getLeft());}
            if(cursor->getRight() != nullptr) {rebalance(cursor->getRight());}
            int lh = -1;
            int rh = -1;
            if(cursor->getLeft() != nullptr) {lh = cursor->getLeft()->getHeight();}
            if(cursor->getRight() != nullptr) {rh = cursor->getRight()->getHeight();}
            int balance = lh - rh;

            if(balance > 1) {
                int lsubbalance = -1;
                int rsubbalance = -1;
                if(cursor->getLeft()->getRight() != nullptr) { rsubbalance = cursor->getLeft()->getRight()->getHeight(); }
                if(cursor->getLeft()->getLeft() != nullptr){ lsubbalance = cursor->getLeft()->getLeft()->getHeight(); }
                
                if(lsubbalance - rsubbalance < 0){ RL(cursor); updateNodeHeights(root); return;}
                else{ RR(cursor); updateNodeHeights(root); return;}
            }
            if(balance < -1) {
                int lsubbalance = -1;
                int rsubbalance = -1;
                if(cursor->getRight()->getRight() != nullptr) { rsubbalance = cursor->getRight()->getRight()->getHeight(); }
                if(cursor->getRight()->getLeft() != nullptr){ lsubbalance = cursor->getRight()->getLeft()->getHeight(); }

                if(lsubbalance - rsubbalance > 0){ LR(cursor); updateNodeHeights(root); return;}
                else{ LL(cursor); updateNodeHeights(root); return;}
            }
        }
        updateNodeHeights(root);
    }
    template <typename Comparable>
    void AVLTree<Comparable>::updateNodeHeights(NodeA<Comparable>* cursor){
        if(cursor->getLeft() != nullptr) {updateNodeHeights(cursor->getLeft());}
        if(cursor->getRight() != nullptr) {updateNodeHeights(cursor->getRight());}
        cursor->recountHeight();           
    }
    template <typename Comparable>
    bool AVLTree<Comparable>::is_balanced(NodeA<Comparable>* cursor) {
        if(root == nullptr) {return true;}
        bool lhs = true;
        bool rhs = true;
        if(cursor->children() == "none"){return true;}
        if(cursor != nullptr) {
            int lh = -1;
            int rh = -1;
            if(cursor->getLeft() != nullptr) {lh = cursor->getLeft()->getHeight();}
            if(cursor->getRight() != nullptr) {rh = cursor->getRight()->getHeight();}
            
            int balance = lh - rh;
            if(balance < -1){ return false;}
            if(balance > 1){ return false;}
        }
        return (lhs && rhs);
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