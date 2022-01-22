#include <stdexcept>
#include <string>
#include <iostream>
using std::string;
#include "taxi_trips.h"


bool is_payment_valid(string type, string valid_types[], unsigned int size) {
  int vType = 0;

  try
  { 
    if (size < 1)
    {
      throw 1;
    }
    for (unsigned i = 0; i < size; ++i)
    { 
      if (type == valid_types[i])
      {
        ++vType;
      }
    }
    if (vType)
    {
      return true;
    }
  }
  catch (int n)
  {
      throw std::invalid_argument("Invalid Argument in function is_payment_valid()");
  }

  return false;
}

double max(double values[], unsigned int size) 
{
  double maximum = 0;
  try
  {
    for(unsigned i = 0; i < size; ++i)
    {
      if (typeid(values[i]) == typeid(double))
      {
              if(values[i] > maximum)
              {
                maximum = values[i];
              }
      }
      else
      {
        throw 1;
      }
    }
    if (size <= 0)
    {
      throw 1;
    }
  }
  catch (int n)
  {
    throw std::invalid_argument("Invalid Argument in function max()");
  }

  return maximum;
}

double min(double values[], unsigned int size) {
    double minimum = values[0];
  try
  {
    for(unsigned i = 0; i < size; ++i)
    {
      if (typeid(values[i]) == typeid(double))
      {
        if(values[i] < minimum)
        {
          minimum = values[i];
        }
      }
      else
      {
        throw 1;
      }
    }
    if (size <= 0)
    {
      throw 1;
    }
  }
  catch (int n)
  {
    throw std::invalid_argument("Invalid Argument in function min()");
  }

  return minimum;
}

double average(double values[], unsigned int size) {

  double temp = 0;
  double avg = 0;
  try
  {
    for(unsigned i = 0; i < size; ++i)
    {
      if (typeid(values[i]) == typeid(double))
      {
        temp += values[i];
      }
      else
      {
        throw 1;
      }
    }
    if (size <= 0)
    {
      throw 1;
    }

    avg = temp / size;

  }
  catch (int n)
  {
    throw std::invalid_argument("Invalid Argument in function average()");
  }

  return avg;
}

double mode(double values[], unsigned int size) {
  int temp = 0;
  int temp1 = 0;
  int numTot= 0;
  try
  {
    if (size <= 0)
      {
        throw 1;
      }

for (unsigned i = 0; i < size; ++i)
{
  temp = 0;
    for(unsigned j = 0; j < size; ++j)
    {
      if (values[j] == values[i])
      {
        ++temp;
          if (temp > temp1)
          {
            numTot = values[i];
            temp1 = temp;
          }
      } 
      else
      {
        continue;
      }
           
    }
}
  }
  catch(int n)
  {
    throw std::invalid_argument("Invalid Argument in function mode()");
  }
  return numTot;
}

int length_longest_seq_zeros(double values[], unsigned int size) {
  int temp = 0;
  int numZero = 0;
  try
  {
    if (size <= 0)
      {
        throw 1;
      }

    for(unsigned j = 0; j < size; ++j)
    {
      

      if (values[j] == 0)
      {
        ++temp;
        if (j == size - 1)
        {
          if (temp > numZero)
        {
          numZero = temp;
        }
        temp = 0;
        }
      }
      else
      {
        if (temp > numZero)
        {
          numZero = temp;
        }
        temp = 0;
      }
      
    }
        
  }
  catch(int n)
  {
    throw std::invalid_argument("Invalid Argument in function length_longest_seq_zeros()");
  }
  
  return numZero;
}