#include <iostream>
#include <vector>
#include "sorts.h"

void ns(){ cout << "~~~~~~~~~~~~~~~~~" << endl; }

int main() {
    // TODO(student): write tests

    
    {//insertion sort tests
        std::vector<int> r = {};
        insertion_sort(r);

        r = {1};
        insertion_sort(r);
        ns();
        r = {1,2,3,4,5};
        insertion_sort(r);
        ns();
        r = {5,4,3,2,1};
        insertion_sort(r);
        ns();
        r = {3,2,6,5,1};
        insertion_sort(r);
        ns();
        std::vector<std::string> t = {"c", "b", "a"};
        insertion_sort(t);
        ns();
        t = {"a", "b", "c"};
        insertion_sort(t);
        ns();
        t = {"c", "b", "a"};
        insertion_sort(t);
        ns();
        t = {"c", "a", "g", "b", "e"};
        insertion_sort(t);

    }
    
    
    {//shell
        //get hibbard increment function correct
        size_t n = 1555;
        for(size_t i = 0; i < 10; ++i ){
            cout << hibbard(n, i) << endl;
        }

        

        std::vector<int> r = {};
        shell_sort(r);
        r = {1};
        shell_sort(r);
        ns();

        r = {1,1,1};
        shell_sort(r);
        ns();
        

        r = {1,2,3,4, 5};
        shell_sort(r);
        ns();

        r = {4,3,2,1};
        shell_sort(r);
        ns();

        r = {5,4,3,2,1};
        shell_sort(r);
        ns();

        std::vector<std::string> t = {"b","f","d","g","h","v","a","d","s","s"};
        shell_sort(t);
        ns();
        
    }
    
   
    {//bucket
        std::vector<unsigned> r = {};
        bucket_sort(r);
        r = {1};
        bucket_sort(r);
        ns();

        r = {1,2,3,4,5};
        bucket_sort(r);
        ns();

        r = {5,4,3,2,1};
        bucket_sort(r);
        ns();

        r = {1,2,3,4,5};
        bucket_sort(r);
        ns();

        r = {1,5,5,4,3,5};
        bucket_sort(r);
        ns();
    }
    
    {
        std::vector<int> r = {};
        radix_sort(r);
        r = {1};
        radix_sort(r);
        ns();
        
        r = {1, 2, 3, 4, 6, 9, 11, 47};
        radix_sort(r);
        ns();

        r = {47,11,9,6,4,3,2,1};
        radix_sort(r);
        ns();

        r = {4,9,3,11,2,6,47,1};
        radix_sort(r);
        ns();

        //"am first", "am second", "am third", "because", "before", "belonged, i", "carried", "carrions", "down the", "down turn", "for", "forever", "however", "hurt", "they", "were"
        std::vector<std::string> t = {"before", "am first", "down turn", "forever", "am third",  "however", "belonged, i", "because", "carrions", "down the","am second",  "for","were",   "hurt", "they", "carried"};
        radix_sort(t);
        ns();
    }
    
    return 0;
}
