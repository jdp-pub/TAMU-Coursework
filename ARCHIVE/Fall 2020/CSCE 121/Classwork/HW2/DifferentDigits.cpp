#include <iostream>

/*
given a range between a user defined a and b, counts the amount of numbers with repeated digits and displays in terminal
*/

//carries out primary computation of script
int CompareDigits(int numInitial, int numFinal)
{
    //number of numbers with repeated digits
    int count;
    bool bEndIteration = false;

    for (numInitial; numInitial <= numFinal; ++numInitial)
    {
        int tempNumCheck = numInitial;
        int numDigits = 0;
        bEndIteration = false;

        //counts total number of digits
        while (tempNumCheck != 0)
        {
            tempNumCheck = tempNumCheck / 10;
            ++numDigits;
        }

        //stores numbers from digits individually
        int tempNumStore [5];
        for(int i = 0; i < numDigits; ++i)
        {
            tempNumStore[i] = numInitial % 10;
            numInitial = numInitial / 10; 
        }

        // iterates through array and compares every number until it finds a match, then increments numInitial to chekc the next number
        for(int i = 1; i < numDigits; ++i)
        {
            // makes sure that the iteration doesnt check beyond scope of array
            if (tempNumStore[i] && bEndIteration == false)
            {
                for(int j = 0; j < numDigits; ++j)
                {
                    if (tempNumStore[i] == tempNumStore[j] && bEndIteration == false)
                    {
                        ++count;
                        bEndIteration = true;
                    }
                }
            }
        }
    }

    return count;
}

int main()
{
    int numInitial, numFinal;
    bool bIsValid = false;

    // recurrent prompt for valid values
    while (bIsValid == false)
    {
        std::cout << "Enter numbers 0 < a <= b <= 10000:";
        std::cin >> numInitial >> numFinal;
        std::cout << "inpur recieved";
        if((numInitial <= numFinal) && (numInitial > 0) && (numFinal <= 10000))
        {
            std::cout << "is valid";
            bIsValid = true;
        }
        else
        {
            std::cout << "Invalid input." << std::endl;
        }
    }
    std::cout << "test";
    int numsWithRepeatedDigits = CompareDigits(numInitial, numFinal);

    std::cout << "There are " + numsWithRepeatedDigits << " valid numbers between " + numInitial << " and " + numFinal << std::endl;

}