#include <vector>
#include <iostream>

using std::vector, std::cout, std::endl;

class Node {
    int datum = 0;

    Node* leftChild = nullptr;
    Node* rightChild = nullptr;

    public:
    Node() {}
    Node(int x) {datum = x;}
    ~Node(){}

    void setRight(Node* right){ rightChild = right; }
    void setLeft(Node* left){ leftChild = left; }
    void setDatum(int x){ datum = x; }

    Node* getRight() {return rightChild;}
    Node* getLeft() {return leftChild;}
    int getDatum() {return datum;}
};

class Tree{
    Node* root = nullptr;

    public:
    Tree(vector<int> x){
        root = new Node(x.at(0));
        init(root, x, 1);
    }
    ~Tree(){ dele(root); }

    Node* findLoc(Node* roots, int val) {
        Node* cursor = roots;
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

    void init(Node* start, vector<int> vals, size_t index) {
        Node* head = nullptr;
        Node* cursor = nullptr;

        if(index < vals.size()) {
            
            head = new Node(vals.at(index));
            
            cursor = findLoc(start, vals.at(index));
            if(cursor == nullptr) {return;}
            if(cursor->getDatum() > head->getDatum()) {
                cursor->setLeft(head);
            }
            if(cursor->getDatum() < head->getDatum()) {
                cursor->setRight(head);
            }
            
            
            init(start, vals, index +1);
        } 
    }

    Node* getRoot() {return root;}

    void print(Node* head) {

        if(head != nullptr) {
            if(head->getLeft() != nullptr) {
                cout << "Node : " << head->getDatum() << endl;
                cout << "Left Child : " << head->getLeft()->getDatum() << endl;
                print(head->getLeft());
            }
            if(head->getRight() != nullptr) {
                cout << "Node : " << head->getDatum() << endl;
                cout << "Right Child : "<< head->getRight()->getDatum() << endl;
                print(head->getRight());
            }
        }
    }

    void dele(Node* head) {

        if(head->getLeft() != nullptr) {
            dele(head->getLeft());
        }
        if(head->getRight() != nullptr) {
            dele(head->getRight());
        }

        if(head != nullptr) {
        delete head;
        }
    }

    int countNodes(Node* head) {// counts all of the nodes in a tree recursively
        if(head==nullptr) {return 0;} //covers the case of being fed the nullptr by the user
        int num = 0;

        if(head->getLeft() != nullptr) { num += countNodes(head->getLeft()); } //each statement creates a new sum recursively, first
        if(head->getRight() != nullptr) { num += countNodes(head->getRight()); }// by adding all of the left children, then adding the 
                                                                                // right children
        return num + 1;//increments every iteration
    }

    int countLeaves(Node* head) {// same function as part a except only counts under the condition that the node has no children
        int num = 0;
        if(head==nullptr) {return 0;}//covers the case of being fed the nullptr by the user

        if(head->getLeft() != nullptr) { num += countLeaves(head->getLeft()); }
        if(head->getRight() != nullptr) { num += countLeaves(head->getRight()); }
        if(head->getLeft() == nullptr && head->getRight() == nullptr){ return num + 1; }

        return num;
    }

    int countFull(Node* head) {//same function as part a except only counts under the condition that the node has two children
        int num = 0;
        if(head==nullptr) {return 0;}//covers the case of being fed the nullptr by the user

        if(head->getLeft() != nullptr) { num += countFull(head->getLeft()); }
        if(head->getRight() != nullptr) { num += countFull(head->getRight()); }
        if(head->getLeft() != nullptr && head->getRight() != nullptr){ return num + 1; }

        return num;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ PROBLEM SET 10
    void LR(Node* groot) {
        Node* c1 = groot; //pointer 1
        Node* c2 = groot->getLeft(); //pointer 2, both are shown in diagrams for previous problems

        //this will be completed in as few steps as possible
        c1->setLeft(c2->getRight()->getLeft()); //rotating node takes over left and right subtrees for left childs right subtree
        c1->setRight(c2->getRight()->getRight());
        c2->getRight()->setRight(c1);

        //second pointer now takes over for the left subtree of the same node
        this->root = c2->getRight(); //updates parent node, this function only changes the root node
        c2->setRight(root->getLeft());// takes over for left subtree
        root->setLeft(c2);



    }
};