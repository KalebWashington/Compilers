


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
private:
	Scanner s;					    //Communicates with the scanner to get next token
	Symbol table;					//Communicates with the symbol table to check variables being stored

	TokenInfo currentToken;			//Displays current token when checking syntax
	TokenInfo getNextToken();		//Gets the next token when checking sentence syntax
public:


	struct TOKENS
	{
		string token_name;
	};


	struct CHARS
	{
		char values;
	};

	//Bool functions for the Parser, returns false if match isn't equal to current token
	bool Match(enum token_name t);
	bool declarations(size_t&);
	bool declarationList();
	bool variableDeclaration();
	bool proto();
	bool lhs();
	bool functionDeclaration();
	bool functionHeader();
	bool arrayDeclaration();
	bool arraylhs();
	bool arrayStatement();
	bool rhs();
	bool blockStatement();
	bool statements();
	bool statement();
	bool prStatement();
	bool prChains();
	bool prAli();
	bool prGoon();
	bool prBB();
	bool prCleats();
	bool puntStatement();
	bool puntChains();
	bool puntAli();
	bool puntGoon();
	bool puntBB();
	bool loop();
	bool forLoop();
	bool whileLoop();
	bool doLoop();
	bool pcBlock();
	bool pcStatement();
	bool audStatement();
	bool parameters();
	bool parameterList();
	bool parameter();


	bool expr6(enum Type);
	bool expr5(enum Type);
	bool expr4(enum Type);
	bool expr3(enum Type);
	bool expr2(enum Type);
	bool expr1(enum Type);
	bool expr0(enum Type);
	bool expr(enum Type);

	bool comparator();
	bool singleComparator();
	bool dualcomparator();
	bool functioncall();
	bool argumentlist();
	bool argument();
	bool returnType();
	bool type();
	bool Literal();
	//bool digits();
	bool letter();
	bool escapedCharacters();
	bool letters();
	bool octDigits();
	bool octDigit();
	bool hexLiteral();
	bool id();
	bool pointer();
	bool idName();
	bool restofid();
	bool lowerCase();
	bool digit();
	bool upperCase();

	//All first of functions-------------------------------------------------//
	bool lBlockToken();
	bool rBlockToken();
	bool whileToken();
	bool forToken();
	bool functionDeclarationToken();
	bool doWhileToken();
	bool eoLToken();
	bool orToken();
	bool andToken();
	bool equateToken();
	bool addToken();
	bool subToken();
	bool multToken();
	bool divToken();
	bool modToken();
	bool incrementToken();
	bool ifToken();
	bool decrementToken();
	bool negateToke();
	bool lParenToken();
	bool rParenToken();
	bool seperatorToken();
	bool lessToken();
	bool greaterToken();
	bool lessThanOrEqToken();
	bool greaterThanOrEqToken();
	bool arrayDefToken();
	bool trueToken();
	bool falseToken();
	bool charLitToken();
	bool realToken();
	bool boolDecToken();
	bool voidDecToken();
	bool hexToken();
	bool stringDecToken();
	bool newLineToken();
	bool intDecToken();
	//-----------------------------------------------//






	//PROTOTYPES//
	void match(vector<Scanner::TOKENS>& tokens);

	void in(vector<TOKENS>& tokens);

};
enum Type { TypeCHAINS = 0, TypeCOIN, TypeGOON, TypeBB, TypeCLEATS };

#endif

