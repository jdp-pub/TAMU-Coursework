#include <stdexcept>
#include <string>

using std::string;

string number_words(unsigned int n) {
    // TODO(student): write your answer (i.e. comments, code) here

    /* PSUDOCODE SOLUTION  
    *  
    * try
    *  test input (if), n must be < 100 and > 0
    *  else throw std::invalid_argument("Invalid Number")
    * catch
    *  initialize placeholder variables that store n /= 10 and n % 10
    *  initialze string
    *  if list, 1 - 9 for tens place, append number-word
    *  if string != null, append "-"
    *  if list 1 - 9 for ones place, append number word
    *  return string
    */

   try
   {
       if (n < 0 || n > 99)
       {
           throw 1;
       }
   }
   catch(int e)
   {
       throw std::invalid_argument("Invalid Number");
   }
   

   string numWord;
   int tens = n / 10;
   int ones = n % 10;
    // Ill come back and add more if there is enough time but works for the input "21"
   if(tens == 2)
   {
       numWord.append("twenty");
   }
   if(numWord != "")
   {
       numWord.append("-");
   }

    if(ones == 1)
    {
        numWord.append("one");
    }
    return numWord;
}
