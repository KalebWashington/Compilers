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
#include "scanner.h"
#include "Symboltable.h"

using namespace std;

class Parser
{
private:
		
	vector <char> parsInCode;
	Scanner scannerobj;

public:

	struct TOKENS                                                                         
	{
		string token_name;                                                                
	};

	Parser::Parser(vector <char> code) 
	{
		cout << "this is size of code from parsConstruct: " << code.size() << endl;
		cout << "this is size of code from parsConstruct: " << parsInCode.size() << endl;

		parsInCode = code;

		cout << "this is size of code from parsConstruct: " << code.size() << endl;
		cout << "this is size of parsInCode from parsConstruct: " << parsInCode.size() << endl;

	}

void Parser::testOutput()
	{
		cout << "this is size of parsInCode from parsTest: " << parsInCode.size() << endl;

		ofstream textout("output2.txt", ios::out);
		textout.write((const char*)&parsInCode[0], parsInCode.size()-1);
		textout.close();
	}

/*
vector <char> Parser::scannerCharVectorFill()
{
	return parsInCode;
}
*/

void Parser::scannerRun()
	{
		vector <Scanner::TOKENS> tokens_f_parser;

		scannerobj.grabCharVector(parsInCode);

		tokens_f_parser=(scannerobj.build_tokens(tokens_f_parser));
		
		while(tokens_f_parser.at(0).token_name != "DoneToken")
		{
			if (tokens_f_parser.at(0).token_name == "IntDecToken")
			{
				cout << "Success! IntDecToken If Statement from Parser\n";
				//call match function
			}
			//tokens_f_parser.pop_back();
			tokens_f_parser = (scannerobj.Scanner::build_tokens(tokens_f_parser));
		}

		cout << "Success! DoneToken from Parser\n";

	}
};

/*

*/

#endif