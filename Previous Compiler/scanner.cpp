//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include "scanner.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

template <typename T>
std::string patch::to_string(T var)
{
	std::stringstream ss;
	ss << var;
	return ss.str();
}

char Scanner::GetNext()
{
	*input >> next;
	currentToken.value.push_back(next);
	next = input->peek();
	return next;
}

char Scanner::GetFirst()
{
	ConsumeWS();
	next = input->peek();
	return next;
}

void Scanner::ReadEscapedCharacter()
{
	if (next == '*') {
		//skip escape literal, read in the next character
		*input >> next;
		next = input->peek();

		//read in value
		char escaped = '\0';
		if (next == '*' || next == '$' || next == '^' || next == '\n')
			escaped = next;
		else if (next == '@')
		{
			//read in hex value
			*input >> next; //read in @, as it's not the value we need;
			*input >> std::hex >> escaped;
		}
		else if (next >= '0' && next < '9')
		{
			//read octal
			*input >> std::oct >> escaped;
		}
		else if (next == 'r')
			escaped = '\r';
		else if (next == 'n')
			escaped = '\n';
		else if (next == '?')
			escaped = '\?';
		else if (next == 't')
			escaped = '\t';
		else if (next == 'v')
			escaped = '\v';
		else if (next == 'f')
			escaped = '\f';
		else if (next == 'b')
			escaped = '\b';
		else if (next == 'a')
			escaped = '\a';
		else {
			std::cout << "Tried to read in improper escaped character \'*" << next << "\' on line " << lineNumber << std::endl;
			throw 0;
		}

		//if it's a new line, then continue reading the multiline string
		if (escaped != '\n')
			currentToken.value.push_back(escaped);

		*input >> next;       //old value still on buffer, remove
		next = input->peek(); //set up for next match
	}
}

void Scanner::ParseString()
{
	if (next == '$')
	{
		//read in the $ from input, but discard it because it's not lexically important
		GetNext();
		currentToken.value = "";

		while (next != '$' && next != '\n')
		{
			if (next == '*')
				this->ReadEscapedCharacter();
			else
				GetNext();
		}

		//loop was broken by a newline, 
		if (next == '\n') {
			std::cout << "String wasn't closed, use * at the end of the line for multiline strings. Line: "<< lineNumber << std::endl;
			throw 0;
		}

		currentToken.token = StringLitToken;

		//consume lingering $
		*input >> next;
		next = input->peek();
	}
}

void Scanner::ParseNumber()
{
	//consume all of the digits for an int
	while (isdigit(GetNext()))
		;
	//check to see if it is a real
	if (next != '.')
	{
		//not a real
		currentToken.token = IntToken;
	}
	else {
		//consume the rest of the numbers
		while (isdigit(GetNext()))
			;
		currentToken.token = RealToken;
	}
}

void Scanner::ConsumeWS()
{
	while (isspace(input->peek()))
	{
		if (next == '\n' || next == '\r')
			++lineNumber;
		SkipNext();
	}

}

inline void Scanner::SkipNext()
{
	*input >> std::ws;
	next = input->peek();
}

bool Scanner::HasToken()
{
	ConsumeWS();
	return !input->eof() && !hasErrored;
}

TokenInfo Scanner::NextToken()
{
	currentToken.token = ErrorToken; //This is the default case
	currentToken.value = "";         //Clear previous lexeme

	GetFirst();
	switch (next) 
	{
	case '#':
		currentToken.token = AddToken;
		GetNext();
		break;
	case '_':
		GetNext();
		if(next == '/')
		{
			currentToken.token = SubToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;

	case '<':
		GetNext();
		if(next == '3')
		{
			currentToken.token = MultToken;
			GetNext();
		}
		else if(next == '}')
		{
			GetNext();
			if(next == '<')
			{
				GetNext();
				if(next == '>')
				{
					currentToken.token = LessOrEqualToken;
					GetNext();
				}
			}
			else
			{
				currentToken.token = LessToken;
				GetNext();
			}
		}
		else if(next == '>')
		{
			currentToken.token = EqToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case 'V':
		GetNext();
		if(next == 'V')
		{
			currentToken.token = DivToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;

	case '{':
		GetNext();
		if(next == '}')
		{
			currentToken.token = ModToken;
			GetNext();
		}
		else if(next == '>')
		{
			GetNext();
			if(next == '<')
			{
				GetNext();
				if(next == '>')
				{
					currentToken.token = GreaterOrEqualToken;
					GetNext();
				}
			}
			else
			{
				currentToken.token = GreaterToken;
				GetNext();
			}
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '/':
		GetNext();
		if(next == 'T')
		{
			currentToken.token = IncrToken;
			GetNext();
		}
		else if(next == '|')
		{
			currentToken.token = AssignToken;
			GetNext();
		}
		else if(next == '/')
		{
			currentToken.token = OrToken;
			GetNext();
		}
		else 
			currentToken.token = ErrorToken;
		break;
	case '\\':
		GetNext();
		if(next == 'T')
		{
			currentToken.token = DecrToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case ':':
		GetNext();
		if(next == '3')
		{
			GetNext();
			if(next == '<')
			{
				GetNext();
				if(next == '>')
				{
					currentToken.token = NotEqualToken;
					GetNext();
				}
			}
			else
			{
				currentToken.token = NegateToken;
				GetNext();
			}
		}
		else if(next == ':')
		{
			currentToken.token = SeparatorToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case 'O':
		GetNext();
		if(next == 'O')
		{
			currentToken.token = TrueToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case 'X':
		GetNext();
		if(next == 'X')
		{
			currentToken.token = FalseToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '@':
		GetNext();
		if (next == '=') {
			currentToken.token = LParenToken;
			GetNext();
		}
		else
			currentToken.token = HexToken;
		break;
	case '^':
		currentToken.token = CharLitToken;
		GetNext();
		break;
	case '$':
		this->ParseString();
		break;
	case '+':
		GetNext();
		if(next == '&')
		{
			currentToken.token = PositiveToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '?':
		currentToken.token = BedEndToken;
		GetNext();
		break;
	case '*':
		currentToken.token = StringEscToken;
		GetNext();
		break;
	case '8':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '9':
		this->ParseNumber();
		break;
	case '=':
		GetNext();
		if(next == '@')
		{
			currentToken.token = RParenToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '|':
		GetNext();
		if(next == 'P')
		{
			currentToken.token = AddressOfToken;
			GetNext();
		}
		else
		{
			currentToken.token = ArrayDefToken;
			GetNext();
		}
		break;
	case '.':
		GetNext();
		if(next == '.')
		{
			currentToken.token = PointerDefToken;
			GetNext();
		}
		//could be a real number, ex. .67
		else if (isdigit(next))
		{
			//push back on the . and number, then parse has number
			std::stringstream ss;
			ss << '.';
			ss << next;
			ss << *input;

			input->clear();
			*input << ss;
			currentToken.value = "";

			this->ParseNumber();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '-':
		GetNext();
		if(next == '-')
		{
			currentToken.token = DerefToken;
			GetNext();
		}
		else if(next == '&')
		{
			currentToken.token = NegativeToken;
			GetNext();
		}
		else
			currentToken.token = ErrorToken;
		break;
	case '!':
		currentToken.token = EoLToken;
		GetNext();
		break;
	case 'G':
		GetNext();
		if(next == 'R')
		{
			GetNext();
			if(next == 'R')
			{
				currentToken.token = LMultiLineCommentToken;
				GetNext();
				break;
			}
		}
		currentToken.token = ErrorToken;
		break;
	case 'B':
		GetNext();
		if(next == 'A')
		{
			GetNext();
			if(next == 'R')
			{
				GetNext();
				if(next == 'K')
				{
					currentToken.token = RMultiLineCommentToken;
					GetNext();
					break;
				}
			}
		}
		else if(next == 'e')
		{
			GetNext();
			if(next == 'd')
			{
				currentToken.token = CaseToken;
				GetNext();
				break;
			}
		}

		currentToken.token = ErrorToken;
		break;

	case 'F':
		GetNext();
		if (next == 'e')
		{
			GetNext();
			if (next == 'e')
			{
				GetNext();
				if (next == 'd')
				{
					GetNext();
					if (next == 'C')
					{
						GetNext();
						if (next == 'o')
						{
							GetNext();
							if (next == 'r')
							{
								GetNext();
								if (next == 'g')
								{
									GetNext();
									if (next == 'i')
									{
										currentToken.token = InputRealToken;
										GetNext();
										break;
									}
								}
							}
						}
					}
					else if (next == 'D')
					{
						GetNext();
						if (next == 'a')
						{
							/*      GetNext();
							if (next == 'c')
							{
							GetNext();
							if (next == 'h')
							{
							GetNext();
							if (next == 's')
							{
							GetNext();
							if (next == 'h')
							{
							GetNext();
							if (next == 'u')
							{
							GetNext();
							if (next == 'n')
							{
							GetNext();
							if (next == 'd')
							{
							currentToken.token = InputStringToken;
							GetNext();
							break;
							}
							}
							}
							}
							}
							}
							}*/
							if (next == 'l')
							{
								GetNext();
								if (next == 'm')
								{
									GetNext();
									if (next == 'a')
									{
										GetNext();
										if (next == 't')
										{
											GetNext();
											if (next == 'i')
											{
												GetNext();
												if (next == 'a')
												{
													GetNext();
													if (next == 'n')
													{
														currentToken.token = InputBoolToken;
														GetNext();
														break;
													}
												}
											}
										}
									}
								}
							}
						}
					}
					else if (next == 'P')
					{
						GetNext();
						if (next == 'o')
						{
							GetNext();
							if (next == 'o')
							{
								GetNext();
								if (next == 'd')
								{
									GetNext();
									if (next == 'l')
									{
										GetNext();
										if (next == 'e')
										{
											currentToken.token = InputIntToken;
											GetNext();
											break;
										}
									}
								}
							}
						}
					}
					else if (next =='Y')
					{
						GetNext();
						if (next =='o')
						{
							GetNext();
							if (next =='r')
							{
								GetNext();
								if (next =='k')
								{
									GetNext();
									if (next =='i')
									{
										GetNext();
										if (next =='e')
										{
											currentToken.token = InputCharToken;
											GetNext();
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			else if (next == 't') {
				GetNext();
				if (next == 'c') {
					GetNext();
					if (next == 'h') {
						currentToken.token = FetchToken;
						GetNext();
						break;

					}
				}
			}
		}
		else if (next == 'r')
		{
			GetNext();
			if (next == 'o')
			{
				GetNext();
				if (next == 'm')
				{
					currentToken.token = FromToken;
					GetNext();
					break;
				}
			}
		}
		currentToken.token = ErrorToken;
		break;

	case 'S':
		GetNext();
		if (next == 'c')
		{
			GetNext();
			if (next == 'r')
			{
				GetNext();
				if (next == 'a')
				{
					GetNext();
					if (next == 't')
					{
						GetNext();
						if (next == 'c')
						{
							GetNext();
							if (next == 'h')
							{
								currentToken.token = RepeatToken;
								GetNext();
								break;
							}
						}
					}
				}
			}
		}
		else if (next == 'n')
		{
			GetNext();
			if (next == 'e')
			{
				GetNext();
				if (next == 'e')
				{
					GetNext();
					if (next == 'z')
					{
						GetNext();
						if (next == 'e')
						{
							currentToken.token = ElseToken;
							GetNext();
							break;
						}
					}
				}
			}
			else if (next == 'i')
			{
				GetNext();
				if (next == 'f')
				{
					GetNext();
					if (next == 'f')
					{
						currentToken.token = IfToken;
						GetNext();
						break;
					}
				}

			}
		}

		else if (next == 'p')
		{
			GetNext();
			if (next == 'e')
			{
				GetNext();
				if (next == 'a')
				{
					GetNext();
					if (next == 'k')
					{
						GetNext();
						if (next == 'C')
						{
							GetNext();
							if (next == 'o')
							{
								GetNext();
								if (next == 'r')
								{
									GetNext();
									if (next == 'g')
									{
										GetNext();
										if (next == 'i')
										{
											currentToken.token = PrintRealToken;
											GetNext();
											break;
										}
									}
								}
							}
						}
						else if (next == 'D')
						{
							GetNext();
							if (next == 'a')
							{
								/*GetNext();
								if (next == 'c')
								{
								GetNext();
								if (next == 'h')
								{
								GetNext();
								if (next == 's')
								{
								GetNext();
								if (next == 'h')
								{
								GetNext();
								if (next == 'u')
								{
								GetNext();
								if (next == 'n')
								{
								GetNext();
								if (next == 'd')
								{
								currentToken.token = PrintStringToken;
								GetNext();
								break;
								}
								}
								}
								}
								}
								}
								}*/
								if (next == 'l')
								{
									GetNext();
									if (next == 'm')
									{
										GetNext();
										if (next == 'a')
										{
											GetNext();
											if (next == 't')
											{
												GetNext();
												if (next == 'i')
												{
													GetNext();
													if (next == 'o')
													{
														GetNext();
														if (next == 'n')
														{
															currentToken.token = PrintBoolToken;
															GetNext();
															break;
														}
													}
												}
											}
										}
									}
								}
							}
						}
						else if (next == 'P')
						{
							GetNext();
							if (next == 'o')
							{
								GetNext();
								if (next == 'o')
								{
									GetNext();
									if (next == 'd')
									{
										GetNext();
										if (next == 'l')
										{
											GetNext();
											if (next == 'e')
											{
												currentToken.token = PrintIntToken;
												GetNext();
												break;
											}
										}
									}
								}
							}

						}
						else if (next =='Y')
						{
							GetNext();
							if (next =='o')
							{
								GetNext();
								if (next =='r')
								{
									GetNext();
									if (next =='k')
									{
										GetNext();
										if (next =='i')
										{
											GetNext();
											if (next =='e')
											{
												currentToken.token = PrintCharToken;
												GetNext();
												break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if (next == 'Q')
		{
			GetNext();
			if (next == 'U')
			{
				GetNext();
				if (next == 'I')
				{
					GetNext();
					if (next == 'R')
					{
						GetNext();
						if (next == 'R')
						{
							GetNext();
							if (next == 'E')
							{
								GetNext();
								if (next == 'L')
								{
									currentToken.token = LBlockToken;
									GetNext();
									break;
								}
							}
						}
					}
				}
			}
		}
		else if (next == 't')
		{
			GetNext();
			if (next == 'r')
			{
				GetNext();
				if (next == 'a')
				{
					GetNext();
					if (next == 'y')
					{
						currentToken.token = VoidDecToken;
						GetNext();
						break;
					}
				}
			}
		}
		currentToken.token = ErrorToken;
		break;
	case 'T':
		GetNext();
		if (next == 'o')
		{
			currentToken.token = ToToken;
			GetNext();
			break;
		}

	case 'N':      
		GetNext();
		if(next == '\'')
		{
			currentToken.token = AndToken;
			GetNext();
			break;
		}  
		else if (next == 'A')
		{
			GetNext();
			if (next == 'P')
			{
				GetNext();
				if (next == 'T')
				{
					GetNext();
					if (next == 'I')
					{
						GetNext();
						if (next == 'M')
						{
							GetNext();
							if (next == 'E')
							{
								currentToken.token = SwitchToken;
								GetNext();
								break;
							}
						}
					}
				}
			}
		}
		else if (next == 'e')
		{
			GetNext();
			if (next == 'v')
			{
				GetNext();
				if (next == 'e')
				{
					GetNext();
					if (next == 'r')
					{
						GetNext();
						if (next == 'm')
						{
							GetNext();
							if (next == 'i')
							{
								GetNext();
								if (next == 'n')
								{
									GetNext();
									if (next == 'd')
									{
										GetNext();
										if (next == '.')
										{
											GetNext();
											if (next == '.')
											{
												GetNext();
												if (next == '.')
												{
													currentToken.token = RBlockToken;
													GetNext();
													break;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if ('O')
		{
			GetNext();
			if (next == 'F')
			{
				GetNext();
				if (next == 'L')
				{
					GetNext();
					if (next == 'E')
					{
						GetNext();
						if (next == 'A')
						{
							GetNext();
							if (next == 'S')
							{
								currentToken.token = UntilToken;
								GetNext();
								break;
							}
						}
					}
				}
			}
		}
		currentToken.token = ErrorToken;
		break;

	case 'D':
		GetNext();
		if(next=='a'){
			GetNext();
			/*if(next=='c'){
			GetNext();
			if(next=='h'){
			GetNext();
			if(next=='s'){
			GetNext();
			if(next=='h'){
			GetNext();
			if(next=='u'){
			GetNext();
			if(next=='n'){
			GetNext();
			if(next=='d'){
			currentToken.token=StringDecToken;
			GetNext();
			}
			else
			currentToken.token=ErrorToken;
			break;
			}
			}
			}
			}
			}
			}*/
			if(next=='l'){
				GetNext();
				if(next=='m'){
					GetNext();
					if(next=='a'){
						GetNext();
						if(next=='t'){
							GetNext();
							if(next=='i'){
								GetNext();
								if(next=='a'){
									GetNext();
									if(next=='n'){
										currentToken.token=BoolDecToken;
										GetNext();
										break;
									}
									else
										currentToken.token=ErrorToken;
									break;
								}
							}	
						}
					}
				}
			}
		}
		else if (next == 'o'){
			GetNext();
			if(next == 'g'){
				GetNext();
				if(next == 'h'){
					GetNext();
					if(next == 'o'){
						GetNext();
						if(next == 'u'){
							GetNext();
							if(next == 's'){
								GetNext();
								if(next == 'e'){
									currentToken.token=DefaultToken;
									GetNext();
								}
								else 
									currentToken.token=ErrorToken;
								break;
							}
						}
					}
				}
			}
		}

		currentToken.token = ErrorToken;
		break;

	case 'P':
		GetNext();
		if(next=='A'){
			GetNext();
			if(next=='N'){
				GetNext();
				if(next=='T'){
					currentToken.token=SingleLineCommentToken;
					GetNext();
					//read in the rest of the line
					while(next!='\n')
						GetNext();
				}
				else 
					currentToken.token=ErrorToken;
				break;
			}
		}

		else if(next=='o'){
			GetNext();
			if(next=='o'){
				GetNext();
				if(next=='d'){
					GetNext();
					if(next=='l'){
						GetNext();
						if(next=='e'){
							currentToken.token=IntDecToken;
							GetNext();
						}
						else
							currentToken.token=ErrorToken;
						break;
					}
				}
			}
		}
		break;

	case 'Y':
		GetNext();
		if(next=='o'){
			GetNext();
			if(next=='r'){
				GetNext();
				if(next=='k'){
					GetNext();
					if(next=='i'){
						GetNext();
						if(next=='e'){
							currentToken.token=CharDecToken;
							GetNext();
						}
						else
							currentToken.token=ErrorToken;
						break;
					}
				}
			}
		}
		currentToken.token = ErrorToken;
		break;
	case 'C':
		GetNext();
		if(next=='h'){
			GetNext();
			if(next=='a'){
				GetNext();
				if(next=='s'){
					GetNext();
					if(next=='e'){
						currentToken.token=WhileToken;
						GetNext();
					}
					else 
						currentToken.token=ErrorToken;
					break;
				}
			}
		}

		else if(next=='o'){
			GetNext();
			if(next=='r'){
				GetNext();
				if(next=='g'){
					GetNext();
					if(next=='i'){
						currentToken.token=RealDecToken;
						GetNext();
					}
					else
						currentToken.token=ErrorToken;
					break;
				}
			}
		}
		break;
	case 'R':
		GetNext();
		if(next=='o'){
			GetNext();
			if(next=='l'){
				GetNext();
				if(next=='l'){
					GetNext();
					if(next=='o'){
						GetNext();
						if(next=='v'){
							GetNext();
							if(next=='e'){
								GetNext();
								if(next=='r'){
									currentToken.token=ForToken;
									GetNext();
								}
								else
									currentToken.token=ErrorToken;
								break;
							}
						}
					}
				}
			}
		}
		break;

	case 'W':
		GetNext();
		if(next == 'a'){
			GetNext();
			if(next == 'k'){
				GetNext();
				if(next == 'e'){
					currentToken.token=BreakToken;
					GetNext();
				}
				else
					currentToken.token=ErrorToken;
				break;
			}
		}

	default:
		//if it begins with a lower case, could be a name of a func or var
		if (islower(next)) {
			do {
				GetNext();
			} while ( (isalpha(next) && !isspace(next)) || isdigit(next));
			currentToken.token = NameToken;
		}
		break;


	}

	if (currentToken.token == ErrorToken) {
		currentToken.value = "Unkown symbol \"" + currentToken.value + "\" found on line " + patch::to_string(lineNumber);
		hasErrored = true;
	}
	if (currentToken.token == SingleLineCommentToken)
		return NextToken();
	return currentToken;
}
