using namespace std;

#include <iostream>
#include <fstream>
#include <map>
#include "ReadWords.h"
#include "Writer.h"

int main()
{
    string in, in2, out; //variables to store names for input and output files
    int wordCount = 0;   // total number of words
    map<string,int> wordOcc; // stores occurrences of search words


    cout<<"Write name of a file you wish to read from: ";
    cin>>in;
    ReadWords script(in.c_str());

    cout<<"Write name of a file containing search words: ";
    cin>>in2;
    ReadWords wordFile(in2.c_str());

    cout<<"Write a name for a file you wish to write to: ";
    cin>>out;
    Writer outFile(out.c_str());

	//stores search words into a map
    while(wordFile.isNextWord())
     {

       string testw = wordFile.getNextWord();
       if(testw!="")
       wordOcc[testw];
     }
	//reads file until it reaches end. If a search word occurs within the text ,updates number of times it occured
    while(script.isNextWord())
     {
       string word = script.getNextWord();

       if (word=="");
       else
        {
         map<string,int>::iterator it;
         it= wordOcc.find(word);
         if( it!=wordOcc.end())
            wordOcc[word]++;
        wordCount++;
        }
     }
	 //outputs number of times each of search words occured
    map<string, int>::iterator it;
    for ( it = wordOcc.begin(); it != wordOcc.end(); it++ )
      {
        string key = it->first;
        int value = it->second;
        outFile.writeString(key+ " occurs: ");
        outFile.writeInt(value);
        outFile.writeString(" time(s)");
        outFile.writeEol();
        outFile.writeEol();
      }

     outFile.writeString("Total number of words in the script is ");
     outFile.writeInt(wordCount);
     outFile.writeEol();
	//closes input and output files
     script.close();
     wordFile.close();
     outFile.close();

    return 0;
}

