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

using namespace std;





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
	register_tokens();//refer to mapping


	cout << tokens.at(2).token_name;



	switch (tokens[tokens.at(0).token_name])
	{
	case FunctionDeclarationToken:
		functionDeclarationToken();
		break;
	case IfToken:
		ifToken();
		break;
		//case audtoken;
		//	break;
	case ForToken:
		forToken();
		break;
	case WhileToken:
		whileToken();
		break;
	case DoWhileToken:
		doWhileToken();
		break;
	case EoLToken:
		eoLToken();
		break;
	case LBlockToken:
		lBlockToken();
		break;
	case RBlockToken:
		rBlockToken();
		break;
		/*case PointerDefToken:
		break;*/
		/*case DerefToken:
		break;*/
	case OrToken:
		orToken();
		break;
	case AndToken:
		andToken();
		break;
	case EquateToken:
		equateToken();
		break;
	case AddToken:
		addToken();
		break;
	case SubToken:
		subToken();
		break;
	case MultToken:
		multToken();
		break;
	case DivToken:
		divToken();
		break;
	case ModToken:
		modToken();
		break;
	case IncrementToken:
		incrementToken();
		break;
	case DecrementToken:
		decrementToken();
		break;
	case NegateToken:
		negateToke();
		break;
	case LParenToken:
		lParenToken();
		break;
	case RParenToken:
		rParenToken();
		break;
	case SeperatorToken:
		seperatorToken();
		break;
	case LessToken:
		lessToken();
		break;
	case GreaterToken:
		greaterToken();
		break;
	case LessThanOrEqToken:
		lessThanOrEqToken();
		break;
	case GreaterThanOrEqToken:
		greaterThanOrEqToken();
		break;
	case ArrayDefToken:
		arrayDefToken();
		break;
	case TrueToken:
		trueToken();
		break;
	case FalseToken:
		falseToken();
		break;
	case CharLitToken:
		charLitToken();
		break;
	case RealToken:
		realToken();
		break;
	case BoolDecToken:
		boolDecToken();
		break;
	case VoidDecToken:
		voidDecToken();
		break;
	case HexToken:
		hexToken();
		break;
	case StringDecToken:
		stringDecToken();
		break;
	case NewLineToken:
		newLineToken();
		break;
	case IntDecToken:
		intDecToken();
		break;
	default:
		break;
	}
}
//bool PlayToken()
//{
//
//	return false;
//}
bool Parser::lBlockToken()
{

	return false;
}
bool Parser::rBlockToken()
{

	return false;
}
bool Parser::whileToken()
{

	return false;
}
bool Parser::forToken()
{
	return false;
}

bool Parser::functionDeclarationToken()
{
	return false;
}
bool Parser::doWhileToken()
{

	return false;
}
bool Parser::eoLToken()
{

	return false;
}
bool Parser::orToken()
{

	return false;
}
bool Parser::andToken()
{

	return false;
}
bool Parser::equateToken()
{

	return false;
}

bool Parser::addToken()
{
	return false;
}
bool Parser::subToken()
{
	return false;
}
bool Parser::multToken()
{

	return false;
}
bool Parser::divToken()
{
	return false;
}
bool Parser::modToken()
{

	return false;
}
bool Parser::incrementToken()
{

	return false;
}
bool Parser::ifToken()
{
	return false;
}
bool Parser::decrementToken()
{
	return false;
}
bool Parser::negateToke()
{
	return false;
}
bool Parser::lParenToken()
{
	return false;
}
bool Parser::rParenToken()
{
	return false;
}
bool Parser::seperatorToken()
{
	return false;
}
bool Parser::lessToken()
{

	return false;
}
bool Parser::greaterToken()
{
	return false;
}
bool Parser::lessThanOrEqToken()
{

	return false;
}
bool Parser::greaterThanOrEqToken()
{
	return false;
}
bool Parser::arrayDefToken()
{

	return false;
}
bool Parser::trueToken()
{
	return false;
}
bool Parser::falseToken()
{
	return false;
}
bool Parser::charLitToken()
{

	return false;
}
bool Parser::realToken()
{
	return false;
}
bool Parser::boolDecToken()
{

	return false;
}
bool Parser::voidDecToken()
{

	return false;
}
bool Parser::hexToken()
{
	return false;
}
bool Parser::stringDecToken()
{

	return false;
}
bool Parser::newLineToken()
{

	return false;
}
bool Parser::intDecToken()
{

	return false;
}

