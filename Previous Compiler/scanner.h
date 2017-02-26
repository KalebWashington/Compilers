#ifndef SCANNER_H
#define SCANNER_H

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include "tokens.h"
#include <sstream>

namespace patch {
	template <typename T>
	std::string to_string(T);
}
class Scanner
{

private:
	std::iostream *input;

	int lineNumber;
	char next;
	bool hasErrored;
	TokenInfo currentToken;

	void ReadEscapedCharacter();
	void ParseString();
	void ParseNumber();
	void ConsumeWS();
	void SkipNext();

public:
	Scanner(std::iostream *in)
	{
		input = in;
		lineNumber = 1;
		hasErrored = false;
	}

	bool HasToken();
	bool HasErrored() { return hasErrored; }
	TokenInfo NextToken();
	char GetNext();
	char GetFirst();
};

#endif
