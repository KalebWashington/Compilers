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
#include "Symboltable.h"

using namespace std;

class Parser
{
private:
	vector <char> parsInCode;
	
public:
	Parser::Parser(vector <char> code) 
	{
		cout << "this is size of code from parsConstruct: " << code.size() << endl;
		parsInCode = code;
	}

void Parser::testOutput()
	{
	
		cout << "this is size of code from parsTest: " << parsInCode.size() << endl;

		/*
		ofstream textout("output2.txt", ios::out);
		textout.write((const char*)&parsInCode[0], parsInCode.size()-1);
		textout.close();
		*/
	}
};


#endif