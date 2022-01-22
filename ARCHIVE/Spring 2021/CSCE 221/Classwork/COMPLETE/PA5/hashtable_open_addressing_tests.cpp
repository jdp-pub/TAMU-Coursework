#include "hashtable_open_addressing.h"

int main() {
    // TODO(student): write at least 1000 lines of test
    size_t n = 0;
    /*
    Constructors
    x HashTable() - makes an empty table with 11 cells
    x explicit HashTable(size_t) - makes an empty table with the specified number of cells
    x HashTable(const HashTable&) - constructs a copy of the given table
    x ~HashTable() - destructs this table
    x HashTable& operator=(const HashTable&) - assigns a copy of the given table

    Iterators
    Optional

    Capacity
    x bool is_empty() const - returns true if the table is empty
    x size_t size() const - returns the number of active values in the table
    x size_t table_size() const - return the number of cells in the table

    Modifiers
    x void make_empty() - remove all values from the table
    x bool insert(const Key&) - insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
    x size_t remove(const Key&) - remove the specified value from the table, return number of elements removed (0 or 1).

    Lookup
    x bool contains(const Key&) const - returns Boolean true if the specified value is in the table

    Position
    x size_t position(const Key&) const - return the index of the cell that would contain the specified value.  This method handles collision resolution.

    Visualization
    x void print_table(std::ostream&=std::cout) const - pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
    
    Optional
    HashTable(HashTable&&) - move constructs a copy of the given (rvalue) table
    HashTable& operator=(HashTable&&) - move assigns a copy of the given (rvalue) table
    void insert(Key&&) - insert the given rvalue reference into the table using move semantics
    */
   
    {
        HashTable<std::string, std::hash<std::string>> e;
        e.print_table();
        e.table_info();
        std::string f = "l";
        e.insert(f);
        e.print_table();
        e.table_info();

        HashTable<std::string, std::hash<std::string>> h(100);
        h.print_table();
        h.table_info();
        h.insert(f);
        h.print_table();
        h.table_info();


        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();
        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();

        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        e.remove("50");
        e.print_table();
        e.table_info();

        f = "50";
        e.insert(f);
        e.print_table();
        e.table_info();


        
        cout << "e.position(8): " << e.position("8") << endl;
        cout << "e.position(0): " << e.position("0") << endl;
        cout << "e.position(128): " << e.position("128") << endl;
        cout << "e.position(l): " << e.position("l") << endl;
        cout << "e.position(32): " << e.position("32") << endl;
        cout << "e.position(lddd): " << e.position("lddd") << endl;
        cout << "e.position(32ddd): " << e.position("32ddd") << endl;
        e.make_empty();

        e.print_table();
        e.table_info();

        e.make_empty();

        e.print_table();
        e.table_info();

        for(int i = 0; i < 100; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        for(int i = 0; i < 100; ++i){
            f = std::to_string(2*i * i);
            cout << "e.contains(" <<  f << ")" << ": " << e.contains(f) << endl ;
        }
        e.print_table();
        e.table_info();
        for(int i = 0; i < 100; ++i){
            f = std::to_string(2*i * i % 50);
            cout << "e.contains(" <<  f << ")" << ": " << e.contains(f) << endl ;
        }
        e.print_table();
        e.table_info();

        e.remove("8");
        e.print_table();
        e.table_info();

        e.remove("0");
        e.print_table();
        e.table_info();

        e.remove("2");
        e.print_table();
        e.table_info();

        e.remove("392");
        e.print_table();
        e.table_info();

        e.remove("882");
        e.print_table();
        e.table_info();

        e.remove("578");
        e.print_table();
        e.table_info();

        e.remove("2888");
        e.print_table();
        e.table_info();

        e.remove("72");
        e.print_table();
        e.table_info();

        e.remove("1152");
        e.print_table();
        e.table_info();

        e.insert("1152");
        e.print_table();
        e.table_info();
        
        for(int i = 0; i < 75; ++i){
            f = std::to_string(2*i * i);
            cout << "e.remove(" <<  f << ")" << ": " << e.remove(f) << endl ;
        }
        e.print_table();
        e.table_info();

        for(int i = 200; i < 250; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        for(int i = 250; i < 300; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table();
        e.table_info();

        for(int i = 0; i < 250; ++i){
            f = std::to_string(2*i * i);
            cout << "e.remove(" <<  f << ")" << ": " << e.remove(f) << endl ;
        }
        e.print_table();
        e.table_info();

        for(int i = 0; i < 400; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        for(int i = 0; i < 350; ++i){
            f = std::to_string(2*i * i);
            e.remove(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        for(int i = 0; i < 800; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        for(int i = 0; i < 350; ++i){
            f = std::to_string(2*i * i);
            e.remove(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        
        for(int i = 0; i < 10000; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        for(int i = 0; i < 10000; ++i){
            f = std::to_string(2*i * i);
            e.remove(f);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~" << endl;
        e.table_info();
        

    }
    
   
   {
       HashTable<std::string, std::hash<std::string>> e;
        std::string f;
       for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.remove(f);
        }
        e.print_table();
        e.table_info();

        HashTable<std::string, std::hash<std::string>> k(e);
        k.print_table();
        k.table_info();

        for(int i = 10; i < 20; ++i){
            f = std::to_string(2*i * i);
            k.insert(f);
        }
        k.print_table();
        k.table_info();
        e.print_table();
        e.table_info();

        k.make_empty();
        k.print_table();
        k.table_info();
        e.print_table();
        e.table_info();

        k = e;
        e.make_empty();
        k.print_table();
        k.table_info();
        e.print_table();
        e.table_info();
        
        k = k;
        k.print_table();
        k.table_info();

        k = e;
        k.print_table();
        k.table_info();
   }
   
 
  //TODO: 
  /*
  x contains
  x copy assignment
  x copy constructor
  x code coverage
  ~ mimir exaple complie
  x position
  x remove
  x size
  x table_size
  x insert
  x isempty
  */

    {//contains
        HashTable<std::string, std::hash<std::string>> e;
        e.print_table(cout);
        e.table_info();
        std::string f;

        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table(cout);
        e.table_info();

        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            cout << "Contains " << f << "?: " << std::boolalpha << e.contains(f) << endl;
        }

    }


    {//copy construct
        HashTable<std::string, std::hash<std::string>> e(1);
        e.print_table(cout);
        e.table_info();
        std::string f;
        th(n, "LOAD");
        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table(cout);
        e.table_info();

        th(n, "COPY CONSTRUCT");
        HashTable<std::string, std::hash<std::string>> h(e);
        e.print_table(cout);
        e.table_info();
        h.print_table(cout);
        h.table_info();

        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            h.insert(f);
        }

        e.print_table(cout);
        e.table_info();
        h.print_table(cout);
        h.table_info();

        e.make_empty();
        th(n, "COPY CONSTRUCT FROM EMPTY");
        HashTable<std::string, std::hash<std::string>> g(e);
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();
        
        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            g.insert(f);
        }
        g.print_table();
        g.table_info();

        th(n, "COPY CONSTRUCT FROM SELF");
        HashTable<std::string, std::hash<std::string>> q(q);
        q.print_table();
        q.table_info();

        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            q.insert(f);
        }
        q.print_table();
        q.table_info();
    }
    
   {//copy assign
        HashTable<std::string, std::hash<std::string>> e;
        e.print_table(cout);
        e.table_info();
        std::string f;
        th(n, "LOAD");
        for(int i = 0; i < 5; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table(cout);
        e.table_info();

        th(n, "COPY ASSIGN: INITIALIZE EMPTY");
        HashTable<std::string, std::hash<std::string>> g;
        g.print_table(cout);
        g.table_info();

        g = e;

        e.print_table(cout);
        e.table_info();
        g.print_table(cout);
        g.table_info();

        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            g.insert(f);
        }
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();

        th(n, "COPY ASSIGN: OVERWRITE");
        g = e;
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();

        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 10; ++i){
            f = std::to_string(2*i * i);
            g.insert(f);
        }
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();

        th(n, "COPY ASSIGN: SELF ASSIGN");
        g = g;
        g.print_table();
        g.table_info();

        th(n, "ADJUSTING COPY");
        for(int i = 0; i < 15; ++i){
            f = std::to_string(2*i * i);
            g.insert(f);
        }
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();

        th(n, "COPY ASSIGN: COPY FROM EMPTY");
        e.make_empty();
        g = e;
        e.print_table(cout);
        e.table_info();
        g.print_table();
        g.table_info();
   }
   
    
    {//position
        HashTable<std::string, std::hash<std::string>> e;
        e.print_table(cout);
        e.table_info();
        std::string f;
        
        th(n, "LOAD");

        for(int i = 0; i < 20; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
        }
        e.print_table(cout);
        e.table_info();

        th(n, "POSITION");
        for(int i = 0; i < 30; ++i){
            f = std::to_string(2*i * i);
            cout << e.position(f) << ": [" << f << "] ";
            if(i%4 == 0 && i != 0){cout <<  endl;}
        }
        cout << endl;
        
    }
    
   {//insert rehash
        HashTable<std::string, std::hash<std::string>> e(1);
        e.print_table(cout);
        e.table_info();
        std::string f;
        
        th(n, "LOAD");

        for(int i = 0; i < 20; ++i){
            f = std::to_string(2*i * i);
            cout << e.position(f) << ": [" << f << "] " << endl;
            e.insert(f);
            e.print_table(cout);
            e.table_info();
        } 
   }
   {//remove
       HashTable<std::string, std::hash<std::string>> e(1);
        e.print_table(cout);
        e.table_info();
        std::string f;
        
        th(n, "LOAD");

        for(int i = 0; i < 20; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
            
        } 
        e.print_table(cout);
        e.table_info();
        for(int i = 0; i < 30; ++i){
            f = std::to_string(2*i * i);
            if(i%2 == 0){cout << "removing "<< f << ": " << e.remove(f) << endl;}
        } 
        e.print_table(cout);
        e.table_info();  
        for(int i = 0; i < 20; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
            
        } 
        e.print_table(cout);
        e.table_info();  
        for(int i = 20; i < 25; ++i){
            f = std::to_string(2*i * i);
            e.insert(f);
            
        } 
        e.print_table(cout);
        e.table_info();
   }
   
    return 0;
}