/*
AUTHORS: J. Robillard, C. Suggs, A. Thomas, J. Vasseur, K. Washington
PROGRAM: Scanner
CLASS: CSI465-01SC
Professor: Dr. Pokorny
DATE CODED: 2 / 20 / 2017
------------------------------------------------------------------------------
USE: This program will serve as the scanner portion of our compiler.

NOTES: We had quite a few issues implementing RealLitTokens. This version is
finicky when dealing with real numbers, however, we hope to remedy this issue
as we move forward and begin wrapping up the compiler, as we are aware this
will reduce the capability of what the compiler is able to achieve.
Aside from that issue we were able to produce a scanner that will hopefully
play nice with the other components of the compiler.
-----------------------------------------------------------------------------
*/
#ifndef Scanner_H_INCLUDED
#define Scanner_H_INCLUDED


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Scanner
{
	public:
	struct TOKENS                                                                         //TOKENS struct; used to create a vector of this type that will hold the tokens generated.
	{
		string token_name;                                                                //string to hold the name of the generated token
	};

	//PROTOTYPES//
	void print_tokens(vector<TOKENS> tokens);                                             //function to print tokens generated. this will more than likely be removed as it was used for testing.

	void elements_delete(vector<char>code, vector<TOKENS> tokens, int counter);           //function to delete the number of character from the code vector that was used to generate the token

	void build_tokens(vector<char> code, vector<TOKENS> tokens);                          //function that will iterate through the code vector looking for tokens

	void load_code(vector<char> code, vector<TOKENS> tokens);                             //function to read from the 'code.txt' file which holds the tokens to pass to the scanner

	void initial();                                                                       //function that will call the build function, may be removed in the final compiler build
																						  //----------------------------------------//


};
#endif