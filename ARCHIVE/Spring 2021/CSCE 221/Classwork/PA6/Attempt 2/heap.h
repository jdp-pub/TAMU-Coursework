#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <iostream>
#include <vector>

using std::cout, std::endl, std::vector;

// TODO(student): implement heap functions
    /*
    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heapify(Container*, Compare <var name> =std::less<typename Container::value_type>{}) - build a heap with the data in the given container (passed by pointer value to indicate that this function modifies the container) using the specified comparator (comparison functor, default is std::less to make a min heap), the first element of the heap should be in index 1.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_insert(Container*, const typename Container::value_type&, Compare=std::less<typename Container::value_type>{}) - insert the specified value into the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap). If the container is empty, do the user a solid and make it a heap before inserting.

    template <class Container>
    const typename Container::value_type& heap_get_min(const Container&) - return the “minimum” value (whichever value is at the root of the heap) in the specified heap (which is passed by constant reference to indicate that this function does not modify the container).  Throw std::invalid_argument if heap is empty.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_delete_min(Container*, Compare=std::less<typename Container::value_type>{}) - remove the “minimum” value (whichever value is at the root of the heap) in the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap).   Throw std::invalid_argument if heap is empty.

    Optional
    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heapify(Container& container, Compare less=std::less<typename Container::value_type>{}) - wrapper function for heapify if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_insert(Container& container, const typename Container::value_type& value, Compare less=std::less<typename Container::value_type>{}) - wrapper function for insert if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_delete_min(Container& container, Compare less=std::less<typename Container::value_type>{}) - wrapper function for delete_min if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.    Throw std::invalid_argument if heap is empty.
    */

   template<class Comparable>
   void test( std::string fctn, Comparable Expected, Comparable Actual, size_t line){
       std::string result = "FAIL";
       if(Expected == Actual){ result = "PASS"; }

       cout << "Line:" << line << ": Function[" << fctn << "] || Expected[" << Expected << "] || Actual[" << Actual << "] || [" << result << "]" << endl;
   }
   void nl(){ cout << endl; }

  
    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_insert(Container* c, const typename Container::value_type& val, Compare comp=std::less<typename Container::value_type>{}){
        typename Container::value_type pl = {};
        if(c->size() == 0){c->push_back(pl); c->push_back(val); return;}
        
        size_t n = 0;
        c->push_back(val);
        n = c->size() - 1;
        
        typename Container::value_type temp;
        
        //node i
        //l child = 2i
        //r child = 2i + 1
        //parent = i/2
        while(n > 1){
            if(comp(c->at(n), c->at(n/2))){
                temp = c->at(n/2);
                c->at(n/2) = c->at(n);
                c->at(n) = temp;
                n = n/2;
            }
            else{ break; }
        }
        
        
        
       
    }// - insert the specified value into the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap). If the container is empty, do the user a solid and make it a heap before inserting.

     template <class Container, class Compare=std::less<typename Container::value_type>>
    void heapify(Container* c, Compare comp =std::less<typename Container::value_type>{} ) {
        typename Container::value_type pl = {};
        
        c->insert(c->begin(), pl);

        typename Container::value_type temp;

        for(size_t i = c->size() / 2; i > 0; --i){

            size_t j = i;
            while (j <= (c->size() / 2)){
                bool lc = false;
                bool rc = false;
                if(j *2+1 < c->size()){
                    //cout << "two subchildren" << endl;
                    if(comp(c->at(2*j), c->at(j*2+1)) && (comp(c->at(2*j), c->at(j)))){
                        lc = true;
                    }
                    else if((comp(c->at(2*j+1), c->at(j*2))) && (comp(c->at(2*j+1), c->at(j)))){
                        rc = true;
                    }
                }
                if((((j *2 + 1 < c->size()) && comp(c->at(2*j+1), c->at(j)))&&(!lc)) || rc){
                    //cout << "swapping right, rc " << std::boolalpha << rc << " : "  << c->at(2*j+1) << "|||" <<  c->at(j) << endl;
                    temp = c->at(2*j+1);
                    c->at(j*2+1) = c->at(j);
                    c->at(j) = temp;
                    j = j*2 + 1;
                }
                else if((((j *2 < c->size()) && comp(c->at(2*j), c->at(j))) && (!rc)) || lc){
                    //cout << "swapping left, lc " << std::boolalpha << lc << " : "  << c->at(2*j) << "|||" <<  c->at(j) << endl;
                    temp = c->at(2*j);
                    c->at(j*2) = c->at(j);
                    c->at(j) = temp;
                    j = j*2;
                }
                else{break;}
            }
        }
    }//- build a heap with the data in the given container (passed by pointer value to indicate that this function modifies the container) using the specified comparator (comparison functor, default is std::less to make a min heap), the first element of the heap should be in index 1.


    template <class Container>
    const typename Container::value_type& heap_get_min(const Container& c) {
        try{if(c.begin() == c.end() || (c.size() < 2)){throw 1;}}
        catch(int n){throw std::invalid_argument("Find min of empty heap.");}
        return c.at(1);
    }//- return the “minimum” value (whichever value is at the root of the heap) in the specified heap (which is passed by constant reference to indicate that this function does not modify the container).  Throw std::invalid_argument if heap is empty.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_delete_min(Container* c, Compare comp=std::less<typename Container::value_type>{}) {
        try{if((c->size() < 2) || (c->begin() == c->end())){throw 1;}}
        catch(int n){throw std::invalid_argument("Delete min of empty heap.");}
        c->at(1) = *c->rbegin();
        c->pop_back();
        
        size_t n = 1;
        
        typename Container::value_type temp;
        
        //node i
        //l child = 2i
        //r child = 2i + 1
        //parent = i/2
        while(n <= (c->size()-1) / 2 ){
            if((n == (c->size()-1) / 2) && !comp(c->at(n*2), c->at(n))){ break; }
            else if((n == (c->size()-1) / 2) && comp(c->at(n*2), c->at(n))){
                temp = c->at(2*n);
                c->at(n*2) = c->at(n);
                c->at(n) = temp;
                n = n*2;
            }
            else if (comp(c->at(n*2), c->at(n)) && (comp(c->at(n*2), c->at(2*n + 1)) || (c->at(n*2) == c->at(2*n + 1)))) {
                //cout << "||| swapping left: " << c->at(n) << " | " << c->at(2*n) <<  " |||" << endl;
                temp = c->at(2*n);
                c->at(n*2) = c->at(n);
                c->at(n) = temp;
                n = n*2;
            }
            else if (comp(c->at(n*2+1), c->at(n)) && comp(c->at(n*2+1), c->at(2*n))) {
               // cout << "||| swapping right: " << c->at(n) << " | " << c->at(2*n+1) <<  " |||" << endl;
                temp = c->at(2*n+1);
                c->at(n*2+1) = c->at(n);
                c->at(n) = temp;
                n = n*2+1;
            }
            else{ break; }
        }

    }//- remove the “minimum” value (whichever value is at the root of the heap) in the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap).   Throw std::invalid_argument if heap is empty.

    //Optional
    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heapify(Container& container, Compare comp=std::less<typename Container::value_type>{}) {heapify(&container, comp);}//- wrapper function for heapify if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_insert(Container& c, const typename Container::value_type& value, Compare comp=std::less<typename Container::value_type>{}) {heap_insert(&c, value, comp);}//- wrapper function for insert if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.

    template <class Container, class Compare=std::less<typename Container::value_type>>
    void heap_delete_min(Container& container, Compare comp=std::less<typename Container::value_type>{}) {heap_delete_min(&container, comp);}//- wrapper function for delete_min if you have difficulty remembering to pass by pointer value, sends the address of the container on to the actual function.    Throw std::invalid_argument if heap is empty.

     template <class Comparable>
    void print_queue(vector<Comparable> container){
        if(container.size() < 2){cout << "<empty>\n"; return;}
        for(size_t i = 1; i < container.size(); ++i){
            cout << container.at(i);
            if(i != container.size() - 1){cout << ", ";}
        }
        cout << endl;
    }
#endif  // HEAP_H