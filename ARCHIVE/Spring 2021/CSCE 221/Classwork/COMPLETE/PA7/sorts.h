#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <vector>

using std::cout, std::endl;

// Pretty printing for vectors of Printable objects (have ostream operator<< defined)
// Be careful: modifications risk failing tests
template <class Printable>
std::ostream& operator<<(std::ostream& os, const std::vector<Printable>& container) {
    os << "[";
    bool first = false;
    for (const Printable& t : container) {
        if (first) {
            os << ", ";
        }
        if (typeid(t) == typeid(std::string)) {
            os << "\"" << t << "\"";
        } else {
            os << t;
        }
        first = true;
    }
    os << "]";
    return os;
}

// Selection sort (example of implementation expectations)
template <class Comparable>
void selection_sort(std::vector<Comparable>& container) {
    // print the initial container
    std::cout << container << std::endl;
    
    if (container.empty()) {
        return;
    }

    for (size_t index = 0; index < container.size()-1; index++) {
        // do 1 pass of selection sort: find the min and swap it to the front
        size_t index_min = index;
        for (size_t i = index+1; i < container.size(); i++) {
            if (container[i] < container[index_min]) {
                index_min = i;
            }
        }
        Comparable t = container[index];
        container[index] = container[index_min];
        container[index_min] = t;
        
        // print the container after each pass
        std::cout << container << std::endl;
    }
}

// TODO(student): implement 4 sorts from: insertion, shell, heap, merge, quick, bucket, radix
template <class Comparable>
void insertion_sort(std::vector<Comparable>& r){
    if(r.size() == 0){ cout << r << endl; return; }

    for(size_t i = 1; i < r.size(); ++i){
        cout << r << endl;
        for(size_t j = i; j > 0; --j){
            if (r.at(j) < r.at(j-1)){
                Comparable temp = r.at(j);
                r.at(j) = r.at(j-1);
                r.at(j-1) = temp;
            }
            else{ break; }
        }
    } 
    cout << r << endl;
}

size_t hibbard(const size_t N, size_t iteration){
    size_t h = 0;
    size_t k = 0;
    size_t n = N;
    //h = 2^k - 1 for all k, where the maximum k generates an h that is less than N/2
    if(N == 1){return 0;}
    while(n >= 2){ n /=2; ++k;}
    if(iteration > k){return 0;}
    k -= iteration;

    while(k > 0){ n *=2; --k;}
    h = n-1;

    return h;
}

template <class Comparable>
void shell_sort(std::vector<Comparable>& r){
    if(r.size() == 0){ cout << r << endl; return; }

    size_t h = hibbard(r.size(), 0);
    size_t inc = 0;

    cout << r << endl;
    while (h > 0){
        h = hibbard(r.size(), inc);
        if(h == 0){ break; }
        ++inc;
        for(size_t i = h; i < r.size(); ++i){
            for(size_t j = i; j-h >= 0 && j >= h; j -=h){
                if (r.at(j) < r.at(j-h)){
                    Comparable temp = r.at(j);
                    r.at(j) = r.at(j-h);
                    r.at(j-h) = temp;
                }
                else{ break; }
            }
        } 
        cout << r << endl;
    }
}

template <class Comparable>
void heap_sort(std::vector<Comparable>&){}

template <class Comparable>
void merge_sort(std::vector<Comparable>&){}

template <class Comparable>
void quick_sort(std::vector<Comparable>& ){}

void bucket_sort(std::vector<unsigned>& r){
    if(r.size() == 0){ cout << r << endl; return; }
    size_t max = r.at(0);
    cout << r << endl;
    for(size_t i = 0; i < r.size(); ++i) {if (max < r.at(i)){max = r.at(i);}}

    std::vector<unsigned> arr(max + 1, 0);

    for(size_t i = 0; i < r.size(); ++i) { ++arr.at(r.at(i)); }
    cout << arr << endl;
    r.clear();
    for(size_t i = 0; i < arr.size(); ++i) { 
        if(arr.at(i) != 0){
            for(size_t j = 0; j < arr.at(i); ++j){
                r.push_back(i);
            }
            cout << r << endl;
        }
    }
}

template <class Comparable>
void radix_sort(std::vector<Comparable>& r){
    if(r.size() == 0){ cout << r << endl; return; }

    Comparable max = r.at(0);
    cout << r << endl;
    for(size_t i = 0; i < r.size(); ++i) {if (max < r.at(i)){max = r.at(i);}}

    size_t passes = 0;
    while (max > 0){ max /= 10; ++passes;}
    
    
    size_t index;

    for(size_t i = 0; i < passes; ++i){
        std::vector<std::vector<Comparable>> buckets(10);
        for(size_t j = 0; j < r.size(); ++j){
            index = r.at(j);
            for(size_t k = 0; k < i; ++k){
                index /= 10;
            }
            buckets.at(index % 10).push_back(r.at(j));
        }
        r.clear();

        for(size_t j = 0; j < buckets.size(); ++j){
            cout << buckets.at(j) << " ";
        }
        cout << endl;

        for(size_t j = 0; j < buckets.size(); ++j){
            for(size_t k =0; k < buckets.at(j).size(); ++k){
                r.push_back(buckets.at(j).at(k));
            }
        }
        cout << r << endl;
    }
}

void radix_sort(std::vector<std::string>& r){
    if(r.size() == 0){ cout << r << endl; return; }

    size_t max = r.at(0).size();
    cout << r << endl;
    
    for(size_t i = 0; i < r.size(); ++i) { if (max < r.at(i).size()){max = r.at(i).size();} }

    for(size_t i = max; i > 0; --i){
        std::vector<std::vector<std::string>> buckets(128);
        for(size_t j = 0; j < r.size(); ++j){
            if(i-1 >= r.at(j).size()){buckets.at(0).push_back(r.at(j)); continue;}
            buckets.at((size_t)(r.at(j).at(i-1))).push_back(r.at(j));
        }
        r.clear();
        
        for(size_t j = 0; j < buckets.size(); ++j){
            cout << buckets.at(j) << " ";
        }
        cout << endl;

        for(size_t j = 0; j < buckets.size(); ++j){
            for(size_t k =0; k < buckets.at(j).size(); ++k){
                r.push_back(buckets.at(j).at(k));
            }
        }
        cout << r << endl;
        
    }
    
}



#endif  // SORTS_H