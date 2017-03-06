


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
	//All first of functions-------------------------------------------------//


	//Bool functions for the Parser, returns false if match isn't equal to current token
	bool Match(enum Token t);
	bool declarations(size_t&);
	bool declarationList();
	bool functionDeclaration(enum Type, size_t&);
	bool functionHeader();
	bool variableDeclaration(enum Type, std::string);
	bool proto();						// HELP
	bool lhs();
	bool rhs(enum Type, std::string);
	bool rhsEnd(enum Type);             // another declaration or end of rhs which includes eol token
	
	//Arrays------------------------------//
	bool arrayDeclaration(enum Type);
	bool arrayLhs(enum Type, std::string);
	bool arrayStatement();
	//Arrays-----------------------------//


	//Statements-------------------------//
	bool blockStatement(size_t&);
	bool statements();
	bool statement(size_t&);
	//Statements------------------------//


	//Input/Output-------------------------//
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
	//Input/Output-------------------------//


	//Loops------------------------------//
	bool loop();
	bool forLoop();
	bool whileLoop();
	bool doLoop();
	//Loops------------------------------//



	//ifStatemtents---------------------//
	bool pcBlock();
	bool pcStatement();
	bool audStatement();
	//ifStatemtents---------------------//



	//Parameters------------------------//
	bool parameters();
	bool parameterList();
	bool parameter();
	//Paremeters------------------------//


	//Expressions-----------------------//
	bool expr6(enum Type);
	bool expr5(enum Type);
	bool expr4(enum Type);
	bool expr3(enum Type);
	bool expr2(enum Type);
	bool expr1(enum Type);
	bool expr0(enum Type);
	bool expr(enum Type);
	//Expressions-----------------------//
	

	//Comparator functions--------------//
	bool comparator();
	bool singleComparator();
	bool dualcomparator();
	//Comparator functions--------------//


	//Fuctions-------------------------//
	bool functioncall();
	bool argumentlist();
	bool argument();
	bool returnType(enum Type&);
	//Fuctions-------------------------//



	
	bool Literal(enum Type&);
	bool type(enum Type&);
	bool BRWNS(enum Type&);
	bool CHAINS(int &);
	bool COIN(enum Type&);
	bool BB(enum Type&);
	bool GOON(enum Type&);
	bool digits();
	bool letter();
	bool escapedCharacters();
	bool letters();
	bool octDigits();
	bool octDigit();
	bool hexLiteral();
	bool id();
	//bool pointer();
	bool idName();
	bool restofid();
	bool lowerCase();
	bool upperCase();
	bool digit();








	//PROTOTYPES//
	void match(vector<Scanner::TOKENS>& tokens);

	void in(vector<TOKENS>& tokens);

};
enum Type { TypeCHAINS = 0, TypeCOIN, TypeGOON, TypeBB, TypeCLEATS };

#endif

