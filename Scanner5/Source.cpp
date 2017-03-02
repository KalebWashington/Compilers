/*
AUTHORS: J. Robillard, C. Suggs, A. Thomas, J. Vasseur, K. Washington
PROGRAM: Scanner
CLASS: CSI465-01SC
Professor: Dr. Pokorny
DATE CODED: 2 / 20 / 2017
------------------------------------------------------------------------------
USE: This program will serve as the scanner portion of our compiler.

NOTES: 

3/1
We ran into some issues with stack overflow errors. After some reading we discovered
that the IDE limits memory use when in 'debug' mode, we remedied this error by switching to
'release' mode. Those who run this will have to ensure they also run the program
in release mode in order for the program to function correctly.

There were also some typos in the programs we submitted, which resulted in the scanner
to have additional issues. Those typos have also been corrected.

2/20
We had quite a few issues implementing RealLitTokens. This version is
finicky when dealing with real numbers, however, we hope to remedy this issue
as we move forward and begin wrapping up the compiler, as we are aware this
will reduce the capability of what the compiler is able to achieve.
Aside from that issue we were able to produce a scanner that will hopefully
play nice with the other components of the compiler.
-----------------------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//PROTOTYPES//

void elements_delete(vector<char>code, int counter);

void build_tokens(vector<char> code);

void load_code(vector<char> code);                             //function to read from the 'code.txt' file which holds the tokens to pass to the scanner

void initial();                                                                       //function that will call the build function, may be removed in the final compiler build
																					  //----------------------------------------//
																					  //MAIN FUNCTION//
int main()
{
	initial();                                                                        //calling the inital function to begin the process of generating tokens
}
//----------------//

//VODE VECTOR DELETE FUNCTION//
void elements_delete(vector<char>code, int counter)           //accepting code and tokens vectors along with the count of how many characters composed the token
{
	code.erase(code.begin(), code.begin() + counter);                                //removing n amount of elements from the code vector; dependent on the counter length
	if (code.size() == 0)                                                            //if we've reached the end of the vector exit
	{
		exit;
	}
	build_tokens(code);                                                     //if we have more characters to process call build function with new code/tokens vector
}
//-------------------------//

//LOAD FUNCTION
void load_code(vector<char> code)
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
	build_tokens(code);                                                   //sending our vectors to the build function to begin the token generation process
}
//----------------------------------------//


//TOKEN BUILDER FUNCTION//
void build_tokens(vector<char> code)                    //accepting code and token vectors for iteration and inserting
{
	int counter = 0;                                                           //counter to count how far into the code vector we go before generating a token
	static int linecounter = 1;                                                //used to print what line an error was generated on   
	auto list = code.begin();                                                  //iterator to be used for looking through the code vector



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
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    

			}
			else if (*list == ')')
			{
				counter++;
				cout << "\nDecrToken";
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    

			}
			else if (*list == '(')
			{
				counter++;
				cout << "\nIncrToken";
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    

			}
			else
			{
				counter++;
				advance(list, 1);                                                           //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
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
					elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
				}
				else
				{
					counter++;
					advance(list, 1);                                                 //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
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
					elements_delete(code, counter);
				}
				else
				{
					counter++;
					advance(list, 1);                                               //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					elements_delete(code, counter);
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
			}
		}
		//-----------------//


		//subtoken//
		else if (code[0] == ')')                                                             //if statements to determine what tokens, if any, exist
		{
			counter++;
			cout << "\nSubToken";
			elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else if (*list == 'M')
			{
				counter++;
				cout << "\nStringEscToken";
				elements_delete(code, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                     //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
								elements_delete(code, counter);
							}
							else
							{
								counter++;
								advance(list, 1);                                               //advance in the list by 1 
								cout << "\nErrorToken found on line: " << linecounter << "\n";
								elements_delete(code, counter);
							}
						}
						else
						{
							counter++;
							advance(list, 1);                                                  //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							elements_delete(code, counter);
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						elements_delete(code, counter);
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                       //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					elements_delete(code, counter);
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
								elements_delete(code, counter);
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
							elements_delete(code, counter);
						}
						else
						{
							counter++;
							advance(list, 1);                                              //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							elements_delete(code, counter);
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                 //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						elements_delete(code, counter);
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                     //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					elements_delete(code, counter);
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
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else if (isReal == true)
			{
				cout << "\nRealLitToken";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else if (*list == 'G')
			{
				counter++;
				cout << "\nTrueToken";
				elements_delete(code, counter);
			}
			else if (*list == 'N')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'G')
				{
					counter++;
					cout << "\nFalseToken";
					elements_delete(code, counter);
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
					elements_delete(code, counter);
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
				elements_delete(code, counter);
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
						elements_delete(code, counter);
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
						elements_delete(code, counter);
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
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}

			else if (*list == 'L')
			{
				counter++;
				cout << "\nLessToken";
				elements_delete(code, counter);
			}

			else if (*list == 'E')
			{
				counter++;
				cout << "\nLessThanOrEqToken";
				elements_delete(code, counter);
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}

			else if (*list == 'W')
			{
				counter++;
				cout << "\nGreaterToken";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}

			else if (*list == 'B')
			{
				counter++;
				advance(list, 1);                                        //advance in the list by 1 
				if (*list == '/')
				{
					counter++;
					cout << "\nOrToken";
					elements_delete(code, counter);
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                 //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				elements_delete(code, counter);
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
				elements_delete(code, counter);
			}
			else if (*list != '\n')
			{
				while (*list != '\n')
				{
					counter++;
					advance(list, 1);                                            //advance in the list by 1 
				}
				cout << "\nSingleLineToken";
				elements_delete(code, counter);
			}
			else if (*list == '/')
			{
				counter++;
				cout << "\nRMultiLineCommentToken";
				elements_delete(code, counter);
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
					elements_delete(code, counter);
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
						elements_delete(code, counter);
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
							elements_delete(code, counter);
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
				elements_delete(code, counter);
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
					elements_delete(code, counter);
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
				elements_delete(code, counter);
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
							elements_delete(code, counter);
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
											elements_delete(code, counter);
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
								elements_delete(code, counter);
							}
						}
					}
				}
				else if (*list == 'L')
				{
					counter++;
					cout << "\nCHLToken";
					elements_delete(code, counter);
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
								elements_delete(code, counter);
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
						elements_delete(code, counter);
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
						elements_delete(code, counter);
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
						elements_delete(code, counter);
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
				elements_delete(code, counter);
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
								elements_delete(code, counter);
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
						cout << "\nPlayToken";
						elements_delete(code, counter);
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
						elements_delete(code, counter);
					}
				}
			}
			else if (*list == 'R')
			{
				counter++;
				cout << "\nPRToken";
				elements_delete(code, counter);
			}
			else if (*list == 'C')
			{
				counter++;
				cout << "\nIfToken";
				elements_delete(code, counter);
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
						elements_delete(code, counter);
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
										elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
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
			elements_delete(code, counter);
		}

		//-------------------//

		//white space character//
		else if (code[0] == ' ')                                          //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);											//advance in the list by 1 
			elements_delete(code, counter);
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
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
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
					elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
				}
			}
			else if (code[counter] != '[')
			{
				cout << "\nID_Token";
				elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    
			}
		}
		//------------//



		else                                                        //else that notifies the user that an error has been encountered
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			cout << "\nErrorToken found on line: " << linecounter << " error is: " << code[0] << "\n";
			elements_delete(code, counter);                      //call delete function to remove the characters that consituted the token    

		}
	}


	else                                                         //else statement to execute if we've reached the end of our code vector
	{
		cin.get();                               //pausing the program before execution
	}
}

//INITIAL FUNCTION//
void initial()
{
	cout << "This program will handle the scanner functions of our compiler.\n--PRESS ENTER TO CONTINUE--\n";
	vector<char> working_code;               //vector to hold the characters read in from the input file
	load_code(working_code);         //call load_code function to begin reading in the code
}
//---------------//
//--END PROGRAM--//
