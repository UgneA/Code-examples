using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "ReadWords.h"

/* Constructor. Opens the file with the given filename.Prints an error message
 then terminates the program if file does not exist.*/
ReadWords::ReadWords(const char *filename )
{
    wordfile.open(filename);

     if (!wordfile)
    {   cout << "Failed to open " << filename << endl;
        exit(1);
	}
}

/*Returns a string, being the next word in the file. All letters are
converted to lower case. Leading and trailing punctuation marks are not included in the word*/
string ReadWords::getNextWord()
{
   nextword.clear();
   char n = wordfile.get();
		
   while (this->isNextWord() && (!isspace(n)) && (!isdigit(n)) ) //while next character is not a space or digit adds it to the word
    {
       nextword+=tolower(n);
       n = wordfile.get();
    }

	//removes punctuation marks
  while( nextword != "" && (!isalpha(*nextword.begin()) || !isalpha(*nextword.rbegin())) )
    {

    if( ispunct(*nextword.rbegin()) )
     {
      nextword = nextword.substr(0, nextword.length() - 1) ;
     }
    else if ( ispunct(*nextword.begin()) )
      {
      nextword = nextword.substr(1 , nextword.length());
      }
    }

    if (nextword=="")
      return nextword;
    else
      return nextword + "\n";
}

//Returns true if there is a further word in the file, false if it has reached the end of file.
bool ReadWords::isNextWord()
{
        if (wordfile.eof())
            return false;
        return true;
}

//Closes the file.
void ReadWords::close()
{
    wordfile.close();
}
