#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

using std::cout, std::endl;

void nl() {cout << endl; }
void ss() {cout << "~~~~~~~~~~~~~~~" << endl;}
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

template <typename Comparable>
class Node {
    Comparable datum = {};

    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    public:
    Node() {}
    Node(Comparable x) {datum = x;}
    Node(Comparable& x) {datum = x;}
    Node(Comparable&& x) {datum = x;}
    Node(const Node& x) {datum = x.getDatum();}
    ~Node(){}

    Node& operator=(const Node& x){datum = x.getDatum; return *this;}

    void setRight(Node* right){ rightChild = right; }
    void setLeft(Node* left){ leftChild = left; }
    void setDatum(const Comparable x){ datum = x; }

    Node* getRight() {return rightChild;}
    Node* getLeft() {return leftChild;}
    Comparable getDatum() const {return datum;}
    Comparable& getDatum() {return datum;}
    std::string children() {
        std::string num = "none";
        if(leftChild != nullptr && rightChild == nullptr){num = "left";}
        if(leftChild == nullptr && rightChild != nullptr){num = "right";}
        if(leftChild != nullptr && rightChild != nullptr){num = "both";}

        return num;
    }
};

template <typename Comparable>
class BinarySearchTree {
    // TODO(student): implement BinarySearchTree
    Node<Comparable>* root = nullptr;

    public:
    BinarySearchTree();// C- makes an empty tree
    BinarySearchTree(const BinarySearchTree&);//C - constructs a copy of the given tree
    ~BinarySearchTree();// C- destructs this tree
    BinarySearchTree& operator=(const BinarySearchTree&);//C - assigns a copy of the given tree
    bool contains(const Comparable&) const;//C - returns Boolean true if the specified value is in the tree
    void insert(const Comparable&);//C - insert the given value into the tree
    void remove(const Comparable&);//C - remove the specified value from the tree (use minimum of right child tree when value has two children)
    const Comparable& find_min() const;//C - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    const Comparable& find_max() const;//C - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    void print_tree(std::ostream&);//C const - pretty print the tree (rotated 90 degrees to the left, two spaces per level; see example below) to the specified output stream (default std::cout). Print “<empty>\n” if the tree is empty.
    void print_tree();

    //Optional
    //BinarySearchTree(BinarySearchTree&&);// - move constructs a copy of the given (rvalue) tree
    //BinarySearchTree& operator=(BinarySearchTree&&);// - move assigns a copy of the given (rvalue) tree
    bool is_empty() const;//C - returns Boolean true if the tree is empty
    void insert(Comparable&&);//C- insert the given rvalue into the tree using move semantics
    void make_empty();//C - remove all values from the tree

    //helpers
    Node<Comparable>* getRoot() const; //returns tree location
    Node<Comparable>* find(const Comparable&) const; //finds a value or the closest thing to it
    void reverse_inorder(std::ostream&, Node<Comparable>*, size_t) const; //recursive reverse inorder node traversal
    void empty(Node<Comparable>*); //recursive node deletion
    void init_copy(Node<Comparable>*, Node<Comparable>*); //recursive initialization
};
    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree(){}
    template <typename Comparable>
    BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& other){
        if(other.getRoot() == nullptr){ make_empty();}
        else{
            make_empty();
            root = new Node<Comparable>;
            root->setDatum(other.getRoot()->getDatum());
            init_copy(root, other.getRoot());
        }
    }
    template <typename Comparable>
    BinarySearchTree<Comparable>::~BinarySearchTree(){ if(root != nullptr) {empty(root);}}
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::contains(const Comparable& val) const{
        if(root == nullptr){return false;}
        Comparable test = find(val)->getDatum();
        return (val == test);
    }
    template <typename Comparable>
    BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& other){
        if(other.getRoot() == root){ return *this;}
        if(!is_empty()){empty(root);}
        if(other.is_empty()){empty(root); return *this;}
        this->root = new Node<Comparable>;
        root->setDatum(other.getRoot()->getDatum());
        init_copy(root, other.getRoot());
        return *this;
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(const Comparable& val){
        if(contains(val)){return; }
        
        Node<Comparable>* newNodeA = new Node<Comparable>;
        newNodeA->setDatum(val);
        if(root == nullptr) {root = newNodeA; return;}
        
        Node<Comparable>* cursor = find(val);
        if(cursor->getDatum() < val) { cursor->setRight(newNodeA); }
        else if(cursor->getDatum() > val) { cursor->setLeft(newNodeA); }
        return;
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::remove(const Comparable& val){
        if(!contains(val)){return;}
        Node<Comparable>* cursor = root;
        Node<Comparable>* parent = root;
        Node<Comparable>* pin = find(val);

        cursor = find(val);
        
        if(cursor->children() == "both") {
            cursor = bottomLeft(cursor->getRight());
            parent = findParent(cursor, root);
            if(parent->getLeft() == cursor){parent->setLeft(cursor->getRight());}
            if(parent->getRight() == cursor){parent->setRight(cursor->getRight());}

            pin->setDatum(cursor->getDatum());
            delete cursor;

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
            return;
        }
    }
    template <typename Comparable>
    const Comparable& BinarySearchTree<Comparable>::find_min() const{
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        Node<Comparable>* cursor = root;
        while(cursor->getLeft() != nullptr){cursor = cursor->getLeft();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    const Comparable& BinarySearchTree<Comparable>::find_max() const{
        try{if(is_empty()){throw 1;}}
        catch(int n){throw std::invalid_argument("find_max() of empty tree.");}
        Node<Comparable>* cursor = root;
        while(cursor->getRight() != nullptr){cursor = cursor->getRight();}
        return cursor->getDatum();
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::print_tree(std:: ostream& os) {
        if(root == nullptr) {os << "<empty>\n"; return;}
        reverse_inorder(os, root, 0);
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::print_tree() {
        if(root == nullptr) {cout << "<empty>\n"; return;}
        reverse_inorder(cout, root, 0);
    }
    template <typename Comparable>
    bool BinarySearchTree<Comparable>::is_empty() const{return !(root);}
    template <typename Comparable>
    void BinarySearchTree<Comparable>::insert(Comparable&& val){ Comparable temp = val; insert(temp);}
    template <typename Comparable>
    void BinarySearchTree<Comparable>::make_empty() {if(root != nullptr) {empty(root);}}
    template <typename Comparable>
    Node<Comparable>* BinarySearchTree<Comparable>::getRoot() const{return root;}
    template <typename Comparable>
    Node<Comparable>* BinarySearchTree<Comparable>::find(const Comparable& val) const{
        Node<Comparable>* cursor = root;
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
    void BinarySearchTree<Comparable>::reverse_inorder(std::ostream& os, Node<Comparable>* cursor, size_t indent) const{
        if(cursor->getRight() != nullptr) {reverse_inorder(os, cursor->getRight(), indent + 2);}

        for(size_t i = 0; i < indent; ++i) { os << " "; }
        os << cursor->getDatum() << endl;

        if(cursor->getLeft() != nullptr) {reverse_inorder(os, cursor->getLeft(), indent + 2);}
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::empty(Node<Comparable>* cursor){
        if(!is_empty()){
            if(cursor->getLeft() != nullptr){empty(cursor->getLeft());}
            if(cursor->getRight() != nullptr){empty(cursor->getRight());}
            if(cursor == root){root = nullptr;}
            delete cursor;
        }
        
    }
    template <typename Comparable>
    void BinarySearchTree<Comparable>::init_copy(Node<Comparable>* CursorSelf, Node<Comparable>* CursorOther) {
        if(CursorOther->getLeft() != nullptr) { 
            Node<Comparable>* temp = new Node<Comparable>;
            temp->setDatum(CursorOther->getLeft()->getDatum());
            CursorSelf->setLeft(temp);
            init_copy(temp, CursorOther->getLeft());
        }
        if(CursorOther->getRight() != nullptr) { 
            Node<Comparable>* temp = new Node<Comparable>;
            temp->setDatum(CursorOther->getRight()->getDatum());
            CursorSelf->setRight(temp);
            init_copy(temp, CursorOther->getRight());
        }

    }
    template <typename Comparable>
    Node<Comparable>* findParent(Node<Comparable>* pin, Node<Comparable>* head) {
        Node<Comparable>* parent = head;
        if(parent != pin){
            while((parent->getLeft() != pin) && (parent->getRight() != pin)){
                if(pin->getDatum() > parent->getDatum()) {parent = parent->getRight();}
                else if(pin->getDatum() < parent->getDatum()) {parent = parent->getLeft();}
            }
        }
        return parent;
    }
    template <typename Comparable>
    Node<Comparable>* bottomLeft(Node<Comparable>* subtree) {
        while(subtree->getLeft() != nullptr) { subtree = subtree->getLeft();}
        return subtree;
    }

#endif