#include "hashtable_separate_chaining.h"

using std::string;

int main() {
    // TODO(student): write at least 1000 lines of test
    size_t n = 0;

    /*
    Constructors
    HashTable() - COMPLETE
    explicit HashTable(size_t) COMEPLTE
    HashTable(const HashTable&) COMPLETE
    ~HashTable() - COMPLETE
    HashTable& operator=(const HashTable&) COMPLETE

    Iterators
    Optional

    Capacity
    bool is_empty() COMPLETE 
    size_t size() cOMPLETE

    Modifiers
    void make_empty() COMPLETE
    bool insert(const Key&) - insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    size_t remove(const Key&) - remove the specified value from the table, return number of elements removed (0 or 1).

    Lookup
    bool contains(const Key&) COMPLETE

    Bucket Interface
    size_t bucket_count() COMPLETE
    size_t bucket_size(size_t) COMPLETE
    size_t bucket(const key_type&) COMPLETE

    Hash Policy
    float load_factor() COMPLETE
    float max_load_factor() const COMPLETE
    void max_load_factor(float) COMPLETE
    void rehash(size_type) COMPLETE
    void print_table(std::ostream&=std::cout) COMPLETE
    
    Optional
    HashTable(HashTable&&) - move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) - move assigns a copy of the given (rvalue) table
    void insert(Key&&) - insert the given rvalue reference into the table using move semantics
    */
   
   {//basic functionality
        HashTable<std::string, std::hash<std::string>> e;
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table(cout);

        cout << "testing e.contains(0): " << e.contains("0") << endl; //true
        cout << "testing e.contains(90): " << e.contains("90") << endl; //true
        cout << "testing e.contains(42): " << e.contains("42") << endl; //true
        cout << "testing e.contains(30): " << e.contains("30") << endl; //true
        cout << "testing e.contains(4fff0): " << e.contains("4fff0") << endl; //false
        cout << "testing e.contains(9df0): " << e.contains("9df0") << endl; //false
        cout << "testing e.contains(42rtr): " << e.contains("42rtr") << endl; //false
        cout << "testing e.contains(30xcvdfg): " << e.contains("30xcvdfg") << endl; //false

        cout << "testing is_empty() [expect false]: " << e.is_empty() << endl; 
        cout << "testing size() [expect 10]: " << e.size() << endl; 
        cout << "emptying hash table..." << endl;
        cout << "testing bucket_count() [expect 11]: " << e.bucket_count() << endl;

        e.make_empty();
        e.print_table(cout);
        e.make_empty();
        e.print_table(cout);

        cout << "testing e.contains(42rtr): " << e.contains("42rtr") << endl;
        cout << "testing e.contains(30xcvdfg): " << e.contains("30xcvdfg") << endl;
        cout << "testing is_empty() [expect true]: " << e.is_empty() << endl;
        cout << "testing size() [expect 0]: " << e.size() << endl;
        cout << "testing bucket_count() [expect 11]: " << e.bucket_count() << endl;
        
        cout << endl << "reloading hash table..." << endl;
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i) + "kshdfjkhsd";
            e.insert(f);
        }
        e.print_table(cout);
        cout << "testing bucket_size() [expect 3]: " << e.bucket_size(3) << endl;
        cout << "testing bucket_size() [expect 0]: " << e.bucket_size(7) << endl;
        cout << "testing bucket_size() [expect 1]: " << e.bucket_size(1) << endl;
        try{cout << "testing bucket_size() [expect throw]: " << e.bucket_size(1000) << endl;}
        catch(std::out_of_range &e){cout << e.what() << endl;}

        cout << "testing bucket() [expect 1]: " << e.bucket("90kshdfjkhsd") << endl;
        cout << "testing bucket() [expect 3]: " << e.bucket("72kshdfjkhsd") << endl;
        cout << "testing bucket() [expect 8]: " << e.bucket("42kshdfjkhsd") << endl;
   }

    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

   {//copy construct, copy assign
   
        HashTable<std::string, std::hash<std::string>> e(17);
        e.print_table(cout);

        
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i/(i+1) + i);
            e.insert(f);
        }
        e.print_table(cout);

        HashTable<std::string, std::hash<std::string>> d(e);
        e.make_empty();
        e.print_table(cout);
        d.print_table(cout);

        for(size_t i = 0; i < 100; ++i){
            std::string f = std::to_string(i*i/(i+1) + i);
            e.insert(f);
        }
        
        e.print_table(cout);
        cout << e.size() << " : " << e.bucket_count() << endl;
        cout << e.max_load_factor() << " : " << std::to_string(e.load_factor()) << endl;
        e.max_load_factor(0.5);
        e.print_table(cout);
        cout << e.size() << " : " << e.bucket_count() << endl;
        cout << std::to_string(e.max_load_factor()) << " : " << std::to_string(e.load_factor()) << endl;

        try{e.max_load_factor(-100);}
        catch(std::invalid_argument &u){cout << u.what() << endl;}
        e.max_load_factor(1);
        //std::chrono::high_resolution_clock::time_point //start;
        //std::chrono::high_resolution_clock::time_point //stop;
        //std::chrono::duration<double> //delta;
        cout << "insertion time in small table" << endl;
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i) + "kshdfjkhsd";
            //start = //std::chrono::high_resolution_clock::now();
            e.insert(f);
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //cout << i << ": time " << //delta.count() << "seconds" << endl;
        }
        //std::chrono::duration<double> SL//delta = //delta;
        //start = //std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < 10000; ++i){
                std::string f = std::to_string(i*i + i) + "kshdfjkhsd";
                e.insert(f);
        }
        //stop = //std::chrono::high_resolution_clock::now();

        //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);

        //cout << "1M insertions took " << //delta.count() << "seconds" << endl;

        //start = //std::chrono::high_resolution_clock::now();
        d = e;
        //stop = //std::chrono::high_resolution_clock::now();
        //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);

        //cout << "1M entry copy assign took " << //delta.count() << "seconds" << endl;

        //start = //std::chrono::high_resolution_clock::now();
        e.make_empty();
        //stop = //std::chrono::high_resolution_clock::now();
        //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
        //cout << "1M empty() took " << //delta.count() << "seconds" << endl;

        //start = //std::chrono::high_resolution_clock::now();
        HashTable<std::string, std::hash<std::string>> r(d);
        //stop = //std::chrono::high_resolution_clock::now();
        //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
        //cout << "1M entry copy construct took " << //delta.count() << "seconds" << endl;

        HashTable<std::string, std::hash<std::string>> h(e);

        cout << e.size() << " : " << e.bucket_count() << endl;
        cout << std::to_string(e.max_load_factor()) << " : " << std::to_string(e.load_factor()) << endl;
        cout << d.size() << " : " << d.bucket_count() << endl;
        cout << std::to_string(d.max_load_factor()) << " : " << std::to_string(d.load_factor()) << endl;
        cout << h.size() << " : " << h.bucket_count() << endl;
        cout << std::to_string(h.max_load_factor()) << " : " << std::to_string(h.load_factor()) << endl;
        cout << r.size() << " : " << r.bucket_count() << endl;
        cout << std::to_string(r.max_load_factor()) << " : " << std::to_string(r.load_factor()) << endl;    

        h = r;
        for(size_t i = 0; i < 10000; ++i){
                std::string f = std::to_string(i*i + i) + "kshdfjkhsd";
                e.insert(f);
        }
        h = h;

        cout << h.size() << " : " << h.bucket_count() << endl;
        cout << std::to_string(h.max_load_factor()) << " : " << std::to_string(h.load_factor()) << endl;
        cout << r.size() << " : " << r.bucket_count() << endl;
        cout << std::to_string(r.max_load_factor()) << " : " << std::to_string(r.load_factor()) << endl;   
        cout << "insertion time in large table" << endl;
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i) + "kshdfjkhsd";
            //start = //std::chrono::high_resolution_clock::now();
            h.insert(f);
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //cout << i << ": time " << //delta.count() << "seconds" << endl;
        }
        //SL//delta -= //delta;
        //cout <<"Diffence between large and small data cases: " << SL//delta.count() << "seconds" << endl;
        
    }

    {//final test sequence: remove, memory integrity, code coverage

        //std::chrono::high_resolution_clock::time_point //start;
        //std::chrono::high_resolution_clock::time_point //stop;
        //std::chrono::duration<double> //delta;

        cout << "insertion time in small table" << endl;
        HashTable<std::string, std::hash<std::string>> h;
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i);
            //start = //std::chrono::high_resolution_clock::now();
            h.insert(f);
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //cout << i << ": time " << //delta.count() << "seconds" << endl;
        }
        //std::chrono::duration<double> SI//delta = //delta;

        h.print_table(cout);
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i);
            //start = //std::chrono::high_resolution_clock::now();
            h.insert(f);
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
        }
        //std::chrono::duration<double> SC//delta = //delta;

        h.print_table(cout);
        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i);
            //start = //std::chrono::high_resolution_clock::now();
            h.remove(f);
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //cout << i << ": time " << //delta.count() << "seconds" << endl;
        }
        //std::chrono::duration<double> SR//delta = //delta;

        for(size_t i = 0; i < 10; ++i){
            std::string f = std::to_string(i*i + i);
            cout << "inserting " << f << endl;
            h.insert(f);
        }
        h.print_table(cout);
        for(int i = 9; i >= 0; --i){
            std::string f = std::to_string(i*i + i);
            cout << "removing " << f << endl;
            h.remove(f);
            h.print_table(cout);
        }

        for(size_t i = 0; i < 20; ++i){
            std::string f = std::to_string(i*i + i);
            cout << "inserting " << f << endl;
            h.insert(f);
        }
        h.print_table(cout);

        h.remove("6");
        h.remove("42");
        h.remove("110");

        h.print_table(cout);

        for(size_t i = 0; i < 10000; ++i){
            std::string f = std::to_string(i*i + i);
            h.insert(f);
        }
        //start = //std::chrono::high_resolution_clock::now();
            h.insert("dfgdfg");
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
        //SI//delta -= //delta;
        //cout << "large and small case difference insert " << SI//delta.count() << endl;
        for(size_t i = 0; i < 10000; ++i){
            std::string f = std::to_string(i*i + i);
            h.remove(f);
        }
        for(size_t i = 0; i < 10000; ++i){
            std::string f = std::to_string(i*i + i);
            h.insert(f);
        }
        //start = //std::chrono::high_resolution_clock::now();
            h.contains("10100");
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //SC//delta -= //delta;
        //cout << "large and small case difference contains " << SC//delta.count() << endl;
        
        //start = //std::chrono::high_resolution_clock::now();
            h.remove("10100");
            //stop = //std::chrono::high_resolution_clock::now();
            //delta = //std::chrono::duration_cast<//std::chrono::duration<double>>(//stop - //start);
            //SR//delta -= //delta;
        //cout << "large and small case difference remove " << SI//delta.count() << endl;
        for(int i = 12000; i >= 0; --i){
            std::string f = std::to_string(i*i + i);
            h.remove(f);
        }
    }
    
   
    {
        HashTable<std::string, std::hash<std::string>> e(2);
        HashTable<std::string, std::hash<std::string>> h;
        std::string f;
        h = e;
        e = h;
        for(size_t i = 0; i < 20; ++i){
            f = std::to_string(i*i + i);
            cout << "inserting: " << f << endl;
            e.insert(f);
            e.print_table();
            cout << endl;
            e.table_info();
            cout << "~~~~~~~~~~~~~" << endl;
        }
        e.make_empty();
        e.insert(f);
        e.print_table();

        
    }
    

   //TODO:
   /*
   x bucket count
   x bucket size
   x copy asisgnment
   x copy constructor
   x mimir compile
   x insert
   x isempty
   x loadfactor
   x maxloadfactor
   x memory errors
   x rehash
   x remove
   x size
   */

    {//bucketcount 
     HashTable<std::string, std::hash<std::string>> e;
        
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.table_info();
        for(size_t i = 15; i < 25; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.table_info();

        HashTable<std::string, std::hash<std::string>> h(1);
        
        
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            h.table_info();
            h.insert(f);
        }
        
        for(size_t i = 15; i < 25; ++i){
            std::string f = std::to_string(i*i + i);
            h.table_info();
            h.insert(f);
        }
        e.table_info();
    }

    
    {//bucket size 
     HashTable<std::string, std::hash<std::string>> e;
        
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.table_info();
        for(size_t i = 15; i < 25; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.table_info();
        e.print_table();

        for(size_t i = 0; i < e.bucket_count(); ++i){
            cout << "bucketsize " << i << ": " << e.bucket_size(i) << endl;
        }
        try{cout << "bucketsize 400: " << e.bucket_size(400) << endl;}
        catch(std::out_of_range &l){cout << l.what() << endl;}
    }

 
    {//copy assign
        HashTable<std::string, std::hash<std::string>> e;
        th(n, "LOAD");
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();
        th(n, "COPY TO EMPTY");
        HashTable<std::string, std::hash<std::string>> h;
        h=e; // copy onto empty
        h.print_table();
        h.table_info();

        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            h.insert(f);
        }

        h.print_table();
        h.table_info();
        th(n, "SELF ASSIGN");
        h = h; //self assign

        e.make_empty();
        th(n, "EMPTY ONTO FILLED");
        h = e; 

        h.print_table();
        h.table_info();

        th(n, "RELOAD");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            h.insert(f);
        }
        h.print_table();
        h.table_info();
        e.print_table();
        e.table_info();

        th(n, "OVERWRITE");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i) + "ooooo";
            e.insert(f);
        }

        h = e;

        h.print_table();
        h.table_info();
        e.print_table();
        e.table_info();

    }
    
    
    {//copy constructor

        HashTable<std::string, std::hash<std::string>> e(1);
        th(n, "LOAD");
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        
        e.print_table();
        e.table_info();
        th(n, "COPY CONSTRUCT");
        HashTable<std::string, std::hash<std::string>> h(e);
        e.print_table();
        e.table_info();
        
        h.print_table();
        h.table_info();

        th(n, "ADJUSTING COPY");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i) + "p";
            h.insert(f);
        }
        e.print_table();
        e.table_info();
        
        h.print_table();
        h.table_info();

        th(n, "COPY CONSTRUCT SELF");
        HashTable<std::string, std::hash<std::string>> g(g);
        
        g.print_table();
        g.table_info();

        th(n, "ADJUSTING COPY");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            g.insert(f);
        }
        g.print_table();
        g.table_info();

        th(n, "COPY CONSTRUCT EMPTY");
        g.make_empty();
        HashTable<std::string, std::hash<std::string>> p(g);
        
        g.print_table();
        g.table_info();
        
        p.print_table();
        p.table_info();

        th(n, "ADJUSTING COPY");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i) + "k";
            p.insert(f);
        }
        g.print_table();
        g.table_info();
        p.print_table();
        p.table_info();

    }
    
    {//isnert, rehash
        HashTable<std::string, std::hash<std::string>> e;
        
        th(n, "LOAD");
        std::string f = "hello world";

        e.print_table();
        e.table_info();
        e.insert(f);
        e.print_table();
        e.table_info();
        e.insert(f);
        e.print_table();
        e.table_info();

        for(size_t i = 0; i < 4; ++i){
            std::string f = std::to_string(i*i + i);
            cout << "inserting " << f << "..." << endl;
            e.insert(f);
            e.print_table();
            e.table_info();
        }
        
        e.print_table();
        e.table_info();
        th(n, "COPY CONSTRUCT");
        
        HashTable<std::string, std::hash<std::string>> h(e);
        e.print_table();
        e.table_info();
        
        h.print_table();
        h.table_info();

        th(n, "ADJUSTING COPY");
        for(size_t i = 0; i < 10; ++i){
            
            f = std::to_string(i*i + i);
            cout << "inserting " << f << "..." << endl;
            h.insert(f);
            h.print_table();
            h.table_info();
        }

        for(size_t i = 0; i < 10; ++i){
            f = std::to_string(i*i + i);
            cout << "inserting " << f << "..." << endl;
            e.insert(f);
            e.print_table();
            e.table_info();
        }
        
        e.print_table();
        e.table_info();
        th(n, "COPY CONSTRUCT 2");
        HashTable<std::string, std::hash<std::string>> g(e);
        e.print_table();
        e.table_info();
        
        g.print_table();
        g.table_info();

        th(n, "ADJUSTING COPY 2");
        for(size_t i = 0; i < 20; ++i){
            f = std::to_string(i*i + i);
            cout << "inserting " << f << "..." << endl;
            g.insert(f);
            //g.print_table();
            //g.table_info();
        }
        for(size_t i = 0; i < 20; ++i){
            f = std::to_string(i*i + i);
            cout << "inserting " << f << "..." << endl;
            g.insert(f);
            //g.print_table();
            //g.table_info();
        }
        g.print_table();
        g.table_info();

        g.rehash(10);

        g.print_table();
        g.table_info();

         g.rehash(5);

        g.print_table();
        g.table_info();

        g.rehash(500);

        g.print_table();
        g.table_info();

        g.rehash(2);

        g.print_table();
        g.table_info();

        
        g.insert(std::string("fgkjdfglkhsdflg"));

        g.print_table();
        g.table_info();
    }
      
   
   {//remove
        HashTable<std::string, std::hash<std::string>> e;
        std::string f = "rats live on no evil star";
        th(n, "REMOVE FROM EMPTY");
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        th(n, "LOAD");
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.rehash(10);
        e.print_table();
        e.table_info();
        th(n, "REMOVE");
        f = "56";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "132";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "0";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "12";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "56fddsf";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "5rerwer3456";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        f = "5ryeryt45fhgb6";
        cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
        e.print_table();
        e.table_info();

        th(n, "REMOVE ALL");
        e.table_info();
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            cout << "removing " << f << ": " << std::boolalpha << e.remove(f) << endl;
            e.print_table();
            e.table_info();
        }

        th(n, "RELOAD");
        for(size_t i = 0; i < 15; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table(cout);
        e.table_info();
   }
   


  //TODO
  //bucket_size; covered by previous test
  //load factor; now includes load factor as maximum
  //insert; suspected problem lies within load factor and rehash
  //rehash(size_t); if value is too low, picks another value
  {// load factor
       HashTable<std::string, std::hash<std::string>> e;
        th(n, "LOAD");
        e.table_info();
        for(size_t i = 0; i < 11; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        for(size_t i = 0; i < 12; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();
  }

  {//rehash
        HashTable<std::string, std::hash<std::string>> e;
        th(n, "LOAD");
        e.table_info();
        for(size_t i = 0; i < 100; ++i){
            std::string f = std::to_string(i*i + i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        e.rehash(1);

        e.print_table();
        e.table_info();

        e.rehash(99);

        e.print_table();
        e.table_info();

        e.rehash(100);

        e.print_table();
        e.table_info();

        HashTable<std::string, std::hash<std::string>> k;
        k.rehash(50);
        k.print_table();
        k.table_info();

        for(size_t i = 0; i < 100; ++i){
            std::string f = std::to_string(i*i + i);
            k.insert(f);
        }
        k.print_table();
        k.table_info();
  }
    return 0;
    
}
