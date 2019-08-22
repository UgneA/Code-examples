using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include "Deri1.h"
#include "Deri2.h"
#include "Deri3.h"

int main()
{
  string in, word;
  char wClass;
  map<string, int> wordOcc;
  vector<string> smallest, biggest;
  int b = 0;
  typedef map<string, int>::iterator IT;
  typedef vector<string>::iterator vIT;
  vector<ReadWords*> v;

  //Attempts to open and read from a file specified by a user
  cout<<"Write name of a file you wish to read from: ";
  cin>>in;
  //Lets user choose which derived class to use
  cout<<"Write which(1,2 or 3) derived class you would like to use: ";
  cin>>wClass;
  //using a switch creates an object of the selected class
  switch (wClass){
    case '1':
      { v.push_back(new Deri1(in.c_str()) );
        break;
      }
    case '2':
      { v.push_back(new Deri2(in.c_str()) );
        break;
      }
    case '3':
      { v.push_back(new Deri3(in.c_str()) );
        break;
      }
    default: cout << "Invalid input";
    exit(1);
  }

  //stores every returned word into map and updates its occurrence count
  while( v[0]->isNextWord() )
  {
   word = v[0]->getNextFilteredWord();
   if(word != "")
       wordOcc[word]++;
  }

//sets smallest / biggest occurrence numbers
  int  s = wordOcc.size();
  IT it = wordOcc.begin();
  IT end = wordOcc.end();
  while(it!=end){
     if(it->second > b)
         b  = it->second;
     if(it->second < s)
         s = it->second;
  it++;
  }

//stores in a vector words with biggest/ smallest occurrence count
  IT itt = wordOcc.begin();
  while(itt!=end){
     if(itt->second == b)
         biggest.push_back(itt->first);
     if(itt->second == s)
         smallest.push_back(itt->first);
  itt++;
  }

/**prints number of entries in the map,
the word or words with the largest occurrence count(along with the count),
and the word or words with the smallest occurrence count (along with the count)*/
  cout<<"Total number of words in a map: "<<wordOcc.size()<<endl;

  cout<<"Word(s) with biggest occurrence count ("<<b<<") :"<<endl;
   for(vIT itB = biggest.begin(); itB!=biggest.end(); itB++)
   { cout<<*itB<<endl;
   }
    if(biggest.size()>10)
    cout<<"and "<<biggest.size()-10<<" more word(s)"<<endl;

   cout<<"Word(s) with smallest occurrence count ("<<s<<") :"<<endl;
   for(int i = 0; i<10; i++)
   { cout<<smallest[i]<<endl;
   }
   if(smallest.size()>10)
    cout<<"and "<<smallest.size()-10<<" more word(s)"<<endl;
}
