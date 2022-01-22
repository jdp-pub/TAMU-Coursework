#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <functional> 
#include <iostream> 
#include <list> 
#include <sstream> 
#include <stdexcept> 
#include <vector> 

using std::cout, std::endl;

void th(size_t& num, std::string test){
    cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "SEQUENCE " << num << " | " << test << endl << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    ++num;
}

template <class Key, class Hash=std::hash<Key>>
class HashTable {
    // TODO(student): implement an open addressing hash table

    /*
    Constructors
    HashTable() - makes an empty table with 11 cells
    explicit HashTable(size_t) - makes an empty table with the specified number of cells
    HashTable(const HashTable&) - constructs a copy of the given table
    ~HashTable() - destructs this table
    HashTable& operator=(const HashTable&) - assigns a copy of the given table

    Iterators
    Optional

    Capacity
    bool is_empty() const - returns true if the table is empty
    size_t size() const - returns the number of active values in the table
    size_t table_size() const - return the number of cells in the table

    Modifiers
    void make_empty() - remove all values from the table
    bool insert(const Key&) - insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    size_t remove(const Key&) - remove the specified value from the table, return number of elements removed (0 or 1).

    Lookup
    bool contains(const Key&) const - returns Boolean true if the specified value is in the table

    Position
    size_t position(const Key&) const - return the index of the cell that would contain the specified value.  This method handles collision resolution.

    Visualization
    void print_table(std::ostream&=std::cout) const - pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
    
    Optional
    HashTable(HashTable&&) - move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) - move assigns a copy of the given (rvalue) table
    void insert(Key&&) - insert the given rvalue reference into the table using move semantics

    */
    struct Node {// a little exra overhead than just a list of keys but allows for keyed objects with multiple data members
       Key Keyval = {};
       bool filled = false;
       bool del = false;

       Node(){}
       Node(const Key& other) {
           Keyval = other;
           filled = other;
       }
       Node& operator=(const Node& other){
         filled = other.hasKey();
         Keyval = other.getKey();
         del = other.isRemoved();
         return *this;
       }
       Key getKey() const { return Keyval; }
       void setKey(Key& key) { 
         Keyval = key;
          filled = true; 
          }
        void setRemove() {del = true;}
       bool hasKey() const{return filled;}
       bool isRemoved() const {return del;}
       void unDelete() {del = false;}
   };
   Node* buckets = {};
   size_t bucketCap = 11;
   size_t elements = 0;
   size_t elementLoad = 0;
   float lambda = 0.5f;

  public:
      // Constructors
    HashTable(){buckets = new Node[bucketCap];}// - makes an empty table with 11 cells
    explicit HashTable(size_t ns){ bucketCap = ns; buckets = new Node[bucketCap];}// - makes an empty table with the specified number of cells
    HashTable(const HashTable& other){
      bucketCap = other.table_size();
      buckets = new Node[bucketCap];
      for(size_t i = 0; i < other.table_size(); ++i){
        buckets[i] = other.getNode(i);
      }
      bucketCap = other.table_size();
      elements = other.size();
      elementLoad = other.totalElements();
    }// - constructs a copy of the given table
    ~HashTable(){delete[] buckets; }// - destructs this table
    HashTable& operator=(const HashTable& other){
      if(buckets == other.getRoot()){ return *this;}

      bucketCap = other.table_size();
      delete[] buckets;
      buckets = new Node[bucketCap];
      for(size_t i = 0; i < other.table_size(); ++i){
        buckets[i] = other.getNode(i);
      }
      bucketCap = other.table_size();
      elements = other.size();
      elementLoad = other.totalElements();
      return *this;
    }// - assigns a copy of the given table

    //Iterators
    //Optional

    //Capacity
    bool is_empty() const{return !(elements);}// - returns true if the table is empty
    size_t size() const{return elements;}// - returns the number of active values in the table
    size_t table_size() const{return bucketCap;}// - return the number of cells in the table

    //Modifiers
    void make_empty(){
      if(is_empty()){return;} 
      
      for(size_t i =0; i < bucketCap; ++i){
        if(buckets[i].hasKey()){buckets[i].setRemove();}
      }
      elements = 0;
    }// - remove all values from the table
    bool insert(const Key& query) {
      size_t index = Hash{}(query);
      index = index % bucketCap;
      size_t fb = 10;//decrement in loop for force break
      while(fb){
        if((!buckets[index].hasKey()) || ((buckets[index].getKey() == query) && buckets[index].isRemoved())){break;}
        else if((buckets[index].getKey() == query) && !buckets[index].isRemoved()){return false;}
        else{index = (index + 1) % bucketCap;}
        //--fb;
      }
      if((buckets[index].getKey() == query) && buckets[index].isRemoved()){++elements; buckets[index].unDelete(); return true;}
      Key temp = query;
      buckets[index].setKey(temp);

      ++elements;
      ++elementLoad;
      while(((float)(elementLoad) / (float)(bucketCap)) >= lambda){
        size_t tempS = bucketCap;
        bucketCap *= 2;
        while(!is_prime(bucketCap)){++bucketCap;} //finds next prime number after doubling
        Node* newBuckets = new Node[bucketCap];
        
        for(size_t i = 0; i < tempS; ++i) {
          if(buckets[i].hasKey() && !buckets[i].isRemoved()){
            index = Hash{}(buckets[i].getKey());
            index = index % bucketCap;
            while(1){
              if(!newBuckets[index].hasKey()){break;}
              else{index = (index + 1) % bucketCap;}
            }
            Key temp = buckets[i].getKey();
            newBuckets[index].setKey(temp);
          }
        }
        delete[] buckets;
        buckets = newBuckets;
        elementLoad = elements;
      }
      return true;
    }//- insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    size_t remove(const Key& query) {
      size_t index = Hash{}(query);
        index = index % bucketCap;
        while(1){
          if(!buckets[index].hasKey() || (buckets[index].getKey() == query && !buckets[index].isRemoved())){break;}
          else{index = (index + 1) % bucketCap;}
        }
        if(query == buckets[index].getKey()){--elements; buckets[index].setRemove(); return 1;}
        else{return 0;}
    }//- remove the specified value from the table, return number of elements removed (0 or 1).

    //Lookup
    bool contains(const Key& query) const{
      size_t index = Hash{}(query);
      index = index % bucketCap;
      while(1){
        if(!buckets[index].hasKey()){return false;}
        if((buckets[index].getKey() == query) && !buckets[index].isRemoved()){break;}
        else{index = (index + 1) % bucketCap;}
      }
      return true;
    }// - returns Boolean true if the specified value is in the table

    //Position
    size_t position(const Key& query) const{
        size_t index = Hash{}(query);
        index = index % bucketCap;
        
        while(1){
          if((!buckets[index].hasKey()) || ((buckets[index].getKey() == query) && buckets[index].isRemoved())){break;}
        else if((buckets[index].getKey() == query) && !buckets[index].isRemoved()){break;}
        else{index = (index + 1) % bucketCap;}
        }
        return index;
    }// - return the index of the cell that would contain the specified value.  This method handles collision resolution.
    Node& getNode(size_t i) const {return buckets[i];}
    size_t totalElements() const {return elementLoad;}
    Node* getRoot() const {return buckets;} 
    //Visualization
    void print_table(std::ostream& os) const{
      if(is_empty()){os << "<empty>\n"; return;}
      size_t  out = 0;
      for(size_t i = 0; i < bucketCap; ++i) {
        if(buckets[i].hasKey() && !buckets[i].isRemoved()){
            if((out%4 == 0) && (out != 0)){os << endl;}
            ++out; os << i << ": [" << buckets[i].getKey() << "] ";
          }
      }
      os << endl;
    }// - pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
    void print_table() const{
      if(is_empty()){cout << "<empty>\n"; return;}
      size_t  out = 0;
      for(size_t i = 0; i < bucketCap; ++i) {
        
        if(buckets[i].hasKey() && !buckets[i].isRemoved()){
          if((out%4 == 0) && (out != 0)){cout << endl;}
          ++out; cout << i << ": [" << buckets[i].getKey() << "] ";
          }
      }
      cout << endl;
    }

    bool is_prime(size_t i){
      size_t count = 2;
      while(count != i){
        if(i % count == 0){ return false;}
        if(count == i / 2){break;}
        count++;
      }
      return true;
    }
    void table_info(){
      cout << "Elements: " << size() << endl
           << "Occupied Buckets: " << elementLoad << endl
           << "Buckets: " << table_size() << endl
           << "Empty?: " << std::boolalpha << is_empty() << endl
           << "Max Load: " << std::to_string(lambda) << endl
           << "Load: " << std::to_string((float)(elementLoad) / (float)(bucketCap)) << endl
           << "~~~~~~~~~~~~~~~~~~~~~" << endl; 
    }
    //Optional
    HashTable(HashTable&&) {}//- move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) {}//- move assigns a copy of the given (rvalue) table
    void insert(Key&& other) {Key temp = other; insert(temp);}//- insert the given rvalue reference into the table using move semantics

};

#endif  // HASHTABLE_OPEN_ADDRESSING_H