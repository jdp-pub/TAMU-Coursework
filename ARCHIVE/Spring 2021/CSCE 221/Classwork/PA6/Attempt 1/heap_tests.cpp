#include "heap.h"

void print_vector(vector<int> r){
    for(size_t i = 0; i < r.size(); ++i){
            cout << i << ": " <<  r.at(i) << endl;
        }
        cout << "~~~~~~~~~~" << endl;
}

template <class Comparable>
struct GreaterThan {
    constexpr bool operator()(const Comparable& lhs, const Comparable& rhs) const {
        return rhs < lhs;
    }
};

int main() {
    // TODO(student): write at least 1000 lines of test
    /*
void heapify
void heap_insert
x heap_get_min
void heap_delete_min

Optional
void heapify
void heap_insert
void heap_delete_min
*/
/*
    //int n = 0;
    {//get something to compile, heapify
        vector<int> r = {22, 1, 5, 33, 4, 11, 2};
        heapify(r);
        for(size_t i = 0; i < r.size(); ++i){
            cout << r.at(i) << endl;
        }
        cout << heap_get_min(r) << endl;

        vector<int> h;
        try{cout << heap_get_min(h) << endl;}
        catch(std::invalid_argument &e){cout << e.what() << endl;}
    }

    {
        int n = 0, i = 0, j = 0;
        vector<int> r = {0, 59,100,100,174,176,185,199,205,217,242,250,431,605,705};

        print_queue(r);
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        j = heap_get_min(r);
        heap_delete_min(r);
        i = heap_get_min(r);
        heap_delete_min(r);
        ++n;
        cout << "Node " << n << ": " << i + j << endl;
        
    }
   */
  {
        vector<int> r;
        for(size_t j = 0; j < 10; ++j){
            cout << "inserting " << (j * 11 + 7) % 20 << endl;
            r.push_back((j * 11 + 7) % 20 );
            print_queue(r);
            cout << "heapifying... " << endl;
            heapify(r);
            print_queue(r);
            cout << endl;
        }

        r.clear();

        for(size_t j = 0; j < 10; ++j){
            cout << "inserting " << (j * 11 + 7) % 20 << endl;
            r.push_back((j * 11 + 7) % 20 );
            
        }

        cout << "heapifying... " << endl;
        heapify(r);
        print_queue(r);
        cout << endl;

        r.clear();

        for(size_t j = 0; j < 10; ++j){
            cout << "inserting " << (j * 11 + 7) % 20 << endl;
            heap_insert(r, (j * 11 + 7) % 20 );
            
        }

        print_queue(r);
        cout << endl;

        
  }

    return 0;
}
