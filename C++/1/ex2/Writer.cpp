using namespace std;

#include <iostream>
#include <cstdlib>
#include "Writer.h"


/*Constructor to create a file.Prints an error message then
 terminates the program if it cannot create the file.*/
Writer::Writer(const char *filename)
{
    out.open(filename);
    if (!out)
    {   cout << "cannot create " << filename << endl;
        exit(1);
    }
}

//writes an integer to the file
void Writer::writeInt(int n)
{
    out<<n;
    cout<<n;
}

//writes a character to the file
void Writer::writeChar(char s)
{
    out<<s;
    cout<<s;
}

//writes a string to the file
void Writer::writeString(string s)
{
    out<<s;
    cout<<s;
}

//writes newline character to the file
void Writer::writeEol()
{
    out<<"\r\n";
    cout<<endl;
}

//closes the file
void Writer::close()
{
    out.close();
}
