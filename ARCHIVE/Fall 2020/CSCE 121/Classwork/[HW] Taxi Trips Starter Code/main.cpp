#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "taxi_trips.h"
#include "taxi_trips.cpp"
using std::string, std::ifstream, std::cin, std::cout, std::endl, std::vector;

int main() {
  const unsigned int MAX_TRIPS = 10000;
  
  string filename;
  string storage;

  vector<string> trip;
  vector<string> duration;
  vector<string> distance;
  vector<string> price;
  vector<string> tip;
  vector<string> payment;

  cout << "Enter name of input file: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) 
  {
    cout << "Can't open " << filename << endl;
    return 0;
  }
  //loads a series of vectors with necessary data
  while(getline(ifs, storage))
  {
    string temp = "";
    for (unsigned i = 0; i < storage.size(); ++i)
    {
      
      if(storage.at(i) == ' ')
      {
        trip.push_back(temp);
        temp = "";
        ++i;
        for (i; i < storage.size(); ++i)
        {
          
          if(storage.at(i) == ' ')
          {
            duration.push_back(temp);
            temp = "";
            ++i;
            for (i; i < storage.size(); ++i)
            {
              if(storage.at(i) == ' ')
              {
                distance.push_back(temp);
                temp = "";
                ++i;
                for (i; i < storage.size(); ++i)
                {
                  if(storage.at(i) == ' ')
                  {
                    price.push_back(temp);
                    temp = "";
                    ++i;
                    for (i; i < storage.size(); ++i)
                    {
                      if(storage.at(i) == ' ')
                      {
                        tip.push_back(temp);
                        temp = "";
                        ++i;
                        for (i; i < storage.size(); ++i)
                        {
                          if(i == storage.size() - 1)
                          {
                            temp.push_back(storage.at(i));
                            payment.push_back(temp);
                            temp = "";
                            break;
                          }
                          temp.push_back(storage.at(i));
                        }
                        break;
                        //////////////////////////////////////////////////////
                      }
                      temp.push_back(storage.at(i));
                    }
                    break;
                    /////////////////////////////////////////////////////
                  }
                  temp.push_back(storage.at(i));
                }
                break;
                //////////////////////////////////////////////////////
              }
              temp.push_back(storage.at(i));
            }
            break;
            /////////////////////////////////////////////////
          }
          temp.push_back(storage.at(i));

        }
        break;
      //////////////////////////////////////////////
      }
      temp.push_back(storage.at(i));  
    }
    //end of while loop
  }

  double durationArr[duration.size()];

  cout << "Number of trips: " << trip.size() << endl
       << "Number of trips with invalid data: " << endl
       << "Duration: max " << max(duration, duration.size()) << "min " << min(duration, duration.size()) << "avg " << avg(duration, duration.size()) << "mode " << max(duration, duration.size()) << endl
       << "Distance: max " << max(distance, distance.size()) << "min " << max(distance, distance.size()) << "avg " << max(distance, distance.size()) << "mode " << max(distance, distance.size()) << endl
       << "Fare: max " << max() << "min " << << "avg " << << "mode " << << endl
       << "Tip: max " << max() << "min " << << "avg " << << "mode " << << endl
       << "Length of longest sequence without tips: " << endl;
  return 0;
}