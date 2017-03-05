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
#include "Symbol.h"
#include "Parser.h"

struct TOKENS
{
	string token_name;
};



//VODE VECTOR DELETE FUNCTION//
void Scanner::elements_delete(vector<char>code, vector<TOKENS>& tokens, int counter)           //accepting code and tokens vectors along with the count of how many characters composed the token
{
	code.erase(code.begin(), code.begin() + counter);                                //removing n amount of elements from the code vector; dependent on the counter length
	if (code.size() == 0)                                                            //if we've reached the end of the vector exit
	{
		exit;
	}
	build_tokens(code,tokens);                                                     //if we have more characters to process call build function with new code/tokens vector
}
//-------------------------//

//LOAD FUNCTION
void Scanner::load_code(vector<char> code, vector<TOKENS>& tokens)
{
	int count = 0;                                                                  //counter to assist in reading from the file
	char ch;                                                                        //character to temporarily hold the character retrieved from the code.txt file
	ifstream file("code.txt");                                                      //ifstream for the file we'll be using to read from

	if (!file)                                                                      //if we can't open the file print a warning and exit
	{
		cout << "\n--Could not open file--\n--Press Enter to exit--\n";
		cin.get();
		exit(EXIT_FAILURE);
	}

	ch = file.peek();                                                              //looking ahead in the file
	while (ch != EOF)                                                              //if we aren't at the end of the file, do this
	{
		ch = file.get();                                                           //retrieving the character from the file
		code.push_back(ch);                                                        //pushing the character into the vector
		count++;                                                                   //increment count, we may need this later on
		ch = file.peek();                                                          //looking at the next char in the file
	}

	file.close();                                                                 //close code.txt file
	build_tokens(code,tokens);                                                   //sending our vectors to the build function to begin the token generation process
}
//----------------------------------------//


//TOKEN BUILDER FUNCTION//
void Scanner::build_tokens(vector<char> code, vector<TOKENS>& tokens)                    //accepting code and token vectors for iteration and inserting
{
	int counter = 0;                                                           //counter to count how far into the code vector we go before generating a token
	static int linecounter = 1;                                                //used to print what line an error was generated on   
	auto list = code.begin();                                                  //iterator to be used for looking through the code vector
	TOKENS new_entry;


	if (code.size() > 0)                                                     //if the size of the vectore is greater than 0 begin looking for tokens
	{
		//GRAPH 1 START//
		//Assign/Decrement/Increment generator//
		if (code[0] == '-')
		{
			counter++;
			advance(list, 1);                                                //advance in the list by 1                                             
			if (*list == '-')                                                //if statements to determine what tokens, if any, exist
			{
				counter++;
				advance(list, 1);
				cout << "\nAssignToken";
				new_entry.token_name = "AssignToken";
				tokens.push_back(new_entry);
				elements_delete(code,tokens,counter);                      //call delete function to remove the characters that consituted the token    

			}
			else if (*list == ')')
			{
				counter++;
				cout << "\nDecrToken";
				new_entry.token_name = "DectToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
																			 //call delete function to remove the characters that consituted the token    

			}
			else if (*list == '(')
			{
				counter++;
				cout << "\nIncrToken";
				new_entry.token_name = "IncrToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    

			}
			else
			{
				counter++;
				advance(list, 1);                                                           //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
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
					cout << "\nLParenToken";
					new_entry.token_name = "LParenToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
				}
				else
				{
					counter++;
					advance(list, 1);                                                 //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);                     //call delete function to remove the characters that consituted the token    
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
					cout << "\nRParenToken";
					new_entry.token_name = "RParenToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
				else
				{
					counter++;
					advance(list, 1);                                               //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
			elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				new_entry.token_name = "AndToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
			else if (*list == 'M')
			{
				counter++;
				cout << "\nStringEscToken";
				new_entry.token_name = "StringEscToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                     //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
								elements_delete(code, tokens, counter);
							}
							else
							{
								counter++;
								advance(list, 1);                                               //advance in the list by 1 
								cout << "\nErrorToken found on line: " << linecounter << "\n";
								new_entry.token_name = "ErrorToken";
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
						else
						{
							counter++;
							advance(list, 1);                                                  //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);
							elements_delete(code, tokens, counter);
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                       //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
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
								elements_delete(code, tokens, counter);
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
							elements_delete(code, tokens, counter);
						}
						else
						{
							counter++;
							advance(list, 1);                                              //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);
							elements_delete(code, tokens, counter);
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                 //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                     //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else if (isReal == true)
			{
				cout << "\nRealLitToken";
				new_entry.token_name = "RealLitToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else if (*list == 'G')
			{
				counter++;
				cout << "\nTrueToken";
				new_entry.token_name = "TrueToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
					elements_delete(code, tokens, counter);
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
					elements_delete(code, tokens, counter);
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
				cout << "\nEOLToken";
				new_entry.token_name = "EOLToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
						cout << "\nRBlockToken";
						new_entry.token_name = "RBlockToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
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
						cout << "\nLBlockToken";
						new_entry.token_name = "LBlockToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'L')
			{
				counter++;
				cout << "\nLessToken";
				new_entry.token_name = "LessToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'E')
			{
				counter++;
				cout << "\nLessThanOrEqToken";
				new_entry.token_name = "LessThanOrEqToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}

			else if (*list == 'W')
			{
				counter++;
				cout << "\nGreaterToken";
				new_entry.token_name = "GreaterToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
					elements_delete(code, tokens, counter);
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
			}
			else if (*list == '/')
			{
				counter++;
				cout << "\nRMultiLineCommentToken";
				new_entry.token_name = "RMultiLineCommentToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
					elements_delete(code, tokens, counter);
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
						elements_delete(code, tokens, counter);
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
							elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
					elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
							cout << "\nVoidDecToken";
							new_entry.token_name = "VoidDecToken";
							tokens.push_back(new_entry);
							elements_delete(code, tokens, counter);
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
											elements_delete(code, tokens, counter);
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
								cout << "\nIntDecToken";
								new_entry.token_name = "IntDecToken";
								tokens.push_back(new_entry);
								elements_delete(code, tokens, counter);
							}
						}
					}
				}
				else if (*list == 'L')
				{
					counter++;
					cout << "\nDoToken";
					new_entry.token_name = "DoToken";
					tokens.push_back(new_entry);
					elements_delete(code, tokens, counter);
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
								elements_delete(code, tokens, counter);
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
						elements_delete(code, tokens, counter);
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
						elements_delete(code, tokens, counter);
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
						elements_delete(code, tokens, counter);
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
				elements_delete(code, tokens, counter);
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
								elements_delete(code, tokens, counter);
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
						cout << "\nFunctionToken";
						new_entry.token_name = "FunctionToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
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
						cout << "\nOutputToken";
						new_entry.token_name = "OutputToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
					}
				}
			}
			else if (*list == 'R')
			{
				counter++;
				cout << "\nInputToken";
				new_entry.token_name = "InputToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
			}
			else if (*list == 'C')
			{
				counter++;
				cout << "\nIfToken";
				new_entry.token_name = "IfToken";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);
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
						new_entry.token_name = "ReturnToken";
						tokens.push_back(new_entry);
						elements_delete(code, tokens, counter);
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
										cout << "\nMainToken";
										new_entry.token_name = "MainToken";
										tokens.push_back(new_entry);
										elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
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
																		//elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
			elements_delete(code, tokens, counter);
		}

		//-------------------//

		//white space character//
		else if (code[0] == ' ')                                          //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);											//advance in the list by 1 
			elements_delete(code, tokens, counter);
		}
		//-------------------//

		//ID Token//
		else if ((code[0] > 'a') && (code[0] < 'z'))                  //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);
			int a;
			while (*list > 48 && *list < 122)
			{
				counter++;
				advance(list, 1);
			}

			a = counter;

			if (counter < 4)
			{
				cout << "\nID_Token";
				new_entry.token_name = "ID_Token";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
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
					elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    
				}
			}
			else if (code[counter] != '[')
			{
				cout << "\nID_Token";
				new_entry.token_name = "ID_Token";
				tokens.push_back(new_entry);
				elements_delete(code, tokens, counter);                     //call delete function to remove the characters that consituted the token    
			}
		}
		//------------//



		else                                                        //else that notifies the user that an error has been encountered
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			cout << "\nErrorToken found on line: " << linecounter << " error is: " << code[0] << "\n";
			elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    

		}
	}


	else                                                         //else statement to execute if we've reached the end of our code vector
	{
		cin.get();                               //pausing the program before execution
	}
}







//INSERT INTO SYMBOL TABLE//

void Scanner::insert_symbol_table(vector<TOKENS>& tokens)
{

	for (int i = 0; i < tokens.size(); i++)
	{

	}



}









//PRINT FUNCTION--will be removed in final product. Just for testing.//
void Scanner::print_tokens(vector<TOKENS>& tokens)                                         //printing our list of tokens. This will be replaced by a function the passes said tokens to the other components
{
	cout << "\nGENERATED TOKENS\n";
	cout << "__________________________________________________________________\n\n";
	for (int i = 0; i < tokens.size(); i++)                                      //iterating through the tokens vector
	{
		cout << tokens.at(i).token_name << " ";                                  //print contents at the index
	}
	cout << "\n__________________________________________________________________\n";

	cout << "\n--PRESS ENTER TO EXIT--\n";

	cin.get();                                                                   //pausing for the user
}
//----------------------------------------//








//INITIAL FUNCTION//
void Scanner::initial()
{
	cout << "This program will handle the scanner functions of our compiler.\n--PRESS ENTER TO CONTINUE--\n";
	vector<char> working_code;               //vector to hold the characters read in from the input file
	vector<TOKENS> tokens;
	load_code(working_code,tokens);         //call load_code function to begin reading in the code
}
//---------------//
//--END PROGRAM--//
