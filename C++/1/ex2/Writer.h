/**
 * WriteBasics Interface for Assignment 1
 */

#ifndef _WRITER_H_
#define _WRITER_H_

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
/**
 *  A class to write items to an arbitrary file.
    YOU ARE TO WRITE THE .CPP FILE THAT IMPLEMENTS THIS, AND ANY OTHER FUNCTIONS THAT
    YOU THINK ARE NECESSARY. THE WriteNumber CLASS FROM THE SECOND LAB SHOULD HELP.
 */
class Writer {
    private:
      ofstream out;

    public:
      /**
       * Constructor to create a file.
       * @param filename - a c style string like "fred.dat"
       * Prints an error message then terminates the program if it cannot create the file.
       */
      Writer(const char *filename);

      /**
       * writes an integer to the file, no end of line.
       * @param n - integer to write
       */
      void writeInt(int n);

     /**
       * Writes a character to the file, no end of line.
       * @param s - character to write.
       */
      void writeChar(char s);

      /**
       * Writes a string to the file, no end of line.
       * @param s - string to write.
       */
      void writeString(string s);

      /**
       * Writes a newline character to the file
       */
      void writeEol();

      /**
       * function to close the file, thus ensuring it is stable on disk,
       */
      void close();
};

#endif
