/*
Scanner.cpp
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Scanner.h"
#include "SymbolTable.h"
#include "Parser.h"

using namespace std;

//TOKEN BUILDER FUNCTION//
vector <Scanner::TOKENS> Scanner::build_tokens(vector<TOKENS>& tokens)                    //accepting code and token vectors for iteration and inserting
{
	int counter = 0;                                                           //counter to count how far into the code vector we go before generating a token
	static int linecounter = 1;                                                //used to print what line an error was generated on   
	auto list = code.begin();                                                  //iterator to be used for looking through the code vector

	Scanner::TOKENS new_entry;

	cout << "made it to builder function" << endl;

	if (code.size() == 1)                                                     //if the size of the vectore is greater than 0 begin looking for tokens
	{
		new_entry.token_name = "DoneToken";
		tokens.push_back(new_entry);
		return tokens;
	}
		//GRAPH 1 START//
		//Assign/Decrement/Increment generator//
		else if (code[0] == '-')
		{
			counter++;
			advance(list, 1);                                                //advance in the list by 1                                             
			if (*list == '-')                                                //if statements to determine what tokens, if any, exist
			{
				counter++;
				advance(list, 1);
				cout << "\nAssignToken_Scanner";
				new_entry.token_name = "AssignToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

			}
			else if (*list == ')')
			{
				counter++;
				cout << "\nDecrToken";
																			 //call delete function to remove the characters that consituted the token    

			}
			else if (*list == '(')
			{
				counter++;
				cout << "\nIncrToken";

			}
			else
			{
				counter++;
				advance(list, 1);                                                           //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}
		}
		//-----------------//


		//left/right parenth. token//
		else if (code[0] == '#')
		{
			counter++;
			advance(list, 1);                                                            //advance in the list by 1                                         
			if (*list == 'L')
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				if (*list == '#')                                                       //if statements to determine what tokens, if any, exist                 
				{
					counter++;
					cout << "\nLParenToken_Scanner";
					new_entry.token_name = "LParenToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
				}
				else
				{
					counter++;
					advance(list, 1);                                                 //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
				}

			}
			else if (*list == 'R')
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				if (*list == '#')
				{
					counter++;
					advance(list, 1);
					cout << "\nRParenToken_Scanner";
					new_entry.token_name = "RParenToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
				}
				else
				{
					counter++;
					advance(list, 1);                                               //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}
		}
		//-----------------//


		//subtoken//
		else if (code[0] == ')')                                                             //if statements to determine what tokens, if any, exist
		{
			counter++;
			cout << "\nSubToken";
		}
		//-----------------//


		//AndToken//
		else if (code[0] == '*')                                                           //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                             //advance in the list by 1                                         
			if (*list == 'N')
			{
				counter++;
				cout << "\nAndToken";
			}
			else
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}

		}
		//-----------------//

		//NegateToken//
		else if (code[0] == '=')                                                  //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                     //advance in the list by 1                                       
			if (*list == '*')
			{
				counter++;
				cout << "\nNegateToken";
			}
			else
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}

		}
		//-----------------//

		//AddToken/StringEscToken//
		else if (code[0] == '\\')
		{
			counter++;
			advance(list, 1);                                                   //advance in the list by 1                                           
			if (*list == ')')                                                   //if statements to determine what tokens, if any, exist
			{
				counter++;
				cout << "\nAddToken";
			}
			else if (*list == 'M')
			{
				counter++;
				cout << "\nStringEscToken";
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}
		}
		//-----------------//

		//ArrayToken//
		else if (code[0] == ']')
		{
			counter++;
			advance(list, 1);                                                            //advance in the list by 1                                           
			if (*list == '[')                                                            //if statements to determine what tokens, if any, exist
			{
				counter++;
				cout << "\nArrayDefToken";
			}
			else
			{
				counter++;
				advance(list, 1);                                                     //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}

		}

		//-----------------//
		//GRAPH 1 END//

		//GRAPH 2 START//
		//HexToken//
		else if (code[0] == 'X')                                                                  //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                                    //advance in the list by 1                                         
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);                                                                 //advance in the list by 1 
				if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
				{
					counter++;
					advance(list, 1);                                                             //advance in the list by 1 
					if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
						{
							counter++;
							advance(list, 1);                                                    //advance in the list by 1 
							if ((*list >= 'A' && *list <= 'F') || (*list >= '0' && *list <= '9'))
							{
								counter++;
								cout << "\nHexToken";
							}
							else
							{
								counter++;
								advance(list, 1);                                               //advance in the list by 1 
								cout << "\nErrorToken found on line: " << linecounter << "\n";
							}
						}
						else
						{
							counter++;
							advance(list, 1);                                                  //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                       //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
				}
			}

		}
		//-----------------//



		//CharLitToken / StringLitToken//
		else if (code[0] == '[')                                                       //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                         //advance in the list by 1                                         
			if (*list == '[')
			{
				counter++;
				advance(list, 1);
				if (*list == '\\')
				{
					counter++;
					advance(list, 1);
					if (*list == 'M')
					{
						counter++;
						advance(list, 1);                                                //advance in the list by 1 
						if (*list == ']')
						{
							counter++;
							advance(list, 1);                                            //advance in the list by 1 
							if (*list == ']')
							{
								counter++;
								cout << "\nCharLitToken";
							}
						}
					}
				}
				else if (isalpha(*list) || isalnum(*list))
				{
					counter++;
					advance(list, 1);                                                //advance in the list by 1 
					if (*list == ']')
					{
						counter++;
						advance(list, 1);                                            //advance in the list by 1 
						if (*list == ']')
						{
							counter++;
							cout << "\nCharLitToken";
						}
						else
						{
							counter++;
							advance(list, 1);                                              //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                 //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                     //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
				}
			}
			else if (*list >= 32 && *list <= 126)
			{
				while (*list != ']')
				{
					counter++;
					advance(list, 1);												    //advance in the list by 1 
				}
				counter++;
				cout << "\nStringLitToken";
			}
		}
		//-----------------//


		//IntToken//
		else if (isdigit(code[0]) || code[0] == '.')                               //if statements to determine what tokens, if any, exist
		{
			counter++;
			vector <char> numvector;
			bool isReal = false;

			numvector.push_back(*list);                                          //push the int into the numvector vector
			while (((isdigit(*list)) || (*list == 'E') || (*list == 'e') || (*list == '-') || (*list == '.')) && (code.size() > counter))
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				numvector.push_back(*list);                                     //push the int into the numvector vector
			}

			for (int i = 0; i < numvector.size(); i++)                          //if statement to determine if we encountered a real
			{
				if (numvector[i] == '.') { isReal = true; }
				else if (numvector[i] == 'E') { isReal = true; }
				else if (numvector[i] == 'e') { isReal = true; }
				else if (numvector[i] == '-') { isReal = true; }
			}

			numvector.clear();                                                 //clear numvector for next iteration

			if (isReal != true)
			{
				cout << "\nIntLitToken";
				new_entry.token_name = "IntLitToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (isReal == true)
			{
				cout << "\nRealLitToken";
			}
		}
		//-----------------//
		//END GRAPH 2//

		//GRAPH 3 STARTS//
		//True/False Token//
		else if (code[0] == '^')                                                 //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                    //advance in the list by 1 
			if (*list == ' ')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				cout << "\nSepToken";
			}
			else if (*list == 'G')
			{
				counter++;
				cout << "\nTrueToken";
			}
			else if (*list == 'N')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'G')
				{
					counter++;
					cout << "\nFalseToken";
				}
			}

		}

		//--------------------//


		//Division Token//
		else if (code[0] == '_')                                           //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                              //advance in the list by 1 
			if (*list == '^')
			{
				counter++;
				advance(list, 1);                                         //advance in the list by 1 
				if (*list == '_')
				{
					counter++;
					cout << "\nDivToken";
				}
			}
		}

		//--------------------//


		//EOL/RBLOCK Token//
		else if (code[0] == '|')                                     //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			if (*list == 'P')
			{
				counter++;
				cout << "\nEoLToken_Scanner";
				new_entry.token_name = "EoLToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}

			else if (*list == '-')
			{
				counter++;
				advance(list, 1);									//advance in the list by 1 
				if (*list == '-')
				{
					counter++;
					advance(list, 1);								//advance in the list by 1 
					if (*list == '%')
					{
						counter++;
						cout << "\nRBlockToken_Scanner";
						new_entry.token_name = "RBlockToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
			}
		}

		//-------------------//



		//LBlockToken//
		else if (code[0] == '%')												  //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);													//advance in the list by 1 
			if (*list == '-')
			{
				counter++;
				advance(list, 1);												//advance in the list by 1 
				if (*list == '-')
				{
					counter++;
					advance(list, 1);										  //advance in the list by 1 
					if (*list == '|')
					{
						counter++;
						cout << "\nLBlockToken_Scanner";
						new_entry.token_name = "LBlockToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
			}
		}


		//-------------------//


		//Pointer Token//
		else if (code[0] == '~')                                                //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);													//advance in the list by 1 
			if (*list == '>')
			{
				counter++;
				cout << "\nPointerToken";
			}
		}


		//-----------------------//


		//Equality/Less/LessThanOrEq Token//
		else if (code[0] == '<')
		{
			counter++;
			advance(list, 1);												//advance in the list by 1 
			if (*list == '>')
			{
				counter++;
				cout << "\nEqToken";
			}

			else if (*list == 'L')
			{
				counter++;
				cout << "\nLessToken";
			}

			else if (*list == 'E')
			{
				counter++;
				cout << "\nLessThanOrEqToken";
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}
		}


		//-----------------------//


		//Greater/GreaterThanOrEq Token//
		else if (code[0] == '>')                                                 //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);													//advance in the list by 1 
			if (*list == 'G')
			{
				counter++;
				cout << "\nGreaterThanOrEqToken";
			}

			else if (*list == 'W')
			{
				counter++;
				cout << "\nGreaterToken";
			}
		}
		//------------------------------//


		// Graph 3 ends, start Graph 4//
		//LMultiLineComment/Or Token//
		else if (code[0] == '/')                                            //if statements to determine what tokens, if any, exist
		{
			advance(list, 1);
			counter++;
			if (*list == '@')
			{
				advance(list, 1);
				counter++;
				while (*list != '@')
				{
					advance(list, 1);
					counter++;
				}
				cout << "\nLMultiLineCommentToken";
			}

			else if (*list == 'B')
			{
				counter++;
				advance(list, 1);                                        //advance in the list by 1 
				if (*list == '/')
				{
					counter++;
					cout << "\nOrToken";
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
			}
		}
		//------------------------//


		//SingleLineComment/RMultiLineComment//

		else if (code[0] == '@')                                                 //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                    //advance in the list by 1 
			if (*list == '/')
			{
				counter++;
				cout << "\nRMultiLineCommentToken";
			}
			else if (*list != '\n')
			{
				while (*list != '\n')
				{
					counter++;
					advance(list, 1);                                            //advance in the list by 1 
				}
				cout << "\nSingleLineToken";
			}
			else if (*list == '/')
			{
				counter++;
				cout << "\nRMultiLineCommentToken";
			}



		}
		//------------------------//


		//While Token//
		else if (code[0] == 'R')                                                   //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                                   //advance in the list by 1 
			if (*list == 'E')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'V')
				{
					counter++;
					cout << "\nWhileToken";
				}
			}
			else if (*list == 'O')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'M')
				{
					counter++;
					advance(list, 1);                                              //advance in the list by 1 
					if (*list == 'O')
					{
						counter++;
						cout << "\nBreakToken";
					}
				}
			}

		}

		//-------------------------------//


		//Case Token//
		else if (code[0] == 'S')                                        //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                           //advance in the list by 1 
			if (*list == 'U')
			{
				counter++;
				advance(list, 1);                                       //advance in the list by 1 
				if (*list == 'B')
				{
					counter++;
					advance(list, 1);
					if (*list == ' ')
					{
						counter++;
						advance(list, 1);                                //advance in the list by 1 
						if ((*list >= 48 && *list <= 57) || (*list >= 65 && *list <= 90) || (*list >= 97 && *list <= 122))
						{
							counter++;
							advance(list, 1);
							cout << "\nCaseToken";
						}
					}
				}
			}
		}


		//--------------------------//




		//Multi Token//
		else if (code[0] == 'T')                                           //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                             //advance in the list by 1 
			if (*list == 'D')
			{
				counter++;
				cout << "\nMultiToken";
			}
		}


		// Graph 5 begins //
		//Else Token//
		else if (code[0] == 'A')                                         //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);                                            //advance in the list by 1 
			if (*list == 'U')
			{
				counter++;
				advance(list, 1);                                      //advance in the list by 1 
				if (*list == 'D')
				{
					counter++;
					cout << "\nElseToken";
				}
			}
		}
		//------------------------//


		//RealDec/VoidDec Token//
		else if (code[0] == 'B')                                                 //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);													//advance in the list by 1 
			if (*list == 'B')
			{
				counter++;
				cout << "\nRealDecToken";
			}

			else if (*list == 'R')
			{
				counter++;
				advance(list, 1);												//advance in the list by 1 
				if (*list == 'W')
				{
					counter++;
					advance(list, 1);											//advance in the list by 1 
					if (*list == 'N')
					{
						counter++;
						advance(list, 1);										//advance in the list by 1 
						if (*list == 'S')
						{
							counter++;
							cout << "\nVoidDecToken_Scanner";
							new_entry.token_name = "VoidDecToken";
							tokens.push_back(new_entry);
							code.erase(code.begin(), code.begin() + counter);
							return tokens;
						}
					}
				}
			}
			else if (*list == 'A')
			{
				counter++;
				advance(list, 1);												//advance in the list by 1 
				if (*list == 'N')
				{
					counter++;
					advance(list, 1);												//advance in the list by 1 
					if (*list == 'D')
					{
						counter++;
						advance(list, 1);												//advance in the list by 1 
						if (*list == 'W')
						{
							counter++;
							advance(list, 1);												//advance in the list by 1 
							if (*list == 'A')
							{
								counter++;
								advance(list, 1);												//advance in the list by 1 
								if (*list == 'G')
								{
									counter++;
									advance(list, 1);												//advance in the list by 1 
									if (*list == 'O')
									{
										counter++;
										advance(list, 1);												//advance in the list by 1 
										if (*list == 'N')
										{
											counter++;
											advance(list, 1);												//advance in the list by 1 
											cout << "\nDefaultToken";
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//----------------------//


		//IntDec/StringDec/BoolDec Token//
		else if (code[0] == 'C')                                                    //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);														//advance in the list by 1 
			if (*list == 'H')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'A')
				{
					counter++;
					advance(list, 1);
					if (*list == 'I')
					{
						counter++;
						advance(list, 1);											//advance in the list by 1 
						if (*list == 'N')
						{
							counter++;
							advance(list, 1);										//advance in the list by 1 
							if (*list == 'S')
							{
								counter++;
								new_entry.token_name = "IntDecToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								return tokens;
							}
						}
					}
				}
				else if (*list == 'L')
				{
					counter++;
					cout << "\nCHLToken";
				}
			}

			else if (*list == 'L')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'E')
				{
					counter++;
					advance(list, 1);												//advance in the list by 1 
					if (*list == 'A')
					{
						counter++;
						advance(list, 1);											//advance in the list by 1 
						if (*list == 'T')
						{
							counter++;
							advance(list, 1);										//advance in the list by 1 
							if (*list == 'S')
							{
								counter++;
								cout << "\nStringDecToken";
							}
						}
					}
				}
			}

			else if (*list == 'O')
			{
				counter++;
				advance(list, 1);												//advance in the list by 1 
				if (*list == 'I')
				{
					counter++;
					advance(list, 1);											//advance in the list by 1 
					if (*list == 'N')
					{
						counter++;
						cout << "\nBoolDecToken";
					}
				}
			}
		}
		//-----------------------------//


		//For/CharDec Token//
		else if (code[0] == 'G')                                             //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);												//advance in the list by 1 
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);											//advance in the list by 1 
				if (*list == 'L')
				{
					counter++;
					advance(list, 1);										//advance in the list by 1 
					if (*list == 'F')
					{
						counter++;
						cout << "\nForToken";
					}
				}

				else if (*list == 'O')
				{
					counter++;
					advance(list, 1);									//advance in the list by 1 
					if (*list == 'N')
					{
						counter++;
						cout << "\nCharDecToken";
					}
				}
			}
		}


		//-------------------------//


		//Deref Token//
		else if (code[0] == 'K')                                            //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);												//advance in the list by 1 
			if (*list == 'O')
			{
				counter++;
				cout << "\nDerefToken";
			}
		}
		//---------------------------//


		//Switch Token//
		else if (code[0] == 'M')                                                     //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);														//advance in the list by 1 
			if (*list == 'O')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'T')
				{
					counter++;
					advance(list, 1);												//advance in the list by 1 
					if (*list == 'I')
					{
						counter++;
						advance(list, 1);											//advance in the list by 1 
						if (*list == 'O')
						{
							counter++;
							advance(list, 1);										//advance in the list by 1 
							if (*list == 'N')
							{
								counter++;
								cout << "\nSwitchToken";
							}
						}
					}
				}
			}
		}
		//----------------------------------//

		//Graph 5 ends//

		// MISC Functions //

		//Function token (added later)
		else if (code[0] == 'P')                                                     //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);														//advance in the list by 1 
			if (*list == 'L')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'A')
				{
					counter++;
					advance(list, 1);												//advance in the list by 1 
					if (*list == 'Y')
					{
						counter++;
						cout << "\nFunDecToken_Scanner";
						new_entry.token_name = "FunDecToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
			}
			else if (*list == 'U')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'N')
				{
					counter++;
					advance(list, 1);													//advance in the list by 1 
					if (*list == 'T')
					{
						counter++;
						cout << "\nPuntToken";
					}
				}
			}
			else if (*list == 'R')
			{
				counter++;
				cout << "\nPRToken";
			}
			else if (*list == 'C')
			{
				counter++;
				cout << "\nIfToken";
			}
			else if (*list == 'A')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'S')
				{
					counter++;
					advance(list, 1);													//advance in the list by 1 
					if (*list == 'S')
					{
						counter++;
						cout << "\nReturnToken";
					}
				}
			}
		}

		//Main function NFL_CHAN

		else if (code[0] == 'N')                                                     //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);														//advance in the list by 1 
			if (*list == 'F')
			{
				counter++;
				advance(list, 1);													//advance in the list by 1 
				if (*list == 'L')
				{
					counter++;
					advance(list, 1);												//advance in the list by 1 
					if (*list == '_')
					{
						counter++;
						advance(list, 1);													//advance in the list by 1 
						if (*list == 'C')
						{
							counter++;
							advance(list, 1);													//advance in the list by 1 
							if (*list == 'H')
							{
								counter++;
								advance(list, 1);													//advance in the list by 1 
								if (*list == 'A')
								{
									counter++;
									advance(list, 1);													//advance in the list by 1 
									if (*list == 'N')
									{
										counter++;
										cout << "\nMainToken_Scanner";
										new_entry.token_name = "MainToken";
										tokens.push_back(new_entry);
										code.erase(code.begin(), code.begin() + counter);
										return tokens;
									}
								}
							}
						}
					}
				}
			}
		}

		//newline & tab character//
		else if ((code[0] == '\n') || code[0] == '\t')                                         //if statements to determine what tokens, if any, exist
		{
			counter++;
			linecounter++;
			advance(list, 1);											//advance in the list by 1 
																		////elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
		}

		//-------------------//

		//white space character//
		else if (code[0] == ' ')                                          //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);
			cout << "\nWhiteSpaceToken_Scanner";
			new_entry.token_name = "WhiteSpaceToken";
			tokens.push_back(new_entry);
			code.erase(code.begin(), code.begin() + counter);
			return tokens;												//advance in the list by 1 
		}
		//-------------------//

		//ID Token//
		else if ((code[0] > 'a') && (code[0] < 'z'))                  //if statements to determine what tokens, if any, exist
		{
			vector <char> idName;
			counter++;
			advance(list, 1);
			char value;
			value = code[0];
			idName.push_back(value);
			int a;
			while (*list > 48 && *list < 122)
			{
				value = *list;
				idName.push_back(value);
				counter++;
				advance(list, 1);
			}

			a = counter;

			if (counter < 4)
			{
				cout << "\nIdToken_Scanner";
				new_entry.token_name = "IdToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}

			else if (code[a - 1] == '[')
			{
				while ((code[a - 2] >= 0 && (code[a - 2] <= 9)))
				{
					a--;
				}
				if (code[a - 3] == ']')
				{
					cout << "\nID_Array_Token";
				}
			}
			else if (code[counter] != '[')
			{
				cout << "\nIdToken_Scanner";
				new_entry.token_name = "IdToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
		}
		//------------//
		else                                                        //else that notifies the user that an error has been encountered
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			cout << "\nErrorToken found on line: " << linecounter << " error is: " << code[0] << "\n";

		}
}
//INSERT INTO SYMBOL TABLE//
void Scanner::insert_symbol_table(vector<TOKENS>& tokens)
{

	for (int i = 0; i < tokens.size(); i++)
	{

	}



}