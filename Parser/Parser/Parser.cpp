
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
	case playtoken:
		break;
	case iftoken:
		break;
	case audtoken;
		break;
	case ForToken:
		break;
	case WhileToken:
		break;
	case DoWhileToken:
		break;
	case EoLToken:
		break;
	case LBlockToken:
		break;
	case RBlockToken:
		break;
	case PointerDefToken:
		break;
	case DerefToken:
		break;
	case OrToken:
		break;
	case AndToken:
		break;
	case equateToken:
		break;
	case AddToken:
		break;
	case SubToken:
		break;
	case MultToken:
		break;
	case DivToken:
		break;
	case ModToken:
		break;
	case incrementToken:
		break;
	case decrementToken:
		break;
	case NegateToken:
		break;
	case LParenToken:
		break;
	case RParenToken:
		break;
	case SeperatorToken:
		break;
	case LessToken:
		break;
	case GreaterToken:
		break;
	case LessThanOrEqToken:
		break;
	case GreaterThanOrEqToken:
		break;
	case ArrayDefToken:
		break;
	case TrueToken:
		break;
	case FalseToken:
		break;
	case CharLitToken:
		break;
	case RealToken:
		break;
	case BoolDecToken:
		break;
	case VoidDecToken:
		break;
	case HexToken:
		break;
	case StringLitToken:
		break;
	case newLineToken:
		break;
	case IntToken:
		break;
	default:
		break;
	}
}




