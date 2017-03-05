#include <iostream>
#include "tokens.h"

std::string lexeme(enum Token token)
{
	if (token == EoLToken) return "|P";
	else if (token == AddToken) return "\)";
	else if (token == SubToken) return ")";
	else if (token == MultToken) return "TD";
	else if (token == DivToken) return "_^_";
	else if (token == ModToken) return "$";
	else if (token == IncrToken) return "-(";
	else if (token == DecrToken) return "-)";
	else if (token == AssignToken) return "--";
	else if (token == LessToken) return "<L";
	else if (token == GreaterToken) return ">W";
	else if (token == EqToken) return "<>";
	else if (token == NegateToken) return "=*";
	else if (token == AndToken) return "*N";
	else if (token == OrToken) return "/B/";
	else if (token == TrueToken) return "^G";
	else if (token == FalseToken) return "^NG";
	else if (token == HexToken) return "XO";
	else if (token == CharLitToken) return "[[]]";//this is going to be tricky
	else if (token == StringLitToken) return "[]";//this is going to be tricky
	else if (token == StringEscToken) return "\M";
	else if (token == VoidDecToken) return " BRWNS";
	else if (token == BoolDecToken) return "COIN";
	else if (token == IntDecToken) return "CHAINS";
	else if (token == CharDecToken) return "GOON";
	else if (token == RealDecToken) return "BB";
	else if (token == StringDecToken) return "CLEATS";
	else if (token == IdToken) return " IDToken";
	//else if (token == VoidToken) return " ";
	//else if (token == BoolToken) return " ";
	else if (token == IntToken) return "IntToken";
	//else if (token == CharToken) return "";
	//else if (token == RealToken) return "";
	//else if (token == StringToken) return "";
	else if (token == LParenToken) return "#L#";
	else if (token == RParenToken) return "#R#";
	else if (token == SeperatorToken) return "^";
	else if (token == ArrayDefToken) return "][";//this is going to be tricky
	else if (token == PointerDefToken) return "~>";
	else if (token == DerefToken) return "KO";
	else if (token == SingleLineCommentToken) return "@";
	else if (token == LMultiLineCommentToken) return "/@";
	else if (token == RMultiLineCommentToken) return "@/";
	else if (token == LBlockToken) return "%--|";
	else if (token == RBlockToken) return "|--%";
	else if (token == IfToken) return "PC";
	else if (token == ElseToken) return "AUD";
	else if (token == SwitchToken) return "MOTION";
	else if (token == CaseToken) return "SUB";
	else if (token == DefaultToken) return "BANDWAGON";
	else if (token == BreakToken) return "ROMO";
	else if (token == WhileToken) return "REV";
	else if (token == ForToken) return "GOLF";
	else if (token == DoToken) return "CHL";
	else if (token == InputIntToken) return "PR CHAINS";
	else if (token == InputCharToken) return "PR GOON";
	else if (token == InputRealToken) return "PR BB";
	else if (token == InputStringToken) return "PR CLEATS";
	else if (token == InputBoolToken) return "PR COIN";
	else if (token == PrintIntToken) return " PUNT CHAINS";
	else if (token == PrintCharToken) return "PUNT GOON";
	else if (token == PrintRealToken) return "PUNT BB";
	else if (token == PrintStringToken) return "PUNT CLEATS";
	else if (token == PrintBoolToken) return "PUNT COIN";
	else if (token == LessOrEqualToken) return "<E";
	else if (token == GreaterOrEqualToken) return ">G";
	//else if (token == NegativeToken) return ""; //I don't think we clarified this
	else if (token == AddressOfToken) return "$'";
	else if (token == ErrorToken) return "ErrorToken";
	else if (token == NewLineToken) return "|P";
	return "Error";
}

std::ostream& operator<<(std::ostream& os, enum Token token)
{
	if (token == EoLToken) return os << "EoLToken";
	else if (token == AddToken) return os << "AddToken";
	else if (token == SubToken) return os << "SubToken";
	else if (token == MultToken) return os << "MultToken";
	else if (token == DivToken) return os << "DivToken";
	else if (token == ModToken) return os << "ModToken";
	else if (token == IncrToken) return os << "IncrToken";
	else if (token == DecrToken) return os << "DecrToken";
	else if (token == AssignToken) return os << "AssignToken";
	else if (token == LessToken) return os << "LessToken";
	else if (token == GreaterToken) return os << "GreaterToken";
	else if (token == EqToken) return os << "EqToken";
	else if (token == NegateToken) return os << "NegateToken";
	else if (token == AndToken) return os << "AndToken";
	else if (token == OrToken) return os << "OrToken";
	else if (token == TrueToken) return os << "TrueToken";
	else if (token == FalseToken) return os << "FalseToken";
	else if (token == HexToken) return os << "HexToken";
	else if (token == CharLitToken) return os << "CharLitToken";
	else if (token == StringLitToken) return os << "StringLitToken";
	else if (token == StringEscToken) return os << "StringEscToken";
	else if (token == VoidDecToken) return os << "VoidDecToken";
	else if (token == BoolDecToken) return os << "BoolDecToken";
	else if (token == IntDecToken) return os << "IntDecToken";
	else if (token == CharDecToken) return os << "CharDecToken";
	else if (token == RealDecToken) return os << "RealDecToken";
	else if (token == StringDecToken) return os << "StringDecToken";
	//	else if (token == IdToken) return os << "IdToken";
	//	else if (token == VoidToken) return os << "VoidToken";
	//	else if (token == BoolToken) return os << "BoolToken";
	//	else if (token == IntToken) return os << "IntToken";
	//	else if (token == CharToken) return os << "CharToken";
	//	else if (token == RealToken) return os << "RealToken";
	//	else if (token == StringToken) return os << "StringToken";
	else if (token == LParenToken) return os << "LParenToken";
	else if (token == RParenToken) return os << "RParenToken";
	else if (token == SeparatorToken) return os << "SeperatorToken";
	else if (token == ArrayDefToken) return os << "ArrayDefToken";
	else if (token == PointerDefToken) return os << "PointerDefToken";
	else if (token == DerefToken) return os << "DerefToken";
	else if (token == SingleLineCommentToken) return os << "SingleLineCommentToken";
	else if (token == LMultiLineCommentToken) return os << "LMultiLineCommentToken";
	else if (token == RMultiLineCommentToken) return os << "RMultiLineCommentToken";
	else if (token == LBlockToken) return os << "LBlockToken";
	else if (token == RBlockToken) return os << "RBlockToken";
	else if (token == IfToken) return os << "IfToken";
	else if (token == ElseToken) return os << "ElseToken";
	else if (token == SwitchToken) return os << "SwitchToken";
	else if (token == CaseToken) return os << "CaseToken";
	else if (token == DefaultToken) return os << "DefaultToken";
	else if (token == BreakToken) return os << "BreakToken";
	else if (token == WhileToken) return os << "WhileToken";
	else if (token == ForToken) return os << "ForToken";
	else if (token == DoToken) return os << "DoToken";
	else if (token == InputIntToken) return os << "InputIntToken";
	else if (token == InputCharToken) return os << "InputCharToken";
	else if (token == InputRealToken) return os << "InputRealToken";
	else if (token == InputStringToken) return os << "InputStringToken";
	else if (token == InputBoolToken) return os << "InputBoolToken";
	else if (token == PrintIntToken) return os << "PrintIntToken";
	else if (token == PrintCharToken) return os << "PrintCharToken";
	else if (token == PrintRealToken) return os << "PrintRealToken";
	else if (token == PrintStringToken) return os << "PrintStringToken";
	else if (token == PrintBoolToken) return os << "PrintBoolToken";
	else if (token == LessOrEqualToken) return os << "LessOrEqualToken";
	else if (token == GreaterOrEqualToken) return os << "GreaterOrEqualToken";
	//else if (token == NegativeToken) return os << "NegativeToken"; //I don't think we clarified this
	else if (token == AddressOfToken) return os << "AddressOfToken";
	else if (token == ErrorToken) return os << "ErrorToken";
	else if (token == NewLineToken) return os << "NewLineToken";
	return os << "Error";
}

std::ostream& operator<<(std::ostream& os, TokenInfo token)
{
	return os << "{ token: " << token.token << " lex: " << token.value.c_str() << " }";
}
