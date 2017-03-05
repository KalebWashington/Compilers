


#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Scanner.h"

using namespace std;

class Parser
{
public:
	
	
	struct TOKENS
	{
		string token_name;
	};
	
	
	struct CHARS 
	{
		char values;
	};




	//PROTOTYPES//
	void match(vector<Scanner::TOKENS>& tokens);

	void in(vector<TOKENS>& tokens);

};
enum Type { TypeCHAINS = 0, TypeCOIN, TypeGOON, TypeBB, TypeCLEATS };

#endif


