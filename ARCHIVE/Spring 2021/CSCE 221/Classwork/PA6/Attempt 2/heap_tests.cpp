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

    {//heap insert, delete
        vector<int> r;
        heap_insert(r, 10);
        print_vector(r);
        heap_insert(r, 5);
        print_vector(r);
        heap_insert(r, 1);
        print_vector(r);
        heap_insert(r, 20);
        print_vector(r);
        heap_insert(r, 9);
        print_vector(r);
        heap_insert(r, 3);
        print_vector(r);
        heap_insert(r, 2);
        print_vector(r);
        heap_insert(r, 5);
        print_vector(r);
        heap_insert(r, 4);
        print_vector(r);
        heap_insert(r, 15);
        print_vector(r);

        cout << "DELETE MIN" << endl;
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
        heap_delete_min(r);
        print_vector(r);
         try{
            heap_delete_min(r);
            print_vector(r);
         }
         catch(std::invalid_argument &e){cout << e.what() << endl;}
    }

  

    {
        vector<int> r;

        size_t j = 1;
        for(size_t i = 0; i < 10; ++i){
            j = (j*i + 97) % 100;
            heap_insert(r, j);
            cout << "size: " << r.size() << endl;
            print_queue(r);
        }

        for(size_t i = 0; i < 10; ++i){
            cout << "deleting " << heap_get_min(r) << "..." << endl;
            heap_delete_min(r);
            cout << "size: " << r.size() << endl;
            print_queue(r);
        }

        vector<int> g = {11,2,3,24,44,5,46,53,45,34,9,37};
        heapify(g);
        print_queue(g);
    }

    return 0;
}
