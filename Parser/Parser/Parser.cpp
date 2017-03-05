
#include "Symbol.h" //including SymbolTable functions
#include "Scanner.h" //including Scanner functions
#include "Parser.h"
#include "tokens.h"

#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm>




struct TOKENS
{
	string token_name;
};


struct CHARS
{
	char values;
};


Scanner scanner;
Symbol symbol_table;

//vector<Symbol::TABLE> tokens;



void Parser::match(vector<Scanner::TOKENS>& tokens)
{

	
	
	cout << tokens.at(2).token_name;
	
	/*
	tokens_enum tokenin = tokens.at(0).token_name;
	
	switch (tokens)
	{

		case '1' 
	default:
		break;
	}

	*/
}




