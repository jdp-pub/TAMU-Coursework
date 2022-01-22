#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

using std::cout, std::endl;

void t() {cout << "||||  test  ||||" << endl;}

template <typename Comparable>
class Node {
    Comparable datum = 0;

    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    public:
    Node() {}
    Node(Comparable x) {datum = x;}
    ~Node(){}

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
class BinarySearchTree{
    Node<Comparable>* root = nullptr;

    public:
    BinarySearchTree();//C
    BinarySearchTree(const BinarySearchTree&); //C
    ~BinarySearchTree();//C
    BinarySearchTree& operator=(const BinarySearchTree&);//C
    bool contains(const Comparable&) const;//C
    void insert(const Comparable&);//C
    void remove(const Comparable&);// - remove the specified value from the tree (use minimum of right child tree when value has two children)
    Comparable& find_min() const; //C
    Comparable& find_max() const; //C
    void print_tree(std::ostream&) const;//C

    //helpers
    void dele(Node<Comparable>*);
    void init_copy(Node<Comparable>*, Node<Comparable>*);
    Node<Comparable>* findLoc(Node<Comparable>*, const Comparable&);
    Node<Comparable>* getRoot() const;
    void reverse_inorder(std::ostream&, Node<Comparable>*, size_t) const;

};

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(){}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& other){
    this->root = new Node<Comparable>;
    root->setDatum(other.getRoot()->getDatum());
    init_copy(root, other.getRoot());
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree(){ 
    if(root != nullptr) {BinarySearchTree<Comparable>::dele(this->root);} }

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& val){
    Node<Comparable>* newnode = new Node<Comparable>;
    cout << "inserting " << val << "..." << endl;
    newnode->setDatum(val);

    if(root == nullptr) {root = newnode; return;}

    Node<Comparable>* cursor = findLoc(this->root, val);
    if(val > cursor->getDatum()){
        cursor->setRight(newnode);
    }
    if(val < cursor->getDatum()){
        cursor->setLeft(newnode);
    }
}

template <typename Comparable>
Node<Comparable>* BinarySearchTree<Comparable>::findLoc (Node<Comparable>* roots, const Comparable& val) {
    Node<Comparable>* cursor = roots;
    while(cursor != nullptr) {
        //cout << cursor << endl;
        if(cursor->getDatum() > val) {
            if(cursor->getLeft() == nullptr) { return cursor; }
            else {cursor = cursor->getLeft();}
        }
        if(cursor->getDatum() < val) {
            if(cursor->getRight() == nullptr) { return cursor; }
            else {cursor = cursor->getRight();}
        }
    }
    return nullptr;
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
Node<Comparable>* BinarySearchTree<Comparable>::getRoot() const {return root;}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& other){
    dele(root);
    this->root = new Node<Comparable>;
    root->setDatum(other.getRoot()->getDatum());
    init_copy(root, other.getRoot());
    return *this;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& other) const{
    Node<Comparable>* cursor = root;
    while(cursor != nullptr) {
        if(cursor->getDatum() > other) {cursor = cursor->getLeft();}
        else if(cursor->getDatum() < other) {cursor = cursor->getRight();}
        else if(cursor->getDatum() == other) {return true;}
    }
    return false;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& val){
    if(!contains(val)){cout << "This value is not in this tree." << endl; return;}
    Node<Comparable>* cursor = root;
    if(cursor->children() == "none") { delete cursor; root = nullptr; return;}
    Node<Comparable>* parent;

    while(cursor != nullptr) {
        if(cursor->getDatum() > val) { 
            parent = cursor;
            cursor = cursor->getLeft(); 
        }
        else if(cursor->getDatum() < val) { 
            parent = cursor;
            cursor = cursor->getRight(); 
        }
        else if(cursor->getDatum() == val) {break;}
    }
    if(cursor == nullptr) {return;}
    //t();
    Node<Comparable>* pin = cursor;
    cout << "pin: " << pin->getDatum() << endl;
    cout << "children: " << pin->children() << endl;
    if(pin->children() == "both") {
        //t();
        //cout << "parent: " << parent->children() << endl;
        parent = cursor;
        cursor = cursor->getRight();
        while(cursor->getLeft() != nullptr) {
            parent = cursor;
            cursor = cursor->getLeft();
            //t();
            }
            cout << "parent: " << parent->getDatum() << endl;
            cout << "cursor: " << cursor->getDatum() << endl;
            cout << "pin: " << pin->getDatum() << endl;

        pin->setDatum(cursor->getDatum());
        if(parent->children() == "left"){
        parent->setLeft(cursor->getRight());
        delete cursor;
        return;}

        parent->setRight(cursor->getRight());
        //if(parent->children() == "both"){parent->setLeft(nullptr);}
        delete cursor;
        return;
        //t();
        
        
    }
    else if(pin->children() == "none") {
        if(parent->getLeft() == pin) { parent->setLeft(nullptr);}
        if(parent->getRight() == pin) {parent->setRight(nullptr);}

        delete pin;
        return;
    }
    else if(pin->children() == "left") {
        if(parent->children() == "right"){
       parent->setRight(pin->getLeft());
        delete pin; 
        return;
        }
        //t();
        parent->setLeft(pin->getLeft());
        delete pin; 
        return;
    }
    else if(pin->children() == "right") {
        if(parent->children() == "right") {
        parent->setRight(pin->getRight());
        delete pin;
        return;
        }
        parent->setLeft(pin->getRight());
        delete pin;
        return;
    }
}

template <typename Comparable>
Comparable& BinarySearchTree<Comparable>::find_min() const{
    try{if(root == nullptr) {throw 1;}}
    catch(int n) {throw std::invalid_argument("No values withing tree.");}
    Node<Comparable>* cursor = root;
    while(cursor->getLeft() != nullptr) { cursor = cursor->getLeft(); }
    return cursor->getDatum();
}

template <typename Comparable>
Comparable& BinarySearchTree<Comparable>::find_max() const{
    try{if(root == nullptr) {throw 1;}}
    catch(int n) {throw std::invalid_argument("No values withing tree.");}
    Node<Comparable>* cursor = root;
    while(cursor->getRight() != nullptr) { cursor = cursor->getRight(); }
    return cursor->getDatum();
}

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& os) const {
    if(root == nullptr) {os << "<empty>\n"; return;}
    reverse_inorder(os, root, 0);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::reverse_inorder(std::ostream& os, Node<Comparable>* cursor, size_t indent) const{
    if(cursor->getRight() != nullptr) {reverse_inorder(os, cursor->getRight(), indent + 2);}

    for(size_t i = 0; i < indent; ++i) { os << "  "; }
    os << cursor->getDatum() << endl;

    if(cursor->getLeft() != nullptr) {reverse_inorder(os, cursor->getLeft(), indent + 2);}

    
}

template <typename Comparable>
void BinarySearchTree<Comparable>::dele(Node<Comparable>* head) {

    if(head == nullptr) {}
    else{
        if(head->getLeft() != nullptr) {
            dele(head->getLeft());
        }
        if(head->getRight() != nullptr) {
            dele(head->getRight());
        }

        if(head != nullptr) {
        delete head;
        head = nullptr;
        }
    }
}

#endif