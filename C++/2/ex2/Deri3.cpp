using namespace std;

#include <string>
#include <cctype>
#include "Deri3.h"

//constructor that invokes constructor of the base class
Deri3::Deri3(const string &filename):
    ReadWords(filename){}

//returns true if supplied word is a non-empty string that contains
//at least one letter and at least one punctuation character
 bool Deri3::filter(string word)
{ string s = word;
  int len = s.size();

  bool hasLett = false;
  bool hasPunc = false;
  for(int i = 0; i<len; ++i)
  {
    if(isalpha(s[i]))
        hasLett = true;
    if(ispunct(s[i]))
        hasPunc = true;

    if(hasLett && hasPunc)
     return true;
  }
  return false;
}
