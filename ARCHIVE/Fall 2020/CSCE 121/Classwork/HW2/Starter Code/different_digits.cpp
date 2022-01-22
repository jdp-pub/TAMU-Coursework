#include <iostream>
#include <limits>
#include "functions.h"


using std::cout, std::cin, std::endl;

int main() 
{
    int numInitial, numFinal;
    int count = 0;
while (1)
{
    // TODO(student): print prompt for input
    cout << "Enter numbers 0 < a <= b <= 10000: ";

    // TODO(student): read the numbers from standard input
    cin >> numInitial >> numFinal;

    // TODO(student): validate input (and reprompt on invalid input)
    if(is_valid_range(numInitial, numFinal))
    {

        // primary calculation goes her
        count = count_valid_numbers(numInitial, numFinal);
        break;
    }
    else
    {
        cout << "Invalid input" << endl;
    }
}
        

    // TODO(student): compute and display solution
    cout << "There are " << count << " valid numbers between " << numInitial << " and " << numFinal << std::endl;


    return 0;
}
