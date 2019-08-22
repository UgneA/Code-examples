using namespace std;

#include <string>
#include "Deri2.h"

//constructor that invokes constructor of the base class
Deri2::Deri2(const string &filename):
    ReadWords(filename){}

//returns true if supplied word is a string containing exactly three vowels
 bool Deri2::filter(string word)
{ string s = word;
  int len = s.size();
  string vowels = "aeiouAEIOU";

  int vowelCount = 0;
  for (int i=0; i<len; ++i){
    size_t found = vowels.find(s[i]);
    if (found!=string::npos)
       vowelCount++;
  }

  if(vowelCount == 3)
    return true;
  return false;
}
