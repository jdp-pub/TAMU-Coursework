#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl, std::invalid_argument;
using std::string, std::to_string;

string ReverseString(string Input)
{
    string Result;
    for(unsigned i = 1; i <= Input.size(); ++i)
    {
        Result.push_back(Input.at(Input.size() - i));
    }
    return Result;
}

string NegateString(string Input2)
{
    string temp = ReverseString(Input2);

    if (Input2[0] == '-')
    {
        temp.pop_back();
    }
    else
    {
        temp.push_back('-');
    }

    Input2 = ReverseString(temp);
    return Input2;
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
    return (decimal - 48);
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
                throw invalid_argument("Invalid Argument2");
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
    string FlipNegative;
    string FlipNegative2;
    string Negative;
    string Negative2;
    bool bNegate = false;
    
    if (rhs[0] == '-' && lhs[0] == '-')
    {
        bNegate = true;
        for (int i = lhsLength; i >= 0; --i)
        {
            FlipNegative.push_back(lhs[i]);
        }
        for (int i = rhsLength; i >= 0; --i)
        {
            FlipNegative2.push_back(rhs[i]);
        }
        
        FlipNegative.pop_back();
        FlipNegative2.pop_back();
        for (int i = FlipNegative.size() - 1; i >= 0; --i)
        {
            Negative.push_back(FlipNegative[i]);
        }
        for (int i = FlipNegative2.size() - 1; i >= 0; --i)
        {
            Negative2.push_back(FlipNegative2[i]);
        }
        lhs = Negative;
        rhs = Negative2;
        --rhsLength;
        --lhsLength;

    }
    if(rhs[0] == '-' && lhs[0] != '-')
    {
        for (int i = rhsLength; i >= 0; --i)
        {
            FlipNegative.push_back(rhs[i]);
        }
        
        FlipNegative.pop_back();
        for (int i = FlipNegative.size() - 1; i >= 0; --i)
        {
            Negative.push_back(FlipNegative[i]);
        }
        return subtract(lhs, Negative);
    }
    if(rhs[0] != '-' && lhs[0] == '-')
    {
        for (int i = lhsLength; i >= 0; --i)
        {
            FlipNegative.push_back(lhs[i]);
        }
        
        FlipNegative.pop_back();
        for (int i = FlipNegative.size() - 1; i >= 0; --i)
        {
            Negative.push_back(FlipNegative[i]);
        }
        return subtract(rhs, Negative);
    }

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

    }
    if (rhsLength == -1)
    {
        for( int i = lhsLength; i >= 0; --i)
        {
            int num1 = digit_to_decimal(lhs[i]);

            Add = num1 + Holdover;
            
            Result.push_back((char)(Add % 10 + 48));
            Holdover = Add / 10;
        }
        if(Holdover)
        {
            Result.push_back((char)(Holdover + 48));
        }
    }
    else if (lhsLength == -1)
    {
        for(int i = rhsLength; i >= 0; --i)
        {
            int num2 = digit_to_decimal(rhs[i]);

            Add = num2 + Holdover;
            
            Result.push_back((char)(Add % 10 + 48));
            Holdover = Add / 10;
        }
        if(Holdover)
        {
            Result.push_back((char)(Holdover + 48));
        }

    }
    if (bNegate == true)
    {
        Result.push_back('-');
    }
    for(unsigned i = 1; i <= Result.size(); ++i)
    {
        FlipResult.push_back(Result.at(Result.size() - i));
    }
    return FlipResult;
}

string subtract(string lhs, string rhs) {
    int num1;
    int num2;
    string Result;
    int Holdover = 0;
    bool bNegateResult = false;

    if (lhs[0] == '-' && rhs[0] != '-')
    {
        rhs = NegateString(rhs);
        return add(lhs, rhs);
    }
    else if (rhs[0] == '-' && lhs[0] != '-')
    {
        rhs = NegateString(rhs);
        return add(lhs, rhs);
    }
    else if (lhs[0] == '-' && rhs[0] == '-')
    {
        lhs = NegateString(lhs);
        rhs = NegateString(rhs);
        string temp = lhs;
        lhs = rhs;
        rhs = temp;
    }
    if ((lhs.size() < rhs.size()))
    {
        string temp = lhs;
        lhs = rhs;
        rhs = temp;
        bNegateResult = true;
    }
    else if(lhs.size() == rhs.size())
    {
        for (unsigned i = 0; i < rhs.size(); ++i)
        {
            int check1 = digit_to_decimal(lhs[i]);
            int check2 = digit_to_decimal(rhs[i]);
            if (check1 == check2)
            {
                continue;
            }
            else if(check1 > check2 )
            {
                break;
            }
            else if(check1 < check2)
            {
                string temp1 = rhs;
                rhs = lhs;
                lhs = temp1;

                bNegateResult = true;

                break;
            }
        }
    }
    lhs = ReverseString(lhs);
    rhs = ReverseString(rhs);
    for(unsigned i = 0; i < rhs.size(); ++i) 
    { 
        num1 = digit_to_decimal(lhs[i]);
        num2 = digit_to_decimal(rhs[i]);
        int Sub = num1 - num2 - Holdover; 

        if (Sub < 0) 
        { 
            Sub += 10; 
            Holdover = 1; 
        }
        else
        {
            Holdover = 0;
        }

        Result.push_back(decimal_to_digit(Sub)); 
        if (i == rhs.size() - 1)
        {
            for(i = rhs.size(); i < lhs.size(); ++i)
            {
                num1 = digit_to_decimal(lhs[i]);
                int Sub = num1 - Holdover; 

                if(Sub < 0)
                {
                    Sub += 10;
                    Holdover = 1;
                }
                else
                {
                    Holdover = 0;
                }
                Result.push_back(decimal_to_digit(Sub));
            }
        }    
    }


    Result = ReverseString(Result);
    Result = trim_leading_zeros(Result);

    if (bNegateResult == true && Result != "0")
    {
        Result = NegateString(Result);
    }
    return Result;
    
}

string multiply(string lhs, string rhs) {
    string temp1;
    int MultiHold;

    bool bNegate = false;
    string Result;
    if ((lhs[0] == '-') ^ (rhs[0] == '-'))
    {
        bNegate = true;
        if (lhs[0] == '-')
        {
            lhs = NegateString(lhs);
        }
        else if (rhs[0] == '-')
        {
           rhs = NegateString(rhs);
        }
        
    }
    if ((lhs[0] == '-') && (rhs[0] == '-'))
    {
       lhs = NegateString(lhs);
        rhs = NegateString(rhs);
    }
    int lhsLength = lhs.size() - 1;
    int rhsLength = rhs.size() - 1;

    if (lhsLength > rhsLength)
    {
        string temp1 = rhs;
        rhs = lhs;
        lhs = temp1;

        lhsLength = lhs.size() - 1;
        rhsLength = rhs.size() - 1;
    }
    
        


    ///////////////
    /*
    *multiplication logic goes here
    * 
    *
    */
    for (int i = rhsLength; i >=0; --i)
    {
        string Multi1;
        string Multi2;
        int num1 = digit_to_decimal(rhs[i]);

        
            
        for(int j = lhsLength; j >= 0; --j)
        {
            for (unsigned k = 0; k < rhs.size() - i  - 1; ++k)
            {
                Multi1.push_back('0');
            }
            for (unsigned k = 0; k < lhs.size() - j  - 1; ++k)
            {
                Multi1.push_back('0');
            }
            
            int num2 = digit_to_decimal(lhs[j]);
            MultiHold = num1 * num2;
            if (MultiHold == 0)
            {
                Multi1.push_back('0');
            }
            else
            {
                while(MultiHold != 0)
                {
                    Multi1.push_back(decimal_to_digit(MultiHold % 10));
                    MultiHold /= 10;
                }
            }
            
            Multi1 = ReverseString(Multi1);
            //cout << Multi1 << endl;
            Multi2 = add(Multi1, Multi2);
            Multi1.erase();
        }
        
        Result = add(Result, Multi2);

    }
 
    ////////////////////////
    if(bNegate == true)
    {
        Result = NegateString(Result);
    }
    return Result;
}
