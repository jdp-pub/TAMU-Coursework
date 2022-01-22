#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl, std::invalid_argument;
using std::string, std::to_string, std::cin;

int main ()
{
    string input1, input2;
    cin >> input1 >> input2;

    cout << "Result: " << add(input1, input2) << endl;
    return 0;
}

bool IsLetter(char test)
{
    if (test == '1' || test == '2' || test == '3' || test == '4' ||test == '5' || test == '6' ||
        test == '7' ||test == '8' ||test == '9' ||test == '0')
        {
            return false;
        }
        else
        {
            return true;
        }
        
}

unsigned int digit_to_decimal(char digit) {
    int decimal = 0;
    try
    {
        if ( IsLetter(digit) )
        {
            throw 1;
        }
        else
        {
            decimal = (int)(digit);
        }
        
    }
    catch(int n)
    {
            if (n == 1)
            {
                throw invalid_argument("Invalid Argument");
            }
    }
    return decimal - 48;
}

char decimal_to_digit(unsigned int decimal) {
    char digit = (char)(decimal + 48);
    try
    {

        if ( IsLetter(digit)) 
        {
            throw 1;
        }

        
    }
    catch(int n)
    {
            if (n == 1)
            {
                throw invalid_argument("Invalid Argument");
            }
    }
    
    return digit;
}

string trim_leading_zeros(string num) {

    string numTrimmed;
    for (unsigned i = 0; i < num.length(); ++i)
    {
        if(num[i] == '-' && i == 0)
        {
            numTrimmed.push_back('-');
            ++i;
        }
        if (num[i] == '0')
        {
            continue;
        }
        else
        {
            for (unsigned j = i; j < num.length(); ++j)
            {
                numTrimmed.push_back(num[j]);
            }

            return numTrimmed;
        }
    }
    if(numTrimmed.length() == 1)
    {
        numTrimmed.pop_back();
        numTrimmed.push_back('0');
    }
    else 
    {
        numTrimmed.push_back('0');
    }
    return numTrimmed;
}

string add(string lhs, string rhs) {
    int lhsLength = lhs.size() - 1;
    int rhsLength = rhs.size() - 1;
    int Holdover = 0;
    int Add = 0;

    string Result;
    string FlipResult;
    while ((rhsLength + 1) && (lhsLength + 1))
    {  

        int num1 = digit_to_decimal(lhs[lhsLength]);
        int num2 = digit_to_decimal(rhs[rhsLength]);

        Add = num1 + num2 + Holdover;
        
        Result.push_back((char)(Add % 10 + 48));
        Holdover = Add / 10;
        --lhsLength;
        --rhsLength;

        cout << lhsLength << " " << rhsLength << endl;
    }
    if (rhsLength == -1)
    {
        for(lhsLength; lhsLength >= 0; --lhsLength)
        {
            Result.push_back(lhs[lhsLength]);
        }
    }
    if (lhsLength == -1)
    {
        for(rhsLength; rhsLength >= 0; --rhsLength)
        {
            Result.push_back(rhs[rhsLength]);
        }
    }
    for(int i = 1; i <= Result.size(); ++i)
    {
        FlipResult.push_back(Result.at(Result.size() - i));
    }
    return FlipResult;
}

string subtract(string lhs, string rhs) {


    return 0;
}

string multiply(string lhs, string rhs) {


    return 0;
}
