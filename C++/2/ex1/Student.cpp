using namespace std;

#include <string>
#include <map>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include "Student.h"

 // constructor initialises name and registration number using arguments
 // and initialises marks map to be empty
Student::Student(const string &name, int regNo):Person(name), marks(){
    this->regNo = regNo;
}

// method to return registration number
int Student::getRegNo() const{
    return regNo;
}

// method to add the mark to the map
// if a mark for the module is already present it should be overwritten
void Student::addMark(const string& module, float mark){
    if(marks.count(module)>0)
        marks[module]=mark;
    else
        marks.insert(make_pair(module,mark));
}

// method to retrieve the mark for a module
// should throw NoMarkException if student has no mark for that module
float Student::getMark(const string &module) const throw (NoMarkException)
{   map<string, float>::const_iterator it = marks.find(module);

    if( it==marks.end() )
	  throw NoMarkException("There are no marks for this module.");

	return marks.at(module);
}

//method to return marks map
map<string,float> Student::getMap()const {

    return marks;
}


// friend function to output details of student so stream
// should output name, regno, and minimum, maximum and average marks on a single line
// if the student has no marks "no marks" should be output instead of the marks
ostream& operator<<(ostream &str, const Student &s){

	//if student has no marks the folllowing is displayed
    if(s.marks.empty())				
        str<<left<<setw(20)<<s.name<<setw(10)<<s.regNo<<setw(10)<<"no marks"<<setw(10)<<"no marks"<<setw(10)<<"no marks";
    else{

    float miin = 100.0;
    float maax = 0.0;
    float avg = 0.0;
    int n = 0;
    float sum = 0.0;

    map<string, float>::const_iterator it = s.marks.begin();
    map<string, float>::const_iterator ennd = s.marks.end();
	
	//sets minimum, maximum marks and calculates average mark
    while(it!=ennd){
        if(miin > it->second)
            miin = it->second;
        if(maax < it->second)
            maax = it->second;
        n++;
        sum +=it->second;
        it++;
    }
    avg = static_cast<float>(sum)/n;
    str<<left<<setw(20)<<s.name<<setw(10)<<s.regNo<<setw(10)<<miin<<setw(10)<<maax<<setw(10)<<setprecision(4)<<avg;
}
    return str;
}

