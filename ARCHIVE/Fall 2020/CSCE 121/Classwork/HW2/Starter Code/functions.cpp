#include "functions.h"

bool is_valid_range(int a, int b) 
{   
    return ((a <= b) && (a > 0) && (b <= 10000));
}

int count_digit_occurrences(int number, int digit) {
  // TODO(student): return how many times digit occurs in number

    if (number < 0)
    {
        number = -1 * number;
    }

    int numStore[100];
    int numDigits = 0;
    int occurrences = 0;

    if (number == 0 && digit == 0)
    {
        return 1;
    }
    
    while (number != 0)
    {
        numStore[numDigits] = number % 10;
        ++numDigits;
        number /= 10;
    }

    for (int i = 0; i < numDigits; ++i)
    {
            if (numStore[i] == digit)
            {
                ++occurrences;
            }
    }

  return occurrences;
}

bool has_repeated_digits(int number) {
    // TODO(student): return true if number has repeated digits
    bool bRepeats = false;

    while (number != 0)
    {
        if(count_digit_occurrences(number, number % 10) > 1)
        {
            bRepeats = true;
            break;
        }
        number /= 10;
    }

    return bRepeats;

}

int count_valid_numbers(int a, int b) {
    // TODO(student): return count of valid numbers in range
    int count = 0;
    
    while (a <= b)
    {

       if(has_repeated_digits(a))
       {
           ++count;
       }
        ++a;
    }
    return count;
}
