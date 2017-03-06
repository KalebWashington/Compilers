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
private: 
	
public:
	struct TOKENS                                                                         //TOKENS struct; used to create a vector of this type that will hold the tokens generated.
	{
		string token_name;  
                                                              //string to hold the name of the generated token
		//string value = NULL;
	};

	vector<char> code;

	//PROTOTYPES//
	void print_tokens(vector<TOKENS>& tokens);                                             //function to print tokens generated. this will more than likely be removed as it was used for testing.

	vector <Scanner::TOKENS> build_tokens(vector<TOKENS>& tokens);                          //function that will iterate through the code vector looking for tokens

	void insert_symbol_table(vector<TOKENS>& tokens);                                      //insert into symbol table function

	string sendIDname()
	{

	}

};
#endif#
