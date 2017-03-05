#ifndef TOKENS_H
#define TOKENS_H
#include <map>
#include <string>
#include <iostream>
using namespace std;

enum Token {
	EoLToken,				//;     |P
	AddToken,				// +	\)
	SubToken,				// -	)
	MultToken,				// *	TD
	DivToken,				// /	_^_
	IncrToken,				// ++	-(
	DecrToken,				// --	-)
	AssignToken,			// ==	--
	LessToken,				// <	<L
	LessThanOrEqToken,		// <=	<E
	GreaterToken,			// >	>W
	GreaterThanOrEqToken,	// >=	>G
	EqToken,				// =	<>
	NegateToken,			// !	=* 
	AndToken,				// &&	*N
	OrToken,				// ||	/B/
	TrueToken,				// True	^G
	FalseToken,				// False^NG
	HexToken,				// 0x	XO
	CharLitToken,			// '	[]
	StringLitToken,			// ''	[[]]
	StringEscToken,			// \	\M
	VoidDecToken,			// void	BRWNS
	BoolDecToken,			// bool	COIN
	IntDecToken,			// int	CHAINS
	CharDecToken,			// char	GOON
	RealDecToken,			// real	BB
	StringDecToken,			// string	CLEATS
	NameToken,				// <id>	<id>
	IntToken,				// 4	// 5
	RealToken,				// 4.1	// 4.2
	LParenToken,			// (	#L#
	RParenToken,			// )	#R#
	SeperatorToken,			// ,	^
	ArrayDefToken,			// []	][
	PointerDefToken,		// *variable	~>
	DerefToken,				// *variable	KO
	SingleLineCommentToken,	// //	@
	LMultiLineCommentToken,	// /*	/@
	RMultiLineCommentToken,	// */	@/
	LBlockToken,			// {	---|
	RBlockToken,			// }	|---
	IfToken,				// if 	PC
	ElseToken,				// else	AUD
	SwitchToken,			// switch	MOTION
	CaseToken,				// case	SUB
	WhileToken,				// while	REV
	ForToken,				// for 	GOLF
	InputIntToken,			// 	PR CHAINS
	InputCharToken,			//	PR GOON
	InputRealToken,			//	PR BB
	InputStringToken,		//	PR CLEATS
	InputBoolToken,			//	PR COIN
	PrintIntToken,			//	PUNT CHAINS
	PrintCharToken,			//	PUNT GOON
	PrintRealToken,			//	PUNT BB
	PrintStringToken,		//	PUNT CLEATS
	PrintBoolToken,			//	PUNT COIN
	ErrorToken,				//parse error
	FetchToken,
	FunctionDeclarationToken,
	DoWhileToken,
	EquateToken,
	ModToken,
	IncrementToken,
	DecrementToken,
	NewLineToken,
	DefaultToken,
	IdToken,
	BreakToken,
	DoToken,
	LessOrEqualToken,
	GreaterOrEqualToken,
	AddressOfToken,
	SeparatorToken

	//Function Call
	//-----         ------
};

typedef struct {
	Token token;
	std::string value;
} TokenInfo;

std::string lexeme(enum Token);
std::ostream& operator<<(std::ostream& os, enum Token);
std::ostream& operator<<(std::ostream& os, TokenInfo token);

std::map<string, Token> tokens;

void register_tokens()
{
	tokens["EoLToken"] = EoLToken;
	tokens["AddToken"] = AddToken;
	tokens["SubToken"] = SubToken;
	tokens["MultToken"] = MultToken;
	tokens["DivToken"] = DivToken;
	tokens["IncrToken"] = IncrToken;
	tokens["DecrToken"] = DecrToken;
	tokens["AssignToken"] = AssignToken;
	tokens["LessToken"] = LessToken;
	tokens["LessThanOrEqToken"] = LessThanOrEqToken;
	tokens["GreaterToken"] = GreaterToken;
	tokens["GreaterThanOrEqToken"] = GreaterThanOrEqToken;
	tokens["EqToken"] = EqToken;
	tokens["NegateToken"] = NegateToken;
	tokens["AndToken"] = AndToken;
	tokens["OrToken"] = OrToken;
	tokens["TrueToken"] = TrueToken;
	tokens["FalseToken"] = FalseToken;
	tokens["HexToken"] = HexToken;
	tokens["CharLitToken"] = CharLitToken;
	tokens["StringLitToken"] = StringLitToken;
	tokens["StringEscToken"] = StringEscToken;
	tokens["VoidDecToken"] = VoidDecToken;
	tokens["BoolDecToken"] = BoolDecToken;
	tokens["IntDecToken"] = IntDecToken;
	tokens["CharDecToken"] = CharDecToken;
	tokens["RealDecToken"] = RealDecToken;
	tokens["StringDecToken"] = StringDecToken;
	tokens["NameToken"] = NameToken;
	tokens["IntToken"] = IntToken;
	tokens["RealToken"] = RealToken;
	tokens["LParenToken"] = LParenToken;
	tokens["RParenToken"] = RParenToken;
	tokens["SeperatorToken"] = SeperatorToken;
	tokens["ArrayDefToken"] = ArrayDefToken;
	tokens["PointerDefToken"] = PointerDefToken;
	tokens["DerefToken"] = DerefToken;
	tokens["SingleLineCommentToken"] = SingleLineCommentToken;
	tokens["LMultiLineCommentToken"] = LMultiLineCommentToken;
	tokens["RMultiLineCommentToken"] = RMultiLineCommentToken;
	tokens["LBlockToken"] = LBlockToken;
	tokens["RBlockToken"] = RBlockToken;
	tokens["IfToken"] = IfToken;
	tokens["ElseToken"] = ElseToken;
	tokens["SwitchToken"] = SwitchToken;
	tokens["CaseToken"] = CaseToken;
	tokens["WhileToken"] = WhileToken;
	tokens["ForToken"] = ForToken;
	tokens["InputIntToken"] = InputIntToken;
	tokens["InputCharToken"] = InputCharToken;
	tokens["InputRealToken"] = InputRealToken;
	tokens["InputStringToken"] = InputStringToken;
	tokens["InputBoolToken"] = InputBoolToken;
	tokens["PrintIntToken"] = PrintIntToken;
	tokens["PrintCharToken"] = PrintCharToken;
	tokens["PrintRealToken"] = PrintRealToken;
	tokens["PrintStringToken"] = PrintStringToken;
	tokens["PrintBoolToken"] = PrintBoolToken;
	tokens["ErrorToken"] = ErrorToken;
	tokens["FetchToken"] = FetchToken;
	tokens["FunctionDeclarationToken"] = FunctionDeclarationToken;
	tokens["DoWhileToken"] = DoWhileToken;
	tokens["EquateToken"] = EquateToken;
	tokens["ModToken"] = ModToken;
	tokens["IncrementToken"] = IncrementToken;
	tokens["DecrementToken"] = DecrementToken;
	tokens["NewLineToken"] = NewLineToken;
}
#endif