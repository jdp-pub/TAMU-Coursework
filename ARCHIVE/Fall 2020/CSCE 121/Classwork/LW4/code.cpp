#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using std::cin, std::cout, std::endl, std::string, std::getline,
      std::ifstream, std::istringstream;

int main() 
{
    string uin;
    std::vector<string> uinList;
    std::vector<double> donation;
    std::vector<std::vector<double>> donationList;
    string storage;
    string filename;
    cout << "Enter donation filename: ";
    cin >> filename;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
    cout << "Failed to open file " << filename << "." << endl;
    return 1;
    }

    double maxTotalDonation = 0;
    int maxTotalCollector = 0;

    //loads vectors with relevant information from file
    while (getline(ifs, storage))
    {
        for(unsigned i = 0; i < storage.size(); ++i)
        {
            uin.push_back(storage.at(i));
            if (storage.at(i) == ' ')
            {
                string temp;
                for(unsigned j = i + 1; j < storage.size(); ++j)
                {
                    if(storage.at(j) == ' ')
                    {
                        continue;
                    }

                    temp.push_back(storage.at(j));
                    
                    if((j == storage.size() - 1 || storage.at(j + 1) == ' '))
                    {
                        try // i dont know how else to handl this, throws an error for stod() on a space char ' ', which should have been skipped in line 40
                        {
                            donation.push_back(std::stod(temp));
                            temp = "";
                        }
                        catch(const std::exception& e)
                        {
                            temp = "";
                            continue;
                        }
                        
                    }
                }
                break;
            }
        }
        if(donation.size() > 1)
        {
            uinList.push_back(uin);
            donationList.push_back(donation);
        }
        donation.clear();
        uin = "";
    }
    ifs.close(); // closes open stream

    /*
    * add each vector from donations list into one number, store in donation
    * find maximum in donation, whichever is highest, assign to max with uin position in uin vector
    */
   double don = 0;
   bool increment = true;
   if(donationList.size() != 0)
   {
   for(unsigned i, j = 0; i < donationList.at(j).size(); i = i)
   {
       don += donationList.at(j)[i];

       if(i == donationList.at(j).size() - 1)
       {
           if(donationList.at(j).size() != 1)
           {
                donation.push_back(don);
           }

           if (j == donationList.size() - 1)
           {
               break;
           }
           increment = false;
           don = 0;
           ++j;
       }

       // tells loop when to increment iterator, should probably be done with while loop
       if(increment)
       {
           ++i;
       }
       else
       {
           i = 0;
           increment = true;
       }
       
   }
   }
    else
    {
        cout << "No donations." << endl;
        return 0;
    }
    
    int maxIndex = 0;

    for (unsigned i = 0; i < donation.size(); ++i)
    {
        if(maxTotalDonation < donation.at(i))
        {
            maxTotalDonation = donation.at(i);
            maxIndex = i;
        }
    }
    if(stoi(uinList.at(maxIndex)))
    {
    maxTotalCollector = stoi(uinList.at(maxIndex));
    }

        cout << "Highest donation total: " << maxTotalDonation << endl;
        cout << "-- collected by id: " << maxTotalCollector << endl;

}