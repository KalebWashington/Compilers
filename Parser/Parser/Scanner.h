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
	void print_tokens(vector<TOKENS>& tokens);                                             //function to print tokens generated. this will more than likely be removed as it was used for testing.

	void elements_delete(vector<char>code, vector<TOKENS>& tokens, int counter);           //function to delete the number of character from the code vector that was used to generate the token

	void build_tokens(vector<char> code, vector<TOKENS>& tokens);                          //function that will iterate through the code vector looking for tokens

	void load_code(vector<char> code, vector<TOKENS>& tokens);                             //function to read from the 'code.txt' file which holds the tokens to pass to the scanner

	void insert_symbol_table(vector<TOKENS>& tokens);                                      //insert into symbol table function
	
	
	void initial();                                                                       //function that will call the build function, may be removed in the final compiler build
																						  //----------------------------------------//


};
#endif