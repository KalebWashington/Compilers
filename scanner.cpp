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



	//Symbol table entry variables//
	Symboltable symbol_list;
	static Symboltable::TABLE new_table_entry;
	vector <Symboltable::TABLE> symbols;
	static int symbol_counter = 0;
	

	/*
	ST_SWITCH turns on/off symboltable insertion. 
	
	True = ON
	False = OFF

	Inserting into the table is not as high on the priority list, so we may need to turn it off till we get the vital
	aspects functioning.
	*/
	bool ST_SWITCH = false;                             
	//-------------------//


	


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
				new_entry.token_name = "DecrToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
																			 //call delete function to remove the characters that consituted the token    

			}
			else if (*list == '(')
			{
				counter++;
				cout << "\nIncrToken";
				new_entry.token_name = "IncrToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

			}
			else
			{
				counter++;
				advance(list, 1);                                                           //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
		}
		//-----------------//


		//subtoken//
		else if (code[0] == ')')                                                             //if statements to determine what tokens, if any, exist
		{
			counter++;
			cout << "\nSubToken";
			new_entry.token_name = "SubToken";
			tokens.push_back(new_entry);
			code.erase(code.begin(), code.begin() + counter);
			return tokens;
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
				new_entry.token_name = "AndToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "NegateToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "AddToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (*list == 'M')
			{
				counter++;
				cout << "\nStringEscToken";
				new_entry.token_name = "StringEscToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "ArrayDefToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else
			{
				counter++;
				advance(list, 1);                                                     //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
								new_entry.token_name = "HexToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								return tokens;
							}
							else
							{
								counter++;
								advance(list, 1);                                               //advance in the list by 1 
								cout << "\nErrorToken found on line: " << linecounter << "\n";
								new_entry.token_name = "ErrorToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								return tokens;
							}
						}
						else
						{
							counter++;
							advance(list, 1);                                                  //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);
							code.erase(code.begin(), code.begin() + counter);
							return tokens;
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                       //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
								new_entry.token_name = "CharLitToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								return tokens;
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
							new_entry.token_name = "CharLitToken";
							tokens.push_back(new_entry);
							code.erase(code.begin(), code.begin() + counter);
							return tokens;
						}
						else
						{
							counter++;
							advance(list, 1);                                              //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);
							code.erase(code.begin(), code.begin() + counter);
							return tokens;
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                 //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                     //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
				new_entry.token_name = "StringLitToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "RealLitToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "SepToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (*list == 'G')
			{
				counter++;
				cout << "\nTrueToken";
				new_entry.token_name = "TrueToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (*list == 'N')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'G')
				{
					counter++;
					cout << "\nFalseToken";
					new_entry.token_name = "FalseToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
					new_entry.token_name = "DivToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
				new_entry.token_name = "PointerToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "EqToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

			}

			else if (*list == 'L')
			{
				counter++;
				cout << "\nLessToken";
				new_entry.token_name = "LessToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

			}

			else if (*list == 'E')
			{
				counter++;
				cout << "\nLessThanOrEqToken";
				new_entry.token_name = "LessThanOrEqToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "GreaterThanOrEqToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}

			else if (*list == 'W')
			{
				counter++;
				cout << "\nGreaterToken";
				new_entry.token_name = "GreaterToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

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
				new_entry.token_name = "LMultiLineCommentToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}

			else if (*list == 'B')
			{
				counter++;
				advance(list, 1);                                        //advance in the list by 1 
				if (*list == '/')
				{
					counter++;
					cout << "\nOrToken";
					new_entry.token_name = "OrToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;

				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
				new_entry.token_name = "RMultiLineCommentToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;

			}
			else if (*list != '\n')
			{
				while (*list != '\n')
				{
					counter++;
					advance(list, 1);                                            //advance in the list by 1 
				}
				cout << "\nSingleLineToken";
				new_entry.token_name = "SingleLineToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (*list == '/')
			{
				counter++;
				cout << "\nRMultiLineCommentToken";
				new_entry.token_name = "RMultiLineCommentToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
					new_entry.token_name = "WhileToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
						new_entry.token_name = "BreakToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
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
							new_entry.token_name = "CaseToken";
							tokens.push_back(new_entry);
							code.erase(code.begin(), code.begin() + counter);
							return tokens;
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
				new_entry.token_name = "MultiToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
					new_entry.token_name = "ElseToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
				new_entry.token_name = "RealDecToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
							
							
							
							//insert into table//
							if (ST_SWITCH == true)
							{
								new_table_entry.type = "VOID";
								symbol_counter++;
								if (new_table_entry.kind != "FUNC")
								{
									new_table_entry.kind = "VAR";
									if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
									{

										//need to figure out an if statement to handle arrays


										symbol_list.add_symbol(symbols, new_table_entry);
										////symbol_list.print_symbol(symbols);
										new_table_entry.name = "EMPTY";
										new_table_entry.kind = "EMPTY";
										new_table_entry.type = "EMPTY";
										new_table_entry.size = 1;
										symbol_counter = 0;
									}
								}


								else if (new_table_entry.kind == "FUNC")
								{
									if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
									{

										//need to figure out an if statement to handle arrays


										symbol_list.add_symbol(symbols, new_table_entry);
										////symbol_list.print_symbol(symbols);
										new_table_entry.name = "EMPTY";
										new_table_entry.kind = "EMPTY";
										new_table_entry.type = "EMPTY";
										new_table_entry.size = 1;
										symbol_counter = 0;
									}
								}

							}
							//---------------//
							
							
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
											new_entry.token_name = "DefaultToken";
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

								//insert into table//
								if (ST_SWITCH == true)
								{
									new_table_entry.type = "INT";
									symbol_counter++;
									if (new_table_entry.kind != "FUNC")
									{
										new_table_entry.kind = "VAR";
										if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
										{

											//need to figure out an if statement to handle arrays


											symbol_list.add_symbol(symbols, new_table_entry);
											////symbol_list.print_symbol(symbols);
											new_table_entry.name = "EMPTY";
											new_table_entry.kind = "EMPTY";
											new_table_entry.type = "EMPTY";
											new_table_entry.size = 1;
											symbol_counter = 0;
										}
									}


									else if (new_table_entry.kind == "FUNC")
									{
										if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
										{

											//need to figure out an if statement to handle arrays


											symbol_list.add_symbol(symbols, new_table_entry);
											////symbol_list.print_symbol(symbols);
											new_table_entry.name = "EMPTY";
											new_table_entry.kind = "EMPTY";
											new_table_entry.type = "EMPTY";
											new_table_entry.size = 1;
											symbol_counter = 0;
										}
									}

								}
                                //---------------//

								return tokens;
							}
						}
					}
				}
				else if (*list == 'L')
				{
					counter++;
					cout << "\nCHLToken";
					new_entry.token_name = "CHLToken";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
								new_entry.token_name = "StringDecToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								
								
								
								
								//insert into table//
								if (ST_SWITCH == true)
								{
									new_table_entry.type = "STRING";
									symbol_counter++;
									if (new_table_entry.kind != "FUNC")
									{
										new_table_entry.kind = "VAR";
										if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
										{

											//need to figure out an if statement to handle arrays


											symbol_list.add_symbol(symbols, new_table_entry);
											//symbol_list.print_symbol(symbols);
											new_table_entry.name = "EMPTY";
											new_table_entry.kind = "EMPTY";
											new_table_entry.type = "EMPTY";
											new_table_entry.size = 1;
											symbol_counter = 0;
										}
									}


									else if (new_table_entry.kind == "FUNC")
									{
										if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
										{

											//need to figure out an if statement to handle arrays


											symbol_list.add_symbol(symbols, new_table_entry);
											//symbol_list.print_symbol(symbols);
											new_table_entry.name = "EMPTY";
											new_table_entry.kind = "EMPTY";
											new_table_entry.type = "EMPTY";
											new_table_entry.size = 1;
											symbol_counter = 0;
										}
									}

								}
								//---------------//														
								
								return tokens;
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
						new_entry.token_name = "BoolDecToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						
						
						
						//insert into table//
						if (ST_SWITCH == true)
						{
							new_table_entry.type = "BOOL";
							symbol_counter++;
							if (new_table_entry.kind != "FUNC")
							{
								new_table_entry.kind = "VAR";
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									//symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}


							else if (new_table_entry.kind == "FUNC")
							{
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									//symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}

						}
						//---------------//
						
						
						
						return tokens;
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
						new_entry.token_name = "ForToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
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
						new_entry.token_name = "CharDecToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						
						
						//insert into table//
						if (ST_SWITCH == true)
						{
							new_table_entry.type = "CHAR";
							symbol_counter++;
							if (new_table_entry.kind != "FUNC")
							{
								new_table_entry.kind = "VAR";
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									//symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}


							else if (new_table_entry.kind == "FUNC")
							{
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									//symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}

						}
						//---------------//
						
						
						
						return tokens;
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
				new_entry.token_name = "DerefToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
								new_entry.token_name = "SwitchToken";
								tokens.push_back(new_entry);
								code.erase(code.begin(), code.begin() + counter);
								return tokens;
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
						
						
						//insert into table//
						if (ST_SWITCH == true)
						{
							new_table_entry.kind = "FUNC";
							symbol_counter++;
							if (new_table_entry.kind != "FUNC")
							{
								new_table_entry.kind = "VAR";
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									////symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}


							else if (new_table_entry.kind == "FUNC")
							{
								if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
								{

									//need to figure out an if statement to handle arrays


									symbol_list.add_symbol(symbols, new_table_entry);
									////symbol_list.print_symbol(symbols);
									new_table_entry.name = "EMPTY";
									new_table_entry.kind = "EMPTY";
									new_table_entry.type = "EMPTY";
									new_table_entry.size = 1;
									symbol_counter = 0;
								}
							}

						}
						//---------------//

						
						
						
						
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
						new_entry.token_name = "PuntToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;
					}
				}
			}
			else if (*list == 'R')
			{
				counter++;
				cout << "\nPRToken";
				new_entry.token_name = "PRToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
			}
			else if (*list == 'C')
			{
				counter++;
				cout << "\nIfToken";
				new_entry.token_name = "IfToken";
				tokens.push_back(new_entry);
				code.erase(code.begin(), code.begin() + counter);
				return tokens;
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
						new_entry.token_name = "IfToken";
						tokens.push_back(new_entry);
						code.erase(code.begin(), code.begin() + counter);
						return tokens;					
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
				
				
				
				
				
				//insert into table//
				if (ST_SWITCH == true)
				{
					string check_id;
					
					for (int i = 0; i <= idName.size(); i++) //writing the idName to the check_id string
					{
						check_id += idName[i];
					}
					

					if (symbol_list.check_id_scope(symbols, check_id) != true) //check if ID is in scope, may need to use who table check since Python is based on globals
					{

						new_table_entry.name = check_id;
						symbol_counter++;
						if (new_table_entry.kind != "FUNC")
						{
							new_table_entry.kind = "VAR";
							if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
							{

								//need to figure out an if statement to handle arrays


								symbol_list.add_symbol(symbols, new_table_entry);
								symbol_list.print_symbol(symbols);
								cin.get();
								new_table_entry.name = "EMPTY";
								new_table_entry.kind = "EMPTY";
								new_table_entry.type = "EMPTY";
								new_table_entry.size = 1;
								symbol_counter = 0;
							}
						}


						else if (new_table_entry.kind == "FUNC")
						{
							if ((symbol_counter == 2) && (new_table_entry.kind != "EMPTY") && (new_table_entry.name != "EMPTY") && (new_table_entry.type != "EMPTY"))
							{

								//need to figure out an if statement to handle arrays


								symbol_list.add_symbol(symbols, new_table_entry);
								////symbol_list.print_symbol(symbols);
								new_table_entry.name = "EMPTY";
								new_table_entry.kind = "EMPTY";
								new_table_entry.type = "EMPTY";
								new_table_entry.size = 1;
								symbol_counter = 0;
							}
						}

					}
				}
				//---------------//

				
				
				
				
				
				
				
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
					new_entry.token_name = "ID_Array_Token";
					tokens.push_back(new_entry);
					code.erase(code.begin(), code.begin() + counter);
					return tokens;
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
			new_entry.token_name = "ErrorToken";
			tokens.push_back(new_entry);
			code.erase(code.begin(), code.begin() + counter);
			return tokens;
		}
}
//INSERT INTO SYMBOL TABLE//
void Scanner::insert_symbol_table(vector<TOKENS>& tokens)
{

	for (int i = 0; i < tokens.size(); i++)
	{

	}



}