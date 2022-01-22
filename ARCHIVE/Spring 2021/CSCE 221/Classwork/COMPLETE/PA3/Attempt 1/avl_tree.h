#ifndef AVL_TREE_H
#define AVL_TREE_H

using std::cout, std::endl;

void r() {cout << "||||  test  ||||" << endl;}

template <typename Comparable>
class Node {
    Comparable datum = 0;
    

    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    public:
    size_t depth = 0;
    Node() {}
    Node(Comparable x) {datum = x;}
    ~Node(){}

    void setRight(Node* right){ rightChild = right; }
    void setLeft(Node* left){ leftChild = left; }
    void setDatum(const Comparable x){ datum = x; }

    Node* getRighr() {return rightChild;}
    Node* getLefr() {return leftChild;}
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
class AVLTree {
    Node<Comparable>* root = nullptr;

    public:
    AVLTree();// - makes an empty tree
    AVLTree(const AVLTree&);// - constructs a copy of the given tree
    ~AVLTree();// - destructs this tree
    AVLTree& operator=(const AVLTree&);// - assigns a copy of the given tree
    bool contains(const Comparable&);// const - returns Boolean true if the specified value is in the tree
    void insert(const Comparable&);// - insert the given value into the tree
    void remove(const Comparable&);// - remove the specified value from the tree (use minimum of right child tree when value has two children)
    Comparable& find_min() const;// - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    Comparable& find_max() const;// - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    void print_tree(std::ostream&) const;// - pretty print the tree (rotated 90 degrees to the left, two spaces per level; see example below) to the specified output stream (default std::cout).  Print “<empty>\n” if the tree is empty.

    //helpers
    void dele(Node<Comparable>*);
    void init_copy(Node<Comparable>*, Node<Comparable>*);
    Node<Comparable>* findLoc(Node<Comparable>*, const Comparable&, size_t&);
    Node<Comparable>* getRoor() const;
    void reverse_inorder(std::ostream&, Node<Comparable>*, size_t) const;
    void rebalance(Node<Comparable>*);
    void LL(Node<Comparable>*);
    void RR(Node<Comparable>*);
    size_t findheight(Node<Comparable>*, size_t&);
};

template <typename Comparable>
AVLTree<Comparable>::AVLTree(){}

template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree& other){
    this->root = new Node<Comparable>;
    root->setDatum(other.getRoor()->getDatum());
    init_copy(root, other.getRoor());
}

template <typename Comparable>
AVLTree<Comparable>::~AVLTree(){ 
    if(root != nullptr) {AVLTree<Comparable>::dele(this->root);} }

template <typename Comparable>
void AVLTree<Comparable>::insert(const Comparable& val){
    Node<Comparable>* newnode = new Node<Comparable>;
    cout << "inserting " << val << "..." << endl;
    newnode->setDatum(val);

    if(root == nullptr) {root = newnode; return;}
    size_t dep = 0;
    Node<Comparable>* cursor = findLoc(this->root, val, dep);
    if(val > cursor->getDatum()){
        cursor->setRight(newnode);
    }
    if(val < cursor->getDatum()){
        cursor->setLeft(newnode);
    }
    newnode->depth = dep;
    rebalance(root);
}

template <typename Comparable>
Node<Comparable>* AVLTree<Comparable>::findLoc (Node<Comparable>* roots, const Comparable& val, size_t& dep) {
    Node<Comparable>* cursor = roots;
    while(cursor != nullptr) {
        //cout << cursor << endl;
        if(cursor->getDatum() > val) {
            if(cursor->getLefr() == nullptr) { ++dep; return cursor; }
            else {cursor = cursor->getLefr(); ++dep;}
        }
        if(cursor->getDatum() < val) {
            if(cursor->getRighr() == nullptr) { ++dep; return cursor; }
            else {cursor = cursor->getRighr(); ++dep;}
        }
    }
    return nullptr;
}


template <typename Comparable>
void AVLTree<Comparable>::init_copy(Node<Comparable>* CursorSelf, Node<Comparable>* CursorOther) {
    if(CursorOther->getLefr() != nullptr) { 
        Node<Comparable>* temp = new Node<Comparable>;
        temp->setDatum(CursorOther->getLefr()->getDatum());
        temp->depth = CursorOther->getLefr()->depth;
        CursorSelf->setLeft(temp);
        init_copy(temp, CursorOther->getLefr());
    }
    if(CursorOther->getRighr() != nullptr) { 
        Node<Comparable>* temp = new Node<Comparable>;
        temp->setDatum(CursorOther->getRighr()->getDatum());
        temp->depth = CursorOther->getRighr()->depth;
        CursorSelf->setRight(temp);
        init_copy(temp, CursorOther->getRighr());
    }

}

template <typename Comparable>
Node<Comparable>* AVLTree<Comparable>::getRoor() const {return root;}

template <typename Comparable>
AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree& other){
    dele(root);
    this->root = new Node<Comparable>;
    root->setDatum(other.getRoor()->getDatum());
    root->depth = other.getRoor()->depth;
    init_copy(root, other.getRoor());
    return *this;
}

template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& other){
    Node<Comparable>* cursor = root;
    while(cursor != nullptr) {
        if(cursor->getDatum() > other) {cursor = cursor->getLefr();}
        else if(cursor->getDatum() < other) {cursor = cursor->getRighr();}
        else if(cursor->getDatum() == other) {return true;}
    }
    return false;
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& val){
    if(!contains(val)){cout << "This value is not in this tree." << endl; return;}
    Node<Comparable>* cursor = root;
    if(cursor->children() == "none") { delete cursor; root = nullptr; return;}
    Node<Comparable>* parent;

    while(cursor != nullptr) {
        if(cursor->getDatum() > val) { 
            parent = cursor;
            cursor = cursor->getLefr(); 
        }
        else if(cursor->getDatum() < val) { 
            parent = cursor;
            cursor = cursor->getRighr(); 
        }
        else if(cursor->getDatum() == val) {break;}
    }
    if(cursor == nullptr) {return;}
    //r();
    Node<Comparable>* pin = cursor;
    cout << "pin: " << pin->getDatum() << endl;
    cout << "children: " << pin->children() << endl;
    if(pin->children() == "both") {
        //r();
        //cout << "parent: " << parent->children() << endl;
        parent = cursor;
        cursor = cursor->getRighr();
        while(cursor->getLefr() != nullptr) {
            parent = cursor;
            cursor = cursor->getLefr();
            //r();
            }
            cout << "parent: " << parent->getDatum() << endl;
            cout << "cursor: " << cursor->getDatum() << endl;
            cout << "pin: " << pin->getDatum() << endl;

        pin->setDatum(cursor->getDatum());
        if(parent->children() == "left"){
        parent->setLeft(cursor->getRighr());
        delete cursor;
        return;}

        parent->setRight(cursor->getRighr());
        //if(parent->children() == "both"){parent->setLeft(nullptr);}
        delete cursor;
        return;
        //r();
        
        
    }
    else if(pin->children() == "none") {
        if(parent->getLefr() == pin) { parent->setLeft(nullptr);}
        if(parent->getRighr() == pin) {parent->setRight(nullptr);}

        delete pin;
        return;
    }
    else if(pin->children() == "left") {
        if(parent->children() == "right"){
       parent->setRight(pin->getLefr());
        delete pin; 
        return;
        }
        //r();
        parent->setLeft(pin->getLefr());
        delete pin; 
        return;
    }
    else if(pin->children() == "right") {
        if(parent->children() == "right") {
        parent->setRight(pin->getRighr());
        delete pin;
        return;
        }
        parent->setLeft(pin->getRighr());
        delete pin;
        return;
    }
}

template <typename Comparable>
Comparable& AVLTree<Comparable>::find_min() const{
    try{if(root == nullptr) {throw 1;}}
    catch(int n) {throw std::invalid_argument("No values withing tree.");}
    Node<Comparable>* cursor = root;
    while(cursor->getLefr() != nullptr) { cursor = cursor->getLefr(); }
    return cursor->getDatum();
}

template <typename Comparable>
Comparable& AVLTree<Comparable>::find_max() const{
    try{if(root == nullptr) {throw 1;}}
    catch(int n) {throw std::invalid_argument("No values withing tree.");}
    Node<Comparable>* cursor = root;
    while(cursor->getRighr() != nullptr) { cursor = cursor->getRighr(); }
    return cursor->getDatum();
}

template <typename Comparable>
void AVLTree<Comparable>::print_tree(std::ostream& os) const {
    if(root == nullptr) {os << "<empty>\n"; return;}
    reverse_inorder(os, root, 0);
}

template <typename Comparable>
void AVLTree<Comparable>::reverse_inorder(std::ostream& os, Node<Comparable>* cursor, size_t indent) const{
    if(cursor->getRighr() != nullptr) {reverse_inorder(os, cursor->getRighr(), indent + 2);}

    for(size_t i = 0; i < indent; ++i) { os << "  "; }
    os << cursor->getDatum() << endl;

    if(cursor->getLefr() != nullptr) {reverse_inorder(os, cursor->getLefr(), indent + 2);}

    
}

template <typename Comparable>
void AVLTree<Comparable>::dele(Node<Comparable>* head) {

    if(head == nullptr) {}
    else{
        if(head->getLefr() != nullptr) {
            dele(head->getLefr());
        }
        if(head->getRighr() != nullptr) {
            dele(head->getRighr());
        }

        if(head != nullptr) {
        delete head;
        head = nullptr;
        }
    }
}

template <typename Comparable>
void AVLTree<Comparable>::rebalance(Node<Comparable>* cursor) {
    if(cursor->getRighr() != nullptr) {rebalance(cursor->getRighr());}
    if(cursor->getLefr() != nullptr) {rebalance(cursor->getLefr());}

    size_t lheight = 0;
    size_t rheight = 0;
    
    int lh = findheight(cursor->getLefr(), lheight);
    int rh = findheight(cursor->getLefr(), rheight);

    int dh = lh - rh;
    if(dh > 1){ LL(cursor); }
    if(dh < -1){ RR(cursor); }
}

template <typename Comparable>
size_t AVLTree<Comparable>::findheight(Node<Comparable>* cursor, size_t& height) {
    if(cursor == nullptr) {return -1;}
    if(cursor->getRighr() != nullptr) {height = findheight(cursor->getRighr(), height+=1);}
    if(cursor->getLefr() != nullptr) {height = findheight(cursor->getLefr(),height+=1);}
    return height;

}
template <typename Comparable>
    void AVLTree<Comparable>::RR(Node<Comparable>* cursor){
        Node<Comparable>* parent = root;
        while(parent->getLefr() != cursor && parent->getRighr() != cursor){
            if(cursor->getDatum() == parent->getDatum()){break;}
            if(cursor->getDatum() > parent->getDatum()){parent = parent->getRighr();}
            if(cursor->getDatum() < parent->getDatum()){parent = parent->getLefr();}
        }

        if(parent == cursor) {}

        parent->setRight(cursor->getLefr());
        cursor->setLeft(nullptr);

    }
    template <typename Comparable>
    void AVLTree<Comparable>::LL(Node<Comparable>* cursor){
        Node<Comparable>* parent = root;
        while(parent->getLefr() != cursor && parent->getRighr() != cursor){
            if(cursor->getDatum() == parent->getDatum()){break;}
            if(cursor->getDatum() > parent->getDatum()){parent = parent->getRighr();}
            if(cursor->getDatum() < parent->getDatum()){parent = parent->getLefr();}
        }

        parent->setLeft(cursor->getRighr());
        cursor->setRight(nullptr);
    }

#endif