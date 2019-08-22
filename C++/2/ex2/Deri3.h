#ifndef _DERI3_H_
#define _DERI3_H_

using namespace std;
#include <string>
#include "ReadWords.h"


class Deri3: public ReadWords
{   public:
		//constructor that invokes constructor of the base class
        Deri3(const string &filename);

        //returns true if supplied word is a non-empty string that contains
		//at least one letter and at least one punctuation character
        bool filter(string word);

};

#endif // _DERI3_H_
