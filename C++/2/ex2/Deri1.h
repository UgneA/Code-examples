#ifndef _DERI1_H_
#define _DERI1_H_

using namespace std;
#include <string>
#include "ReadWords.h"


class Deri1: public ReadWords
{   public:
        //constructor that invokes constructor of the base class
        Deri1(const string &filename);

        //returns true if supplied word contains at least one upper-case letter
        bool filter(string word);

};

#endif // _DERI1_H_
