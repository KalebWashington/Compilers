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
	vector <Scanner::TOKENS> token_to_match_v;
	vector <Scanner::TOKENS> token_to_match_v2;
	vector <Scanner::TOKENS> token_to_match_v3;
	vector <Scanner::TOKENS> token_to_match_v4;
	vector <Scanner::TOKENS> token_to_match_v5;
	vector <Scanner::TOKENS> token_to_match_v6;
	vector <Scanner::TOKENS> token_to_match_v7;
	vector <Scanner::TOKENS> token_to_match_v8;
	Scanner::TOKENS token_to_match;
	Scanner::TOKENS token_to_match2;
	Scanner::TOKENS token_to_match3;
	Scanner::TOKENS token_to_match4;
	Scanner::TOKENS token_to_match5;
	Scanner::TOKENS token_to_match6;
	Scanner::TOKENS token_to_match7;
	Scanner::TOKENS token_to_match8;
	vector <Scanner::TOKENS> tokens_f_parser;
	Scanner::TOKENS token_to_match;
	int parsoutcodectr;
	Scanner scannerobj;

public:

	Parser::Parser(vector <char> code)
	{
		parsInCode = code;
		parsoutcodectr = 0;
	}

	bool Parser::match(Scanner::TOKENS token_to_match, vector <Scanner::TOKENS> parsInToken)
	{
		if (tokens_f_parser.at(0).token_name == token_to_match.token_name)
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
		return tokens_f_parser;
	}

	void Parser::emit(vector <char> emit_code)
	{

		for (int i = 0; i < emit_code.size(); i++)
		{
			parsOutCode.push_back(emit_code.at(i));
		}

		emit_code.erase(emit_code.begin(), emit_code.end());
	}

	bool declarations()
		bool declList();
	bool funcDeclaration();
	bool funcHeader();
	bool varDeclaration();
	bool proto();
	bool lhs();
	bool rhs();
	bool rhsEnd();

	bool arrDeclaration();          // Declaration of array
	bool arrayLhs();                      // Type array and size
	bool arrStatement();

	void Parser::blockStatement() {
		sum = 0;
		// BlockStatement calls statement or LBlock<statementRBlock
		token_to_match.token_name = "LBlockToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser)) {
			cout << "in LBlockToken function before emit\n";
			token_to_match.token_name = "RBlockToken";
			token_to_match_v.push_back(token_to_match);
			while (!match(token_to_match, tokens_f_parser)) {
				sum += Statements();								//Read in multiple statements (lines)
				token_to_match.token_name = "EOLToken";
				token_to_match_v.push_back(token_to_match);
				match(toke_to_match, tokens_f_parser);
			}
		}
		else {
			Statement();											//Call statement to read one line
		}
	}

	bool Parser::statements() {
		if (statement()) {											//Call statement to read one line
			return true;
		}
	}
		else if (statement()) {										//Call statement to read one line
			if (statements()) {										//Read in multiple statements (lines)
				return true;
			}
		}
		else {
			return false;											//Nothing else
		}
}
	
bool Parser::statement() {
	if (prStatement()) {
		return true;
	}
	else if (puntStatement) {
		return true;
	}
	else if (funcDeclaration()) {
		return true;
	}
	else if (varDeclaration()) {
		return true;
	}
	else if (arrDeclaration()) {
		return true;
	}
	else if (expr()) {
		return true;
	}
	else if (loop()) {
		return true;
	}
	else if (condStatement) {
		return true;
	}
	token_to_match.token_name = "LBlockToken";
	token_to_match_v.push_back(token_to_match);
	else if (match(token_to_match, tokens_f_parser)) {
		cout << "in LBlockToken function before emit\n";
	}

	return false;
}


/*
	void Parser::PC_Block() {
		token_to_match.token_name = "IfToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser))
		{
			cout << "in If token function before emit\n";
			token_to_match.token_name = "LParenToken";
			token_to_match_v.push_back(token_to_match);
			tokens_f_parser = getToken(tokens_f_parser);
			if (match(token_to_match, tokens_f_parser))
			{
				cout << "in LParen token function before emit\n";
				emit_code.push_back('i');
				emit_code.push_back('f');
				emit(emit_code);
			}
		}
	}
*/
	bool Parser::expr0()
	{
		token_to_match.token_name = "LParenToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser))
		{
			cout << "in LParentoken function before emit\n";
			//expr9
			token_to_match.token_name = "RParenToken";
			token_to_match_v.push_back(token_to_match);
			if (match(token_to_match, tokens_f_parser))
			{
				cout << "in RParentoken function before emit\n";
			}
		}
		/*
		else if{
			//function call
		}
		else if{
		//id
		}
		else if{
		//literal
		}
		else 
		//error
		*/
	}

	void Parser::expr()
	{
		expr6();
	}

	bool Parser::expr4()
	{
		token_to_match.token_name = "LParenToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser))
		{
			cout << "in LParentoken function before emit\n";
			//expr9
			token_to_match.token_name = "RParenToken";
			token_to_match_v.push_back(token_to_match);
			if (match(token_to_match, tokens_f_parser))
			{
				cout << "in RParentoken function before emit\n";
			}
		}
	}

	bool Parser::expr4()
	{
		token_to_match.token_name = "LParenToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser))
		{
			cout << "in LParentoken function before emit\n";
			//expr9
			token_to_match.token_name = "RParenToken";
			token_to_match_v.push_back(token_to_match);
			if (match(token_to_match, tokens_f_parser))
			{
				cout << "in RParentoken function before emit\n";
			}
		}
	}

	void Parser::expr6()
	{
		token_to_match.token_name = "LParenToken";
		token_to_match_v.push_back(token_to_match);

		else if (match(token_to_match, tokens_f_parser))
		{
			token_to_match.token_name = "OrToken";
			token_to_match_v.push_back(token_to_match);
			if (match(token_to_match, tokens_f_parser))
			{
				if ()
			}
		}
	}
		
	void Parser::PC_Block() {
		token_to_match.token_name = "IfToken";
		token_to_match_v.push_back(token_to_match);
		if (match(token_to_match, tokens_f_parser))
		{
			cout << "in If token function before emit\n";
			//if (expr())
			//}
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

		tokens_f_parser = (scannerobj.build_tokens(tokens_f_parser));

		cout << "this is tokens_f_parser" << tokens_f_parser.at(0).token_name << endl;

		while (tokens_f_parser.at(0).token_name != "DoneToken")
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
				PC_Block();
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