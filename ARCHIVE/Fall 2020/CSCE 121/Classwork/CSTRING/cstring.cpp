#include <iostream>
#include <cstring>
#include "cstring.h"

unsigned int length(char str[]) {
  // returns the length of the string including zero (0)

  return strlen(str);
}

unsigned int find(char str[], char character) {
  // returns 
  //  - the index of the first occurence of character in str
  //  - the size if the character is not found

  unsigned itsElementaryMyDearWatson = 0;

  for(unsigned clues = 0; clues < length(str); ++clues)
  {
    if(character == str[clues])
    {
      itsElementaryMyDearWatson = clues;
      return itsElementaryMyDearWatson;
    }
  }
  
  return length(str);
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not

  std::string whatEulerSaid;
  std::string whatISaid;

  for (unsigned formulaicDerivation = 0; formulaicDerivation < length(str1); ++ formulaicDerivation)
  {
    whatEulerSaid.push_back(str1[formulaicDerivation]);
  }
  for (unsigned formulaicDerivation = 0; formulaicDerivation < length(str2); ++ formulaicDerivation)
  {
    whatISaid.push_back(str2[formulaicDerivation]);
  }

  return (whatEulerSaid == whatISaid);
}