#ifndef _DERI2_H_
#define _DERI2_H_

using namespace std;
#include <string>
#include "ReadWords.h"


class Deri2: public ReadWords
{   public:
		//constructor that invokes constructor of the base class
        Deri2(const string &filename);

        //returns true if supplied word is a string containing exactly three vowels
        bool filter(string word);

};

#endif // _DERI2_H_
