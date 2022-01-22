#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"
#include "./string_calculator.cpp"

using std::cout, std::endl, std::cin;
using std::string;

int main() 
{
    string Input1;
    string Input2;
    string Result;
    char Operator;
    bool RunProgram = true;

    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    while (RunProgram)
    {

        try
        {
                cout << ">> " << endl;

        cin >> Input1; 

        if (Input1 == "q" || Input1 == "quit")
        {
            cout << "farvel!" << endl;
            break;
        }

        cin >> Operator >> Input2;

        Input1 = trim_leading_zeros(Input1);
        Input2 = trim_leading_zeros(Input2);

        if(Operator == '+')
        {
            Result = add(Input1, Input2);
        }
        if(Operator == '-')
        {
            Result = subtract(Input1, Input2);
        }
        if(Operator == '*')
        {
            Result = multiply(Input1, Input2);
        }
        

            cout << "ans = " << endl
             << endl
             << "    " << Result << endl << endl;
        }
        catch(...)
        {
            Input1 = "";
            Input2 = "";
            Operator = ' ';
            continue;
        }
    }

return 0;
}

