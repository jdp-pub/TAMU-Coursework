#include <iostream>
#include <vector>

using std::vector, std::cout, std::endl;

//  QUESTION 1 PART A

void print(vector<int> a) {
    for(size_t i = 0; i < a.size(); ++i) {
        cout << a.at(i) << endl;
    }
} //prints contents of a list, for debugging

bool contains(vector<int> a, int val) { //time complexity O(N)
    for(size_t i = 0; i < a.size(); ++i) {//O(N)
        if(a.at(i) == val) { return true;}//O(1)
    }
    return false;
}//checks for existence of a given value in a list

void nl() { cout << endl; } //format the console output

int main() {
    vector<int> a = {0, 2, 4, 6};
    vector<int> b = {0, 3, 6, 9, 12};

    print(a);
    nl();
    print(b);
    nl();

    vector<int> u = a; // copies over one list

    for(size_t i = 0; i < b.size(); ++i) {//iterates through other list O(N)
        if(!contains(u, b.at(i))) {//O(N)
            vector<int>::iterator index = u.begin();//O(1)
            
            size_t k = 0;//used as an index tracker, finds where the current value should go O(1)
            while(b.at(i) > u.at(k)) {++index; ++k; if(k >= u.size()) {break;}} //iterate through list to find sorted position O(N)
            if(k >= u.size()) {u.push_back(b.at(i)); continue; }//if current value is the largest, appends to rear O(1)
            else { u.insert(index ,1,  b.at(i));}// otherwise, puts value right between larger and smaller value O(1)
        }
    }// COMPOUNDED TIME COMPLEXITY O(N^2)

    print(u);
}

// EXPLANATION OF QUESTION 1, PART A:
/*
* The algorithm I initially proposed was poorly designed and had
* a few logical flaws. Namely, that if a value already existed in a list but wasn't
* at the current index, a duplicate would be copied to the union. 
*
* the new algorithm (the one above) fixes this issue by checking if the value exists 
* in the list already. It does this for every value so I was trying to avoid this method
* initially, but I did not figure out how to do this one with a time complexity of O(N)
*/

//  QUESTION 1 PART B
/*
* the total time complexity of this algorithm is
*
* [O(N) * O(2N+4)]
*
* this was deduced by adding time complexities on the same layer and multiplying 
* complexities within nested layers. Since O(2N+4) happens N times, it becomes N*O(2N+4)
*which then becomes O(2N^2+4N). As N diverges, the leading term dominates and the total time
* complexity becomes O(N^2).
*
*/

// EXPLANATION OF QUESTION 1, PART B:
/*
* My first attempt didn't show any work on how I got the answer
* so I provided a more detailed explanation.
*/