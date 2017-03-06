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
	vector <char> parsOutCode;
	Scanner scannerobj;
	vector <Scanner::TOKENS> tokens_f_parser;


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
		scannerobj.code = parsInCode;

		cout << "size of code in scannerobject: " << scannerobj.code.size() << endl;

		tokens_f_parser=(scannerobj.build_tokens(tokens_f_parser));
		
		cout << "this is tokens_f_parser" << tokens_f_parser.at(0).token_name << endl;

		while(tokens_f_parser.at(0).token_name != "DoneToken")
		{
			if (tokens_f_parser.at(0).token_name == "IntDecToken")
			{
				cout << "Success! IntDecToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "LBlockToken")
			{
				cout << "Success! LBlockToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "RBlockToken")
			{
				cout << "Success! RBlockToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "VoidDecToken")
			{
				cout << "Success! VoidDecToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "IdToken")
			{
				cout << "Success! IdToken If Statement from Parser\n";

				//Check ID in Symbol Table
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "EoLToken")
			{
				cout << "Success! EoLToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "FunDecToken")
			{
				cout << "Success! FunDecToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "LParenToken")
			{
				cout << "Success! LParenToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "RParenToken")
			{
				cout << "Success! RParenToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "MainToken")
			{
				cout << "Success! MainToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "WhiteSpaceToken")
			{
				cout << "Success! MainToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "IntLitToken")
			{
				cout << "Success! IntLitToken If Statement from Parser\n";
				//call match function
			}
			else if (tokens_f_parser.at(0).token_name == "AssignToken")
			{
				cout << "Success! AssignToken If Statement from Parser\n";
				//call match function
			}

			tokens_f_parser.pop_back();
			tokens_f_parser = (scannerobj.Scanner::build_tokens(tokens_f_parser));
			//cin.get();
		}

		cout << "Success! DoneToken from Parser\n";
	}
};

/*

*/

#endif