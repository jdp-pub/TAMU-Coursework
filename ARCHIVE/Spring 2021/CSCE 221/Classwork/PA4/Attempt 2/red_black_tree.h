#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::cout, std::endl;
void nl() {cout << endl; }
void ss() {cout << "~~~~~~~~~~~~~~~" << endl;}
void TestHeader(std::string name, size_t& number){
    cout << "~~~BEGIN TEST SEQUENCE " << number << " : " << name << "~~~" << endl;
    ++number;
    nl();
}

template <typename Comparable>
class RedBlackTree {
 public:
    enum Color {RED, BLACK, DBLeft, DBRight};
    struct Node{
        Comparable value = {};
        Color color = BLACK;

        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
        bool inorderPredecessor = true; //points to inorder traversal predecessor
        bool inorderSuccessor = true;//ponts to inorder successor

        Node(){}
        Node(Comparable x){value = x;}
        Node(Node& x){value = x.getDatum();}
        Node& operator=(const Node other){
            value = other.getDatum();
            inorderPredecessor = other.getLeftT();
            inorderSuccessor = other.getRightT();
            }
        ~Node(){}
        //setters
        void setRight(Node* rightC){ right = rightC; }
        void setLeft(Node* leftC){ left = leftC; }
        void setParent(Node* p){parent = p;}//p for parent
        void setDatum(const Comparable x){ value = x; }
        void flipColor() {if(color == BLACK) {color = RED;} else{color = BLACK;}}
        void setColor(Color c){color = c;}
        void setLeftT(bool T){inorderPredecessor = T;}//T for thread
        void setRightT(bool T){inorderSuccessor = T;}//used for iteration and threading, since the tree is continuous, the nullptr is never reached
        void setLeaf(){inorderSuccessor = true; inorderPredecessor = true;}
        

        //getters
        Node* getRight()  const {return right;}
        Node* getLeft() const {return left;}
        Node* getParent() const {return parent;}
        Color getColor() const{return color;} 
        bool getLeftT() const {return inorderPredecessor;}
        bool getRightT() const {return inorderSuccessor;}
        bool getLeaf() const { return (inorderPredecessor && inorderSuccessor);}
        Comparable getDatum() const {return value;}
        Comparable& getDatum() {return value;}
        Node*  getGrandparent(){return getParent()->getParent(); }
    };
    Node* root = nullptr;
    Node* dummy = nullptr;//used for iteration, when the threads are being followed, this lets us know when to stop

    // TODO(student): implement
    //Constructors
    public:
    RedBlackTree(){}// - makes an empty tree
        
    RedBlackTree(const RedBlackTree& other){// - constructs a copy of the given tree
        if(root != other.getRoot()){
            if(other.getRoot() == nullptr){ make_empty();}
            else{
                make_empty();
                root = new Node;
                dummy = new Node;
                dummy->setLeft(root);
                dummy->setRight(dummy);
                dummy->setParent(root);
                root->setParent(dummy);
                root->setDatum(other.getRoot()->getDatum());
                root->setColor(other.getRoot()->getColor());
                
                init_copy(root, other.getRoot());
                

                Node* cursor = find_min(root);
                
                while(cursor != dummy) { //rethread tree
                    if(cursor->getLeftT() == true){cursor->setLeft(findNextSmallest(cursor));}
                    if(cursor->getRightT() == true){cursor->setRight(findNextLargest(cursor));}
                    if(cursor->getRightT() == true){cursor = cursor->getRight();}
                    else{cursor = find_min(cursor->getRight());}
                }
            }
        }
    }
    ~RedBlackTree(){make_empty();}// - destructs this tree
    RedBlackTree& operator=(const RedBlackTree& other){
        if(root != other.getRoot()){
            if(other.getRoot() == nullptr){ make_empty();}
            else{
                make_empty();
                root = new Node;
                dummy = new Node;
                dummy->setLeft(root);
                dummy->setRight(dummy);
                dummy->setParent(root);
                root->setParent(dummy);
                root->setDatum(other.getRoot()->getDatum());
                root->setColor(other.getRoot()->getColor());
                
                init_copy(root, other.getRoot());

                Node* cursor = find_min(root);
                while(cursor != dummy) { //rethread tree
                    if(cursor->getLeftT() == true){cursor->setLeft(findNextSmallest(cursor));}
                    if(cursor->getRightT() == true){cursor->setRight(findNextLargest(cursor));}

                    if(cursor->getRightT() == true){cursor = cursor->getRight();}
                    else{cursor = find_min(cursor->getRight());}
                }
            }
        }
        return *this;
    }// - assigns a copy of the given tree

    //Element Access

    //Iterators

    //Capacity

    //Modifiers
    void insert(const Comparable& val){// - insert the given lvalue reference into the tree
    
        if(contains(val)) {return;}

        if(root == nullptr){
            dummy = new Node;
            root = new Node;
            root->setDatum(val);
            root->setParent(dummy);
            root->setColor(BLACK);
            
            dummy->setLeft(root);
            dummy->setRight(dummy);
            dummy->setParent(dummy);

            root->setLeftT(true);
            root->setRightT(true);
            root->setLeft(dummy);
            root->setRight(dummy);
            return;
        }

        Node* cursor = root;
        Node* newNode = new Node;
        Node* leftThreadtoNew;
        Node* rightThreadtoNew;
        newNode->setDatum(val);
        newNode->setLeaf();
        newNode->setColor(RED);

        while(cursor != dummy) {
            //process current node
            /*
            1~The textbook has the cases.  The rules are different for bottom-up and top-down trees, so it depends on which way you go.  Assuming you to top-down (which is recommended for efficiency), we have the following rules for insert:
                    2~on the way down, a black parent with 2red kids --> flip the colors
                        3~if the grandparent is also red, do the appropriate AVL rotation and re-color (new "root" is black, kids are red)
            4~after insert, if the parent is red, do the appropriate AVL rotation around grandparent and re-color (new "root" is black, kids are red)
            */

           //1
            if(cursor->getColor() == BLACK){
                if(!cursor->getRightT() && !cursor->getLeftT()){
                    if((cursor->getRight()->getColor() == RED) && (cursor->getLeft()->getColor() == RED)) {
                        cursor->flipColor();
                        cursor->getLeft()->flipColor();
                        cursor->getRight()->flipColor();
                        if(cursor->getParent()->getColor() == RED) {
                            if(cursor == cursor->getParent()->getRight()) {
                                if(cursor->getColor() == RED){cursor->setColor(BLACK);}
                                LL(cursor->getParent());
                                if(!cursor->getRightT()){if(cursor->getRight()->getColor() == BLACK){cursor->getRight()->flipColor();}}
                                if(!cursor->getLeftT()){if(cursor->getLeft()->getColor() == BLACK){cursor->getLeft()->flipColor();}}
                            }
                            else if (cursor == cursor->getParent()->getLeft()) {
                                if(cursor->getColor() == RED){cursor->setColor(BLACK);}
                                RR(cursor->getParent());
                                if(!cursor->getRightT()){if(cursor->getRight()->getColor() == BLACK){cursor->getRight()->flipColor();}}
                                if(!cursor->getLeftT()){if(cursor->getLeft()->getColor() == BLACK){cursor->getLeft()->flipColor();}}
                            }
                            if(cursor->getParent() == dummy) { root = cursor;}
                        }
                    }
                }
            }

            //move cursor and insert
            if(newNode->getDatum() > cursor->getDatum()){ 
                if(!cursor->getRightT()){cursor = cursor->getRight();}
                else {
                    cursor->setRightT(false);
                    cursor->setRight(newNode);
                    newNode->setParent(cursor);
                    leftThreadtoNew = findNextLargest(newNode);
                    rightThreadtoNew = findNextSmallest(newNode);
                    newNode->setLeft(rightThreadtoNew);
                    newNode->setRight(leftThreadtoNew);
                    if(rightThreadtoNew != dummy){if(rightThreadtoNew->getRightT()){rightThreadtoNew->setRight(findNextLargest(rightThreadtoNew));}}
                    if(leftThreadtoNew != dummy){if(leftThreadtoNew->getLeftT()){leftThreadtoNew->setLeft(findNextSmallest(leftThreadtoNew));}}
                    rebalance(newNode);//checks for the rebalancing cases
                    break;
                }
            }
            else if(newNode->getDatum() < cursor->getDatum()){ 
                if(!cursor->getLeftT()){cursor = cursor->getLeft();}
                else {
                    cursor->setLeftT(false);
                    cursor->setLeft(newNode);
                    newNode->setParent(cursor);
                    leftThreadtoNew = findNextLargest(newNode);
                    rightThreadtoNew = findNextSmallest(newNode);
                    newNode->setLeft(rightThreadtoNew);
                    newNode->setRight(leftThreadtoNew);
                    if(rightThreadtoNew != dummy){if(rightThreadtoNew->getRightT()){rightThreadtoNew->setRight(findNextLargest(rightThreadtoNew));}}
                    if(leftThreadtoNew != dummy){if(leftThreadtoNew->getLeftT()){leftThreadtoNew->setLeft(findNextSmallest(leftThreadtoNew));}}
                    rebalance(newNode);
                    break;
                }
            }
        }
        if(root->getColor() == RED) { root->flipColor();}

    }
    void insert(const Comparable&& val){Comparable x = val; insert(x);}
    void remove(const Comparable& val){ //INCOMPLETE // - remove the specified value from the tree (use minimum of right child tree when value has two children)
    /* CASES TO COVER
        1. C ~Deleted node is red and replacement is red or NIL
        2. ~Deleted node is red and {replacemnet is black}
        3. C ~deleted node is black and {replacement is red}
        4. ~deleted node is black and {replacement is black} or {NIL}

        IMPLEMENTATION STEPS
        1. delete node, reorganize threads and parents DONE

        2. color replacement red, rebalance

        3. color replacement black DONE

        4. rebalance

    */
        
        if(!contains(val)){return;}//O(log N)
        Node* cursor = find(val);//O(log N)
        Node* parent = cursor->getParent();
        Node* temp = cursor;

        if(!cursor->getRightT()) { temp = find_min(cursor->getRight());}
        else if(!cursor->getLeftT()) { temp = find_max(cursor->getLeft());}
        Node* tempSibling = nullptr;
        if(temp->getParent()->getLeft() == temp){ if(!temp->getParent()->getRightT()){tempSibling = temp->getParent()->getRight();}}
        if(temp->getParent()->getRight() == temp){ if(!temp->getParent()->getLeftT()){tempSibling = temp->getParent()->getLeft();}}
            

        
        Color delColor = temp->getColor();
        Color sibColor = siblingColor(temp);
        //Color nepColorL = nephewColorL(temp);
        //Color nepColorR = nephewColorR(temp);

        Node* rightThreadtoTemp = findNextSmallest(temp);
        Node* leftThreadtoTemp = findNextLargest(temp);

        if(cursor == root){
            if(cursor->getLeaf()){make_empty();}
            if(!cursor->getLeftT() && !cursor->getRightT()) {//two subtrees
                if(delColor == BLACK){
                    parent = temp->getParent();
                    if(temp->getLeaf()) {//deleted node is leaf
                        cursor->setDatum(temp->getDatum());
                        if(temp == temp->getParent()->getLeft()){
                            parent->setRightT(true);
                            parent->setRight(findNextSmallest(parent));
                            delete temp;
                        }
                        else if(temp == temp->getParent()->getRight()){
                            parent->setLeftT(true);
                            parent->setLeft(findNextLargest(parent));
                            delete temp;
                        }
                    }
                    else {//deleted node has subtrees
                        cursor->setDatum(temp->getDatum());

                        if(temp == temp->getParent()->getLeft()){
                            if(!temp->getRightT()){ parent->setLeft(temp->getRight());}
                            else if(!temp->getLeftT()){ parent->setLeft(temp->getLeft());}
                            parent->getLeft()->setParent(parent);
                            delete temp;
                        }
                        else if(temp == temp->getParent()->getRight()){
                            if(!temp->getRightT()){ parent->setRight(temp->getRight());}
                            else if(!temp->getLeftT()){ parent->setRight(temp->getLeft());}
                            parent->getRight()->setParent(parent);
                            delete temp;
                        }
                    }

                    if(sibColor == BLACK) {
                        if(tempSibling != nullptr) {tempSibling->setColor(tempSibling->getParent()->getColor());}
                        parent->setColor(BLACK);

                        if(tempSibling == parent->getRight()){
                            if(!tempSibling->getRightT()) { tempSibling->getRight()->setColor(BLACK);}
                            print_tree();
                            LL(tempSibling->getParent());
                        }
                        else if(tempSibling == parent->getLeft()){
                            if(!tempSibling->getLeftT()) { tempSibling->getLeft()->setColor(BLACK);}
                            RR(tempSibling->getParent());
                        }  
                    }
                }
                else if(delColor == RED) {// CASE 3 : REPLACE BLACK WITH RED
                parent = temp->getParent();
                    if(temp == parent->getRight()){//temp is a right child
                        if(!temp->getLeaf()) {
                            if(!temp->getLeftT()){
                                parent->setRight(temp->getLeft());
                                parent->getRight()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                            else if(!temp->getRightT()){
                                parent->setRight(temp->getRight());
                                parent->getRight()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                        }
                        else{
                            parent->setRightT(true); 
                            parent->setRight(findNextLargest(parent));
                            cursor->setDatum(temp->getDatum());
                            delete temp;
                        }         
                    }
                    else if(temp == parent->getLeft()){//temp is a left child
                        if(!temp->getLeaf()) {
                            if(!temp->getLeftT()){
                                parent->setLeft(temp->getLeft());
                                parent->getLeft()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                            else if(!temp->getRightT()){
                                parent->setLeft(temp->getRight());
                                parent->getLeft()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                        }
                        else{
                            parent->setLeftT(true); 
                            parent->setLeft(findNextSmallest(parent));
                            cursor->setDatum(temp->getDatum());
                            delete temp;
                        }
                    }
                }
            }
            else if(cursor->getLeftT() && !cursor->getRightT()){ //right subtree
                dummy->setLeft(cursor->getRight());
                cursor->getRight()->setParent(dummy);
                delete cursor;
            }
            else if(!cursor->getLeftT() && cursor->getRightT()){ //left subtree
                dummy->setLeft(cursor->getLeft());
                cursor->getLeft()->setParent(dummy);
                delete cursor;
            }
            if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
            if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
            return;
        }

        if(cursor->getColor() == RED){ //RED, always either leaf node or has two children
            
            if(cursor->getLeaf()){ // no subtrees Case 1. replacement is NIL
                parent = cursor->getParent();
                if(cursor == parent->getLeft()){
                    
                    parent->setLeftT(true);
                    delete cursor;
                    parent->setLeft(findNextSmallest(parent));
                    if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
                    if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
                    return;
                }
                if(cursor == parent->getRight()){
                    parent->setRightT(true);
                    delete cursor;
                    parent->setRight(findNextLargest(parent));
                    if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
                    if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
                    return;
                }
            }
            else{ //has two subtrees
                temp = find_min(cursor->getRight());
                parent = temp->getParent();// temp is red
                    //temp parent takes over right subtree
                    Node* rightThreadtoTemp = findNextSmallest(temp);
                    Node* leftThreadtoTemp = findNextLargest(temp);
                    if(temp->getLeaf()){
                        if(temp == parent->getRight()){
                            // case 2 : temp is a right child, in order for this to happen, temp must be black, replced by NIL
                                parent->setRightT(true); 
                                parent->setRight(findNextLargest(parent));
                                cursor->setDatum(temp->getDatum());
                                cursor->flipColor();
                                cursor->getLeft()->flipColor();
                                delete temp;
                        }
                        else if(temp == parent->getLeft()){//case 1  : temp is a left child, replacement is RED
                            if(!temp->getRightT()){
                                parent->setLeft(temp->getRight());
                                parent->getLeft()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                cursor->setColor(temp->getColor());
                                delete temp;
                            }
                            else{
                                parent->setLeftT(true); 
                                parent->setLeft(findNextSmallest(parent));
                                cursor->setDatum(temp->getDatum());
                                cursor->setColor(temp->getColor());
                                delete temp;
                                }
                        }
                        if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
                        if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
                    }
                    else{//temp has subtrees
                        if(temp->getColor() == BLACK) {
                            if(temp == parent->getRight()){// case 2 : temp is a right child
                                if(!temp->getRightT()){
                                    parent->setRight(temp->getRight());
                                    parent->getRight()->setParent(parent);
                                    cursor->setDatum(temp->getDatum());
                                    if(parent->getRight()->getColor() == RED){parent->getRight()->flipColor();}
                                    else{}
                                    delete temp;
                                }
                                else{
                                    parent->setRightT(true); 
                                    parent->setRight(findNextLargest(parent));
                                    cursor->setDatum(temp->getDatum());
                                    delete temp;
                                }
                            }
                            else if(temp == parent->getLeft()){

                            }
                        }
                            if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
                            if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
                    
                    }
                }
            
            return; 
            ///////END OF RED NODE CASE
        }
        else{//node is black
            if(temp->getLeaf()){//Case 4 : BLACK REPLACED WITH NIL

            }
            else{
                if(!cursor->getRightT()){temp = find_min(cursor->getRight());}
                else{temp = find_max(cursor->getLeft());}

                parent = temp->getParent();
                if(temp->getColor() == RED) {// CASE 3 : REPLACE BLACK WITH RED
                    if(temp == parent->getRight()){//temp is a right child
                        if(temp->getLeftT() || temp->getRightT()) {
                            if(!temp->getLeftT()){
                                parent->setRight(temp->getLeft());
                                parent->getRight()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                            else if(!temp->getRightT()){
                                parent->setRight(temp->getRight());
                                parent->getRight()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                        }
                        else{
                            parent->setRightT(true); 
                            parent->setRight(findNextLargest(parent));
                            cursor->setDatum(temp->getDatum());
                            delete temp;
                        }         
                    }
                    else if(temp == parent->getLeft()){//temp is a left child
                        if(temp->getLeftT() || temp->getRightT()) {
                            if(!temp->getLeftT()){
                                parent->setLeft(temp->getLeft());
                                parent->getLeft()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                            else if(!temp->getRightT()){
                                parent->setLeft(temp->getRight());
                                parent->getLeft()->setParent(parent);
                                cursor->setDatum(temp->getDatum());
                                delete temp;
                            }
                        }
                        else{
                            parent->setLeftT(true); 
                            parent->setLeft(findNextSmallest(parent));
                            cursor->setDatum(temp->getDatum());
                            delete temp;
                        }
                    }
                }
                else{// CASE 4: REPLACE BLACK WITH BLACK
                    if(!temp->getLeaf()){//deleted node has subtrees
                        cursor->setDatum(temp->getDatum());
                        if(temp == temp->getParent()->getLeft()){
                            if(!temp->getRightT()){ parent->setLeft(temp->getRight());}
                            else if(!temp->getLeftT()){ parent->setLeft(temp->getLeft());}
                            parent->getLeft()->setParent(parent);
                            delete temp;
                        }
                        else if(temp == temp->getParent()->getRight()){
                            if(!temp->getRightT()){ parent->setRight(temp->getRight());}
                            else if(!temp->getLeftT()){ parent->setRight(temp->getLeft());}
                            parent->getRight()->setParent(parent);
                            delete temp;
                        }
                    }

                    if(sibColor == BLACK) {
                        if(tempSibling != nullptr) {tempSibling->setColor(tempSibling->getParent()->getColor());}
                        parent->setColor(BLACK);

                        if(tempSibling == parent->getRight()){
                            if(!tempSibling->getRightT()) { tempSibling->getRight()->setColor(BLACK);}
                            LL(tempSibling->getParent());
                        }
                        else if(tempSibling == parent->getLeft()){
                            if(!tempSibling->getLeftT()) { tempSibling->getLeft()->setColor(BLACK);}
                            RR(tempSibling->getParent());
                        }
                        
                    }
                }
            if(rightThreadtoTemp != dummy){if(rightThreadtoTemp->getRightT()){rightThreadtoTemp->setRight(findNextLargest(rightThreadtoTemp));}}
            if(leftThreadtoTemp != dummy){if(leftThreadtoTemp->getLeftT()){leftThreadtoTemp->setLeft(findNextSmallest(leftThreadtoTemp));}}
            return;
            }
        }
        
    }

    //Lookup
    bool contains(const Comparable& val) const{// - returns Boolean true if the specified value is in the tree
        if(root == nullptr){return false;} 
        return (val == find(val)->getDatum());
    }
    const Comparable& find_min() const{// - return the minimum value in the tree or throw std::invalid_argument if the tree is empty
        try{if(root == nullptr){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        Node* cursor = root;
        while(cursor != dummy) {
        if(cursor->getLeftT() != true) {cursor = cursor->getLeft();}
        if(cursor->getLeftT() == true) {return cursor->getDatum();}
        }
        return cursor->getDatum();
    }
    const Comparable& find_max() const{// - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
        try{if(root == nullptr){throw 1;}}
        catch(int n){throw std::invalid_argument("find_max() of empty tree.");}
        Node* cursor = root;
        while(cursor != dummy) {
        if(cursor->getRightT() != true) {cursor = cursor->getRight();}
        if(cursor->getRightT() == true) {return cursor->getDatum();}
        }
        return cursor->getDatum();
    }
    Node* find_max(Node* cursor) const{// - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
        try{if(cursor == nullptr){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        while(cursor != dummy) {
        if(cursor->getRightT() != true) {cursor = cursor->getRight();}
        else if(cursor->getRightT() == true) {return cursor;}
        }
        return cursor;
    }
    Node* find_min(Node* cursor) const{// - return the maximum value in the tree or throw std::invalid_argument if the tree is empty
        try{if(cursor == nullptr){throw 1;}}
        catch(int n){throw std::invalid_argument("find_min() of empty tree.");}
        while(cursor != dummy) {
        if(cursor->getLeftT() != true) {cursor = cursor->getLeft();}
        else if(cursor->getLeftT() == true) {return cursor;}
        }
        return cursor;
    }
    Node* find(const Comparable& val) const{//O(log N)
        if(root == nullptr){return nullptr;}
        
        
        Node* cursor = root;
        while(cursor->getDatum() != val) {
        if((cursor->getDatum() < val) && (cursor->getRightT() != true)) {cursor = cursor->getRight();}
        if((cursor->getDatum() > val) && (cursor->getLeftT() != true)) {cursor = cursor->getLeft();}
        if(cursor->getDatum() == val) {return cursor;}
        
        if((cursor->getDatum() < val) && (cursor->getRightT() == true)) {return cursor;}
        if((cursor->getDatum() > val) && (cursor->getLeftT() == true)) {return cursor;}
        }
        return cursor;
    }
    Node* findNextSmallest(Node* pin) {
        //int forcebreak = 10;
        Node* cursor = root;
        while((cursor != pin)) {
            if(cursor->getLeftT() != true) {
                if(pin->getDatum() < cursor->getDatum()){ cursor = cursor->getLeft();}
            }
            if(cursor->getRightT() != true) {
                if(pin->getDatum() > cursor->getDatum()){
                    
                    if(find_min(cursor->getRight()) == pin) {return cursor;}
                    cursor = cursor->getRight();
                }
            }
        }
        if(cursor == pin) {return dummy;}
        return cursor;
    }
    Node* findNextLargest(Node* pin) {
        Node* cursor = root;
        while(cursor != pin) { 
            if(cursor->getLeftT() != true) {
                if(pin->getDatum() < cursor->getDatum()){
                    if(find_max(cursor->getLeft()) == pin) {return cursor;}
                    cursor = cursor->getLeft();
                    }
            }
            if(cursor->getRightT() != true) {
                if(pin->getDatum() > cursor->getDatum()) {cursor = cursor->getRight();}
            }
        }
        if(cursor == pin) {return dummy;}
        return cursor;
    }
    Node* findParent(Node* pin) {
        Node* parent = pin;
        if(parent != pin){
            while((parent->getLeft() != pin) && (parent->getRight() != pin)){
                if(pin->getDatum() > parent->getDatum()) {parent = parent->getRight();}
                else if(pin->getDatum() < parent->getDatum()) {parent = parent->getLeft();}
            }
        }
        return parent;
    }
    Node* findNephewL(Node* pin) {
        if(pin == pin->getParent()->getRight()){
            if(pin->getParent()->getLeftT() == true) {return dummy;}
            else{
                if(pin->getParent()->getLeft()->getLeftT() == true){return dummy;}
                return pin->getParent()->getLeft()->getLeft();
            }
        }
        if(pin == pin->getParent()->getLeft()){
            if(pin->getParent()->getRightT() == true) {return dummy;}
            else{
                if(pin->getParent()->getRight()->getLeftT() == true){return dummy;}
                return pin->getParent()->getRight()->getLeft();
            }
        }
        return dummy;
    }
    Node* findNephewR(Node* pin) {
        if(pin == pin->getParent()->getRight()){
            if(pin->getParent()->getLeftT() == true) {return dummy;}
            else{
                if(pin->getParent()->getLeft()->getRightT() == true){return dummy;}
                return pin->getParent()->getLeft()->getRight();
            }
        }
        if(pin == pin->getParent()->getLeft()){
            if(pin->getParent()->getRightT() == true) {return dummy;}
            else{
                if(pin->getParent()->getRight()->getRightT() == true){return dummy;}
                return pin->getParent()->getRight()->getRight();
            }
        }
        return dummy;
    }
    Node* findSibling(Node* pin){
        if(pin == pin->getParent()->getRight()){
            if(pin->getParent()->getLeftT() == true) {return dummy;}
            else{
                return pin->getParent()->getLeft();
            }
        }
        if(pin == pin->getParent()->getLeft()){
            if(pin->getParent()->getRightT() == true) {return dummy;}
            else{
                return pin->getParent()->getRight();
            }
        }
        return dummy;
    }
    
    //Visualization
    //Optional

    //For Testing
    int color(const Node* node) const{if(node != nullptr){return node->color;} else{return BLACK;}}// - return the color of the specified node (the null pointer is black).  This function is required to be public by the instructor’s tests.
    const Node* get_root() const {return root;}
    const Node* getRoot() const{return root;}// - return the root of the tree or nullptr if the tree is empty. This function is required by the instructor’s tests.
    Node* getDummy() const {return dummy;} 

    //Optional
    RedBlackTree(RedBlackTree&&){}// - move constructs a copy of the given (rvalue) tree
    RedBlackTree& operator=(RedBlackTree&&){}// - move assigns a copy of the given (rvalue) tree
    bool is_empty() const{return !(root);}// - returns Boolean true if the tree is empty
    void make_empty(){if(root != nullptr){empty(root); root = nullptr; delete dummy; dummy = nullptr;}}// - remove all values from the tree
    void empty(Node* cursor){
        if(cursor->getLeftT() != true){empty(cursor->getLeft());}
        if(cursor->getRightT() != true){empty(cursor->getRight());}
        delete cursor;
    }// - remove all values from the tree
    void print_tree() const {// const - pretty print the tree
        if(root == nullptr) {std::cout << "<empty>\n"; return;}
        reverse_inorder(std::cout, root, 0);
    }
    void reverse_inorder(std::ostream& os, Node* cursor, size_t indent) const{//recursive os load
        if(cursor->getRightT() != true) {reverse_inorder(os, cursor->getRight(), indent + 2);}

        for(size_t i = 0; i < indent; ++i) { os << " "; }
        if(cursor->getColor() == RED){os << "R:";}
        os << cursor->getDatum() << std::endl;

        if(cursor->getLeftT() != true) {reverse_inorder(os, cursor->getLeft(), indent + 2);}
    }
    void inorder() {
        if(root == nullptr){return;}
        Node* cursor = find_min(root);
        while(cursor != dummy) {
            cout << cursor->getDatum();
            if(cursor ->getRight() == dummy) {break;}
            cout << ", ";
            if(cursor->getRightT() == true){cursor = cursor->getRight();}
            else{cursor = find_min(cursor->getRight());}
        }
        cout << endl;
    }
    void LL(Node* pin){
        Node* cursor = pin->getRight();

        pin->setRight(cursor->getLeft());
        cursor->setLeft(pin);

        

       
        Node* parent = pin->getParent();
        cursor->setParent(parent);
        pin->setParent(cursor);

        

        if(pin == parent->getLeft()) {parent->setLeft(cursor); }
        if(pin == parent->getRight()) {parent->setRight(cursor);}

        if(pin == root) {root = cursor;}
        if(cursor->getLeftT() == true) {
            cursor->setLeftT(false);
            pin->setRightT(true);
            pin->setRight(findNextLargest(pin));
        }
        else{pin->getRight()->setParent(pin);}

    }
    void RR(Node* pin){
            Node* cursor = pin->getLeft();
            pin->setLeft(cursor->getRight());
            cursor->setRight(pin);

            Node* parent = pin->getParent();
            cursor->setParent(parent);
            pin->setParent(cursor);
            
            if(pin == parent->getLeft()) {parent->setLeft(cursor);}
            if(pin == parent->getRight()) {parent->setRight(cursor);}

            if(pin == root) {root = cursor;}
            if(cursor->getRightT() == true) {
                cursor->setRightT(false);
                pin->setLeftT(true);
                pin->setLeft(findNextSmallest(pin));   
            }
            else{pin->getLeft()->setParent(pin);}
    }
    void rebalance(Node* cursor) {
         //4~after insert, if the parent is red, do the appropriate AVL rotation around grandparent and re-color (new "root" is black, kids are red)

        if(cursor->getParent()->getColor() == RED){
            if(cursor->getParent() == cursor->getGrandparent()->getRight()) {
                if(cursor == cursor->getParent()->getLeft()) { 
                    RR(cursor->getParent()); 
                    LL(cursor->getParent());
                    cursor->flipColor();
                    if(!cursor->getLeftT()){cursor->getLeft()->flipColor();}
                }
                else{
                    LL(cursor->getGrandparent());
                    Node* sib = findSibling(cursor);
                    if((sib != dummy) && (sib->getColor() == BLACK))->flipColor();
                    if(cursor->getParent()->getColor() == RED){cursor->getParent()->flipColor();}
                    if(cursor->getColor() != RED){cursor->flipColor();}
                }
            }
            else if (cursor->getParent() == cursor->getGrandparent()->getLeft()) {
                if(cursor == cursor->getParent()->getRight()) { 
                    LL(cursor->getParent()); 
                    RR(cursor->getParent());
                    cursor->flipColor();
                    if(!cursor->getRightT()){cursor->getRight()->flipColor();}
                }
                else{
                    RR(cursor->getGrandparent());
                    findSibling(cursor)->flipColor();
                    cursor->getParent()->flipColor();
                }
            }
        }
    }
    void init_copy(Node* CursorSelf, const Node* CursorOther) {
        if(CursorOther->getLeftT() != true) { 
            Node* temp = new Node;
            temp->setDatum(CursorOther->getLeft()->getDatum());
            CursorSelf->setLeft(temp);
            temp->setParent(CursorSelf);
            CursorSelf->setLeftT(false);
            init_copy(temp, CursorOther->getLeft());
        }
        else{CursorSelf->setLeftT(true);}
        if(CursorOther->getRightT() != true) { 
            Node* temp = new Node;
            temp->setDatum(CursorOther->getRight()->getDatum());
            CursorSelf->setRight(temp);
            temp->setParent(CursorSelf);
            CursorSelf->setRightT(false);
            init_copy(temp, CursorOther->getRight());
        }
        else{CursorSelf->setRightT(true);}

        CursorSelf->setColor(CursorOther->getColor());

    }
    void nodeInfo(const Node* pin) const {
        std::string c;

        if(pin->getColor() == BLACK){c = "BLACK";}
        else{c = "RED";}
        ss();
        cout << "Node " << pin << " : " << c << " : " << pin->getDatum() << endl
             << "Parent : " << pin->getParent()->getDatum() << endl
             << "Left threaded? : " << pin->getLeftT() << endl
             << "Right threaded? : " << pin->getRightT() << endl
             << "Left child : " << pin->getLeft()->getDatum() << endl
             << "Right child : "<< pin->getRight()->getDatum() << endl;
        ss();
    }
};
#endif  // RED_BLACK_TREE_H