#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <typename Object>
class Node {
    Object datum = {};

    Node* prev = nullptr;
    Node* next = nullptr;


    public:
    Node() {}
    Node(const Node&) {}
    Node operator=(const Node&) {}
    ~Node() {}

    void setPrev(Node* newPrev) {prev = newPrev;}
    void setNext(Node* newNext) {next = newNext;}

    Node* getNext() {return next;}
    Node* getPrev() {return prev;}

    void setDatum(Object newDatum) { datum = newDatum; }
    Object& getDatum() { return datum; }
};

template <typename Object>
class DoublyLinkedList {
    // TODO(student): implement DoublyLinkedList
    Node<Object>* head = nullptr;
    Node<Object>* cursor = nullptr;
    Node<Object>* tail = nullptr;
    Node<Object>* previous = nullptr;

    size_t elements = 0;

    public:
    //COMPLETE
    DoublyLinkedList() {} //- makes an empty list

    //Rule of Three
    //COMPLETE
    DoublyLinkedList(const DoublyLinkedList& other) {
        if(other.size() > 0) {
            elements = other.size();

            head = new Node<Object>;
            head->setDatum(other.getHead()->getDatum());
            previous = head;

            for(size_t i = 1; i < elements; ++i) {
                Node<Object>* iterate = other.getHead();
                for(size_t j = 1; j <= i; ++j) {
                    iterate = iterate->getNext();
                }
                cursor = new Node<Object>;
                cursor->setDatum(iterate->getDatum());
                cursor->setPrev(previous);
                previous->setNext(cursor);
                previous = cursor;
            }

            tail = cursor;
            cursor = nullptr;
            previous = nullptr;
        }
    }// - constructs a copy of the given list
    //COMPLETE
    ~DoublyLinkedList() {
        if(head == nullptr) {}
        else {
        cursor = head->getNext();
        previous = head;
        tail = nullptr;

        for(size_t i = 0; i < elements; ++i) { 
            delete previous;
            previous = cursor;
            if(cursor != nullptr) {
                cursor = cursor->getNext();
            }
            
        }
        
        

        previous = nullptr;
        cursor = nullptr;
        head = nullptr;
        }
    }// - destroys this list
    
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if(head == nullptr) {}
        else {
        cursor = head->getNext();
        previous = head;
        tail = nullptr;

        for(size_t i = 0; i < elements; ++i) { 
            delete previous;
            previous = cursor;
            if(cursor != nullptr) {
                cursor = cursor->getNext();
            }
            
        }
        
        

        previous = nullptr;
        cursor = nullptr;
        head = nullptr;
        }

        if(other.size() > 0) {
            elements = other.size();

            head = new Node<Object>;
            head->setDatum(other.getHead()->getDatum());
            previous = head;

            for(size_t i = 1; i < elements; ++i) {
                Node<Object>* iterate = other.getHead();
                for(size_t j = 1; j <= i; ++j) {
                    iterate = iterate->getNext();
                }
                cursor = new Node<Object>;
                cursor->setDatum(iterate->getDatum());
                cursor->setPrev(previous);
                previous->setNext(cursor);
                previous = cursor;
            }

            tail = cursor;
            cursor = nullptr;
            previous = nullptr;
        }
        return *this;
    }// - assigns a copy of the given list
    //COMPLETE
    size_t size() const { return elements; }// - returns the number of elements in the list
    Object& operator[](size_t index) {
        try{ if(index >= elements) {throw 1;} }
        catch(int n) {throw std::out_of_range("insert() index request out of bounds.");}
        Node<Object>* iterate = head;
        for(size_t i = 1; i <= index; ++i) {
            iterate = iterate->getNext();
        }

        return iterate->getDatum();        
    }// - returns a reference to the element at the specified index or throws std::out_of_range if the index is out of bounds.
   //COMPLETE
    void insert(size_t index, const Object& item) {
        try{ if(index > elements) {throw 1;} }
        catch(int n) {throw std::out_of_range("insert() index request out of bounds.");}


        if(elements == 0) {
            Node<Object>* newnode = new Node<Object>;
            head = newnode;
            tail = newnode;

            newnode->setDatum(item);
            ++elements;
        }
        else if (index == 0) {
            Node<Object>* newnode = new Node<Object>;
            newnode->setNext(head);
            head->setPrev(newnode);

            head = newnode;

            newnode->setDatum(item);
            ++elements;
        }
        else if (index == elements) { //appends to end of list
            Node<Object>* newnode = new Node<Object>;
            newnode->setPrev(tail);
            tail->setNext(newnode);
            
            tail = newnode;

            newnode->setDatum(item);
            ++elements;
        }
        else {
            cursor = head;
            for(size_t i = 0; i < index; ++i) {cursor = cursor->getNext();}

            Node<Object>* newnode = new Node<Object>;
            newnode->setDatum(item);
            newnode->setNext(cursor);
            newnode->setPrev(cursor->getPrev());
            cursor->getPrev()->setNext(newnode);
            cursor->setPrev(newnode);

            cursor = nullptr;
            ++elements;
        }
        
            
        
    }// - insert the given object at the specified index or throws std::out_of_range if the index is out of bounds
    //Complete
    void remove(size_t index) {
        try{ if(index >= elements || head == nullptr) {throw 1;}}
        catch(int n) {throw std::out_of_range("remove() index requested out of bounds.");}

        if (index == 0) {
            if(elements == 1) {
                delete head; 
                head = nullptr; 
                tail = nullptr; 
                --elements;
            }
            else {
            head = head->getNext();
            delete head->getPrev();
            head->setPrev(nullptr);
            --elements;
            }
        }
        else if (index == elements - 1) { //remove from end of list
            tail = tail->getPrev();
            delete tail->getNext();
            tail->setNext(nullptr);
            --elements;
        }
        else {
            cursor = head->getNext();
            previous = head;
            for(size_t i = 0; i < index; ++i) {cursor = cursor->getNext(); previous = previous->getNext();}

            cursor->setPrev(previous->getPrev());
            previous->getPrev()->setNext(cursor);
            delete previous;

            cursor = nullptr;
            previous = nullptr;
            --elements;
        }
    }// - remove the object at the specified index or throws std::out_of_range if the index is out of bounds

    void print() {
        if(elements == 0) {std::cout << "this list is empty..." << std::endl;}
        else{
        cursor = head;

        for(size_t i = 0; i < elements; ++i) {
            std::cout << "Element at " << i << " " << cursor << " : " << cursor->getDatum() << std::endl;
            cursor = cursor->getNext();
        }
        std::cout << std::endl;

        cursor = nullptr;
        }
    }

    Node<Object>* getHead() const { return head;}
};

#endif  // DOUBLY_LINKED_LIST_H
