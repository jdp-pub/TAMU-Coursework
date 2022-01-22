#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl, std::vector;

int main() {
    // TODO(student): write your answer (i.e. comments, code) here
    /* PSUDOCODE SOLUTION
    *
    *  initialize vector of ints
    * initialize min at 10, max at 0, count of valid terms at 0, and average at 0
    *  While the input != 0
    *  pushback input to vector
    *  
    *  for i < vector.size()
    *   if vector[i] < 0 continue, skips negative values
    *   avg += vector[i]
    *   count ++
    *   if vector[i] < min, reassign min to vector[i]
    *   if vector[i] > max, reassign max to vector[i]
    * 
    *   after for loop breaks, avg /= count
    * 
    *   set up UI for displaying information as noted in handout.
    */

   vector<int> inputTest;
   int min = 10;
   int max, avg, count = 0;
   int input;

    //input parameter
    while (cin >> input)
    {
        if(input == 0)
        {
            break;
        }
        inputTest.push_back(input);
    }

    for(unsigned i = 0; i < inputTest.size(); ++i)
    {
        if (inputTest.at(i) < 0)
        {
            continue;
        }
        avg += inputTest.at(i);
        ++count; // counts valid numbers

        if(inputTest.at(i) < min)
        {
            min = inputTest.at(i); // sets minimum value
        }
        if(inputTest.at(i) > max)
        {
            max = inputTest.at(i); // sets maximum value
        }
    }

    avg /= count; //averages average over the input

    cout << "min " << min << " max " << max << " average " << avg << endl;
}
