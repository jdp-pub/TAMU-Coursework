#include <stdexcept>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

double average(double values[], unsigned int size) {

  double temp = 0;
  double avg = 0;
  try
  {
    for(int i = 0; i < size; ++i)
    {
      if (typeid(values[i]) == typeid(double))
      {
              std::cout << values[i] << std::endl;
        temp += values[i];
      }
      else
      {
        throw 1;
      }
    }

    avg = temp / size;

  }
  catch (int n)
  {
    throw std::invalid_argument("Invalid Argument in function average()");
  }

  return avg;
}

int main ()
{
    int test[2];

    cin >> test[0];
    cout << test[0];
}