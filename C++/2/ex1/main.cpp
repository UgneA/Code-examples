using namespace std;

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Student.h"
//-----------------------functions--------------------------------------------
void printBetter(vector<Student> &studs, float mark);
void printBetterMod(vector<Student> &studs, string module, float mark);
bool sorting (const Student &s1, const Student &s2);
//-----------------------------------------------------------------------
main(){

string fullName, name, sur, mod, sName, mName, line, modName;
ifstream file;
char inp;
float mark, mar;
int regN;
bool found = false;
vector<Student> studentList;
set<string> mods;

/**Attempts to open and read from a file specified by a user*/
cout<<"Write the name of the file you wish to read from : "<<endl;
cin>>sName;
file.open(sName.c_str());

if(!file){
    cout<<"Failed to open "<<sName<<endl;
    exit(1);
}/**reads a line from a file and invokes Student constructor*/
while(file>>regN>>name>>sur){
    fullName = name+" "+sur;
    Student s(fullName, regN);
    studentList.push_back(s);
}
file.close();

/**Attempts to open and read from a file specified by a user*/
cout<<"Write the name of the file you wish to read from : "<<endl;
cin>>mName;
file.open(mName.c_str());

if(!file){
    cout<<"Failed to open "<<mName<<endl;
    exit(1);
}
/**Reads a line from a file and searches student collection for a student 
with supplied registration number if it is found adds marks for the module 
(or overwrites it if it already exists) otherwise displays a warning message*/
while(file>>regN>>mod>>mark){

    vector<Student>::iterator it = studentList.begin();
    vector<Student>::iterator ennd = studentList.end();
    mods.insert(mod);
    while(it!=ennd)
     {
        if( it->getRegNo() == regN)
        { it->addMark(mod,mark);
          found = true;
        }
        it++;
     }
    if (!found)
       cout<<"There is no student with registration number "<<regN<<endl;
    found = false;
}
file.close();


/**prints student's information and marks of all of his/her modules*/
vector<Student>::iterator it = studentList.begin();
vector<Student>::iterator end = studentList.end();

    while(it != end){
      cout<<left<<setw(20)<<it->getName()<<setw(8)<<it->getRegNo()<<endl;
      map<string,float> m = it->getMap();
      if(m.empty())
        cout<<"Student has no marks"<<endl;
      else{
        map<string,float>::iterator mit = m.begin();
        while(mit!=m.end()){
            cout<<mit->first<<" "<<mit->second<<endl;
            mit++;
        }
      }
      it++;
    }

/**loop that allows to choose which function to test*/
while(true)
{ cout<<"To test first function type 1, to test second function type 2, to leave type 0"<<endl;
  cin>>inp;
  if(inp=='1') {
    cout<<"Write a mark(press ENTER): ";
    cin>>mar;
    printBetter(studentList,mar);
    continue;
  }
  if(inp=='2') {
    cout<<"Write a module name(press ENTER) and a mark(press ENTER): ";
    cin>>modName>>mar;
    printBetterMod(studentList, modName.c_str(), mar);
    continue;
  }
  else if(inp=='0')
    break;
  else{
    cout<<"Invalid input try again."<<endl;
    continue;
  }
}

return 0;
}

/**function that displays information of all students (along with their average, minimum and 
maximum marks) who have at least one mark greater than the one supplied as second argument */
void printBetter( vector<Student> &studs, float mark)
{ bool found = false;

  sort(studs.begin(), studs.end(),sorting);			  //sorts collection by regisration number
  vector<Student>::iterator it = studs.begin();
    while( it!=studs.end() ){
      map<string,float> m = it->getMap();
      map<string,float>::iterator mit = m.begin();
      while( mit!=m.end() ){
         if( mark< mit->second ){
          cout<<*it<<endl;
          found = true;				//if at least one such student is found sets found to true
          break;
         }
         mit++;
      }
    it++;
    }
  if(!found)					//if there are no such students dispslays the following message
    cout<<"There are no students with at least one mark higher than "<<mark<<endl;
}
/**function that prints on the screen the name and mark for that module of each student
 in the collection who has a mark for that module that is greater than or equal to the
 one supplied as a third argument */
void printBetterMod(vector<Student> &studs, string module, float mark)
{ bool found = false;
  vector<Student>::iterator it = studs.begin();

  while( it!=studs.end() ){
      try{
        float itMark = it->getMark(module);
        if(itMark >= mark){
            cout<<setw(20)<<it->getName()<<setw(6)<<itMark<<endl;
            found = true;				//if at least one student is found , found is set to true
        }
      }
      catch(NoMarkException e){}
    it++;
    }
  if(!found)							//otherwise following message is displayed
    cout<<"There are no students with mark higher than or equal to "<<mark<<" for module "<<module<<endl;
}
//function that helps sort student collection by registration number
bool sorting (const Student &s1, const Student &s2) {return s1.getRegNo()<s2.getRegNo();}
