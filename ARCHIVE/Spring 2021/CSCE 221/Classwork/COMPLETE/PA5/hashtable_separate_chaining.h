#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <functional> 
#include <iostream> 
#include <list> 
#include <sstream> 
#include <stdexcept> 
#include <vector> 

using std::vector, std::list, std::cout, std::endl;

void th(size_t& num, std::string test){
    cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "SEQUENCE " << num << " | " << test << endl << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    ++num;
}

template <class Key, class Hash=std::hash<Key>>
class HashTable {
    // TODO(student): implement a separate chaining hash table
    /*
    Constructors
    HashTable() - makes an empty table with 11 buckets
    explicit HashTable(size_t) - makes an empty table with the specified number of buckets
    HashTable(const HashTable&) - constructs a copy of the given table
    ~HashTable() - destructs this table
    HashTable& operator=(const HashTable&) - assigns a copy of the given table

    Iterators
    Optional

    Capacity
    bool is_empty() const - returns true if the table is empty
    size_t size() const - returns the number of values in the table

    Modifiers
    void make_empty() - remove all values from the table
    bool insert(const Key&) - insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    size_t remove(const Key&) - remove the specified value from the table, return number of elements removed (0 or 1).

    Lookup
    bool contains(const Key&) const - returns Boolean true if the specified value is in the table

    Bucket Interface
    size_t bucket_count() const - return the number of buckets in the table
    size_t bucket_size(size_t) const - return the number of values in the specified bucket; throw std::out_of_range if the bucket index is out of bounds of the table.
    size_t bucket(const key_type&) const - return the index of the bucket that contains the specified value

    Hash Policy
    float load_factor() const - return the current load factor of the table
    float max_load_factor() const - return the current maximum load factor of the table 
    void max_load_factor(float) - set the maximum load factor of the table, forces a rehash if the new maximum is less than the current load factor, throws std::invalid_argument if the input is invalid
    void rehash(size_t) - set the number of buckets to the specified value and rehash the table if the total number of buckets has changed. If the new number of buckets would cause the load factor to exceed the maximum load factor, then the new number of buckets is at least size() / max_load_factor(). 
    Visualization
    void print_table(std::ostream&=std::cout) const - pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
    
    Optional
    HashTable(HashTable&&) - move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) - move assigns a copy of the given (rvalue) table
    void insert(Key&&) - insert the given rvalue reference into the table using move semantics
    */
   struct Node {// a little exra overhead than just a list of keys but allows for keyed objects with multiple data members
       Key Keyval = {};
       bool keyed = false;

       Node(){}
       Node(const Key& other) {
           Keyval = other;
           keyed = true;
       }
       Key getKey() const { return Keyval; }
       bool hasKey() const {return keyed;}
   };

   list<Node>* bucketList = nullptr;
   size_t bucketCap = 11;
   size_t elements = 0;
   float lambda = 1.0f;

   public:
    //Constructors
    HashTable(){
        bucketList = new list<Node>[bucketCap];
    } //- makes an empty table with 11 buckets
    explicit HashTable(size_t size) {
        bucketCap = size;
        bucketList = new list<Node>[bucketCap];
    }//- makes an empty table with the specified number of buckets
    HashTable(const HashTable& other) {
        if(other.root() != root()){
            bucketCap = other.bucket_count();
            elements = other.size();
            lambda = other.max_load_factor();
            
            bucketList = new list<Node>[bucketCap];
            typename list<Node>::iterator it;
            
            for(size_t i = 0; i < bucketCap; ++i){
                

                for(size_t j = 0; j < other.bucket_size(i); ++j){  
                    it = other.iterateFrom(i);
                    std::advance(it, j);
                    Node temp(it->getKey());
                    bucketList[i].push_back(temp); 
                }
            }
        }
        else{ bucketList = new list<Node>[bucketCap]; }
    }//- constructs a copy of the given table
    ~HashTable(){delete[] bucketList;}// - destructs this table
    HashTable& operator=(const HashTable& other) {
        
        if(other.root() != root()){
            if(other.size() == 0){ 
                delete[] bucketList;
                bucketCap = other.bucket_count();
                elements = other.size();
                lambda = other.max_load_factor();
                bucketList = new list<Node>[bucketCap];
                return *this;
            }
            bucketCap = other.bucket_count();
            elements = other.size();
            lambda = other.max_load_factor();
            
            

            delete[] bucketList;
            
            bucketList = new list<Node>[bucketCap];
            typename list<Node>::iterator it;
            
            for(size_t i = 0; i < bucketCap; ++i){
                it = other.iterateFrom(i);
                
                for(size_t j = 0; j < other.bucket_size(i); ++j){
                    Node temp(it->getKey());
                    bucketList[i].push_back(temp); 
                    std::advance(it, 1);
                }
            }
        }
        return *this;
    }//- assigns a copy of the given table

    //Iterators
    //Optional

    //Capacity
    bool is_empty() const{ return !(elements); }// - returns true if the table is empty
    size_t size() const { return elements; }//- returns the number of values in the table
    typename list<Node>::iterator iterateFrom (size_t i) const {
        typename list<Node>::iterator it = bucketList[i].begin();
        return it;
        }
    //Modifiers
    void make_empty() { 
        if(elements != 0){
            elements = 0; 
            delete[] bucketList; 
            bucketList = new list<Node>[bucketCap];
        }
    }//- remove all values from the table
    bool insert(const Key& query) {
        size_t index = bucket(query);
        
        typename list<Node>::iterator it;
        it = bucketList[index].begin();

        for(size_t i = 0; i < bucketList[index].size(); ++i) {
            if(query == it->getKey()) {return false;}
            std::advance(it, 1);
        }
        
        Node temp(query);
        bucketList[index].push_back(temp);

        ++elements;

        while(load_factor() > max_load_factor()){rehash();}

        return true;
    }//- insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    size_t remove(const Key& query){
        size_t index = bucket(query);
        
        typename list<Node>::iterator it;
        it = bucketList[index].begin();

        for(size_t i = 0; i < bucketList[index].size(); ++i) {
            if(query == it->getKey()) {
                bucketList[index].erase(it);
                --elements;
                return 1;
            }
            std::advance(it, 1);
        }

        return 0;
    } //- remove the specified value from the table, return number of elements removed (0 or 1).

    //Lookup
    bool contains(const Key& query) const {
        size_t index = bucket(query);
        
        typename list<Node>::iterator it;
        it = bucketList[index].begin();

        for(size_t i = 0; i < bucketList[index].size(); ++i) {
            if(query == it->getKey()) {return true;}
            std::advance(it, 1);
        }
        return false;
    }//- returns Boolean true if the specified value is in the table

    //Bucket Interface
    size_t bucket_count() const {return bucketCap; }//- return the number of buckets in the table
    size_t bucket_size(size_t query) const {
        try{ if(query >= bucket_count()){throw 1;} }
        catch(int n){throw std::out_of_range("Bucket query not in range.");}
        return bucketList[query].size();
    }//- return the number of values in the specified bucket; throw std::out_of_range if the bucket index is out of bounds of the table.
    size_t bucket(const Key query) const {
        size_t index = Hash{}(query);
        index = index % bucketCap;
        return index;
    }//- return the index of the bucket that contains the specified value

    //Hash Policy
    float load_factor() const { float load = (float)(elements) / (float)(bucketCap); return load;}//- return the current load factor of the table
    float max_load_factor() const { return lambda; }//- return the current maximum load factor of the table 
    void max_load_factor(float newLambda) {
        try{if(newLambda <= 0){throw 1;}}
        catch(int n){throw std::invalid_argument("New max load factor outside of possible values.");}
        if(lambda == newLambda){return;}
        lambda = newLambda;
        
        if(load_factor() > max_load_factor()) {rehash();}
    }//- set the maximum load factor of the table, forces a rehash if the new maximum is less than the current load factor, throws std::invalid_argument if the input is invalid
    void rehash() {
        size_t tempCap = bucketCap * 2;
        while(!is_prime(tempCap)){++tempCap;}

        while(((float)(elements) / (float)(tempCap)) > lambda) {
            tempCap = tempCap * 2;
            while(!is_prime(tempCap)){++tempCap;}
        }
        list<Node>* temp;
        temp = new list<Node>[tempCap];

        typename list<Node>::iterator it;

        for(size_t i = 0; i < bucketCap; ++i){
            for(size_t j = 0; j < bucket_size(i); ++j){

                it = iterateFrom(i);
                std::advance(it, j);

                size_t index = Hash{}(it->getKey());
                index = index % tempCap;

                Node temp2(it->getKey());
                temp[index].push_back(temp2);
                
            }
        }

        delete[] bucketList;
        bucketCap = tempCap;
        bucketList = temp;
    }//- set the number of buckets to the specified value and rehash the table if the total number of buckets has changed. If the new number of buckets would cause the load factor to exceed the maximum load factor, then the new number of buckets is at least size() / max_load_factor(). 
    void rehash(size_t newSize) {
        while(((float)(elements) / (float)(newSize)) > lambda) {
            newSize = newSize * 2;
            while(!is_prime(newSize)){++newSize;}
        }
        list<Node>* temp;
        temp = new list<Node>[newSize];

        typename list<Node>::iterator it;

        for(size_t i = 0; i < bucketCap; ++i){
            for(size_t j = 0; j < bucket_size(i); ++j){

                it = iterateFrom(i);
                std::advance(it, j);

                size_t index = Hash{}(it->getKey());
                index = index % newSize;
                Node temp2(it->getKey());
                temp[index].push_back(temp2);
                
            }
        }

        delete[] bucketList;
        bucketCap = newSize;
        bucketList = temp;
    }
    bool is_prime(size_t i){
        //if(i = 1){ return true; }
      size_t count = 2;
      while(count != i){
        if(i % count == 0){ return false;}
        if(count == i / 2){break;}
        count++;
      }
      return true;
    }
    //Visualization
    void print_table(std::ostream& os) const {
        typename list<Node>::iterator it;
        if(is_empty()){os << "<empty>\n"; return;}
        for(size_t i = 0; i < bucketCap; ++i){
            if(bucketList[i].size() > 0){os << i << ": ";}
            for(size_t j = 0; j < bucketList[i].size(); ++j){
                it = bucketList[i].begin();
                std::advance(it, j);

                os << "[";
                os << it->getKey() << "]";
                if(j < bucketList[i].size() - 1){os << "->"; }
            }
            if(bucketList[i].size() > 0){os << endl;}
        }
    }//- pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
    void print_table() const {
        typename list<Node>::iterator it;
        if(is_empty()){cout << "<empty>\n"; return;}
        for(size_t i = 0; i < bucketCap; ++i){
            if(bucketList[i].size() > 0){cout << i << ": ";}
            for(size_t j = 0; j < bucketList[i].size(); ++j){
                it = bucketList[i].begin();
                std::advance(it, j);

                cout << "[";
                cout << it->getKey() << "]";
                if(j < bucketList[i].size() - 1){cout << "->"; }
            }
            if(bucketList[i].size() > 0){cout << endl;}
        }
    }
    void table_info() {
        cout << "Elements: " << size() << endl
             << "Load Factor: " << std::to_string(load_factor()) << endl
             << "Max Load: " << std::to_string(max_load_factor()) << endl
             << "Buckets: " << bucket_count() << endl
             << "Empty? " << std::boolalpha << is_empty() << endl
             << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    //Optional
    HashTable(HashTable&&) {}//- move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) {}//- move assigns a copy of the given (rvalue) table
    void insert(Key&& other) {Key temp = other; insert(temp);}//- insert the given rvalue reference into the table using move semantics
    list<Node>* root() const {return bucketList;}
    //vector<vector<Node>> getBucketList() const {return bucketList;}
};

#endif  // HASHTABLE_SEPARATE_CHAINING_H