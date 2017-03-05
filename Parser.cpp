
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
bool lBlockToken()
{

	return false;
}
bool rBlockToken()
{

	return false;
}
bool whileToken()
{

	return false;
}
bool forToken()
{
	return false;
}

bool functionDeclarationToken()
{
	return false;
}
bool doWhileToken()
{

	return false;
}
bool eoLToken()
{

	return false;
}
bool orToken()
{

	return false;
}
bool andToken()
{

	return false;
}
bool equateToken()
{

	return false;
}

bool addToken()
{
	return false;
}
bool subToken()
{
	return false;
}
bool multToken()
{

	return false;
}
bool divToken()
{
	return false;
}
bool modToken()
{

	return false;
}
bool incrementToken()
{

	return false;
}
bool ifToken()
{
	return false;
}
bool decrementToken()
{
	return false;
}
bool negateToke()
{
	return false;
}
bool lParenToken()
{
	return false;
}
bool rParenToken()
{
	return false;
}
bool seperatorToken()
{
	return false;
}
bool lessToken()
{

	return false;
}
bool greaterToken()
{
	return false;
}
bool lessThanOrEqToken()
{

	return false;
}
bool greaterThanOrEqToken()
{
	return false;
}
bool arrayDefToken()
{

	return false;
}
bool trueToken()
{
	return false;
}
bool falseToken()
{
	return false;
}
bool charLitToken()
{

	return false;
}
bool realToken()
{
	return false;
}
bool boolDecToken()
{

	return false;
}
bool voidDecToken()
{

	return false;
}
bool hexToken()
{
	return false;
}
bool stringDecToken()
{

	return false;
}
bool newLineToken()
{

	return false;
}
bool intDecToken()
{

	return false;
}
