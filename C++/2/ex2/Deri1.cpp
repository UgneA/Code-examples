using namespace std;

#include <string>
#include <cctype>
#include "Deri1.h"

//constructor that invokes constructor of the base class
Deri1::Deri1(const string &filename):
    ReadWords(filename){}

//returns true if supplied word contains at least one upper-case letter
 bool Deri1::filter(string word)
{ string s = word;
  int len = s.size();

  for (int i=0; i<len; ++i){
     if(isupper(s[i]))
       return true;
  }
  return false;
}
