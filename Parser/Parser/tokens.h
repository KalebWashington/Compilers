#ifndef TOKENS_H
#define TOKENS_H
#include <iostream>


typedef enum {
		EoLToken = 1,			//;           |P
		AddToken = 2,			// +	\)
		SubToken = 3,			// -	)
		MultToken = 4,			// *	TD
		DivToken = 5,			// /	_^_
		IncrToken = 6,			// ++	-(
		DecrToken = 7,			// --	-)
		AssignToken = 8,		// ==	--
		LessToken = 9,			// <	<L
		LessThanOrEqToken = 10,	// <=	<E
		GreaterToken = 11,	// >	>W
		GreaterThanOrEqToken = 12,	// >=	>G
		EqToken = 13,	// =	<>
		NegateToken = 14,	// !	// =* 
		AndToken = 15,	// &&	*N
		OrToken = 16,	// ||	/B/
		TrueToken = 17,	// True	^G
		FalseToken = 18,	// False	^NG
		HexToken = 19,	// 0x	XO
		CharLitToken = 20,	// '	[]
		StringLitToken = 21,	// ''	[[]]
		StringEscToken = 22,	// \	\M
		VoidDecToken = 23,	// void	BRWNS
		BoolDecToken = 24,	// bool	COIN
		IntDecToken = 25,	// int	CHAINS
		CharDecToken = 26,	// char	GOON
		RealDecToken = 27,	// real	BB
		StringDecToken = 28,	// string	CLEATS
		NameToken = 29,	// <id>	<id>
		IntToken = 30,	// 4	// 5
		RealToken = 31,	// 4.1	// 4.2
		LParenToken = 32,	// (	#L#
		RParenToken = 33,	// )	#R#
		SeperatorToken = 34,	// ,	^
		ArrayDefToken = 35,	// []	][
		PointerDefToken = 36,	// *variable	~>
		DerefToken = 37,	// *variable	KO
		SingleLineCommentToken = 38,	// //	@
		LMultiLineCommentToken = 39,	// /*	/@
		RMultiLineCommentToken = 40,	// */	@/
		LBlockToken = 41,	// {	---|
		RBlockToken = 42,	// }	|---
		IfToken = 43,	// if 	PC
		ElseToken = 44,	// else	AUD
		SwitchToken = 45,	// switch	MOTION
		CaseToken = 46,	// case	SUB
		WhileToken = 47,	// while	REV
		ForToken = 48,	// for 	GOLF
		InputIntToken = 49,	// 	PR CHAINS
		InputCharToken = 50,	//	PR GOON
		InputRealToken = 51,	//	PR BB
		InputStringToken = 52,	//	PR CLEATS
		InputBoolToken = 53,	//	PR COIN
		PrintIntToken = 54,	//	PUNT CHAINS
		PrintCharToken = 55,	//	PUNT GOON
		PrintRealToken = 56,	//	PUNT BB
		PrintStringToken = 57,	//	PUNT CLEATS
		PrintBoolToken = 58,	//	PUNT COIN
		ErrorToken = 59,	//parse error
		FetchToken = 60,           //-----         ----
	} tokens_enum;
#endif