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
	vector <char> emit_code;
	int parsoutcodectr;
	Scanner scannerobj;
	vector <Scanner::TOKENS> tokens_f_parser;


public:

	struct TOKENS                                                                         
	{
		string token_name;                                                                
	};

	Parser::Parser(vector <char> code) 
	{
		parsInCode = code;
		parsoutcodectr = 0;
	}

	bool Parser::match(string tokenStr, vector <Scanner::TOKENS> parsInToken)
	{
		if (tokens_f_parser.at(0).token_name == tokenStr)
		{
			cout << "return true from match\n";
			return true;
		}
		else
			cout << "return false from match\n";
		return false;
	}

	vector <Scanner::TOKENS> Parser::getToken(vector <Scanner::TOKENS> parsInToken) 
	{
		tokens_f_parser.pop_back();
		cout << "Size of token in get token after pop: " << tokens_f_parser.size() << "\n";
		tokens_f_parser = (scannerobj.Scanner::build_tokens(tokens_f_parser));
		cout << "Size of token in get token after fill: " << tokens_f_parser.size() << "\n";
	}

	void Parser::emit(vector <char> emit_code) 
	{
		
		for (int i = 0; i < emit_code.size(); i++)
		{
			parsOutCode.push_back(emit_code.at(i));
		}
		
		emit_code.erase(emit_code.begin(), emit_code.end());
	}

	void Parser::pcFunc() {
		string tokenStr = "IfToken";
		if (match(tokenStr, tokens_f_parser))
		{
			cout << "in If token function before emit\n";
			string tokenStr = "LParenToken";
			if (match(tokenStr, tokens_f_parser))
			{
				cout << "in LParen token function before emit\n";
				emit_code.push_back('i');
				emit_code.push_back('f');
				emit(emit_code);
			}
		}
	}

	vector <char> Parser::sendCharVector()
	{
		return parsOutCode;
	}

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
				//cout << "Success! MainToken If Statement from Parser\n";
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
			else if (tokens_f_parser.at(0).token_name == "IfToken")
			{
				cout << "Success! IfToken If Statement from Parser\n";
				pcFunc();
			}

			tokens_f_parser.pop_back();
			tokens_f_parser = (scannerobj.Scanner::build_tokens(tokens_f_parser));
		}

		cout << "Success! DoneToken from Parser\n";
	}
};



/*

*/

#endif