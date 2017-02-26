/*
AUTHORS: J. Robillard, C. Suggs, A. Thomas, J. Vasseur, K. Washington
PROGRAM: Scanner
CLASS: CSI465-01SC
Professor: Dr. Pokorny
DATE CODED: 2 / 20 / 2017
trsdt
------------------------------------------------------------------------------
USE: This program will serve as the scanner portion of our compiler.

NOTES: We had quite a few issues implementing RealLitTokens. This version is
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

struct TOKENS                                                                         //TOKENS struct; used to create a vector of this type that will hold the tokens generated.
{
	string token_name;                                                                //string to hold the name of the generated token
};

//PROTOTYPES//
void print_tokens(vector<TOKENS> tokens);                                             //function to print tokens generated. this will more than likely be removed as it was used for testing.

void elements_delete(vector<char>code, vector<TOKENS> tokens, int counter);           //function to delete the number of character from the code vector that was used to generate the token

void build_tokens(vector<char> code, vector<TOKENS> tokens);                          //function that will iterate through the code vector looking for tokens

void load_code(vector<char> code, vector<TOKENS> tokens);                             //function to read from the 'code.txt' file which holds the tokens to pass to the scanner

void initial();                                                                       //function that will call the build function, may be removed in the final compiler build
																					  //----------------------------------------//


																					  //MAIN FUNCTION//
int main()
{
	initial();                                                                        //calling the inital function to begin the process of generating tokens
}
//----------------//



//VODE VECTOR DELETE FUNCTION//
void elements_delete(vector<char>code, vector<TOKENS> tokens, int counter)           //accepting code and tokens vectors along with the count of how many characters composed the token
{
	code.erase(code.begin(), code.begin() + counter);                                //removing n amount of elements from the code vector; dependent on the counter length
	if (code.size() == 0)                                                            //if we've reached the end of the vector exit
	{
		exit;
	}
	build_tokens(code, tokens);                                                     //if we have more characters to process call build function with new code/tokens vector
}
//-------------------------//

//LOAD FUNCTION
void load_code(vector<char> code, vector<TOKENS> tokens)
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



	/* loop to print through the retrieved characters, was used for testing; will be removed in final version once we get everything in an acceptable working order

	cout << "The gathered data is: \n";

	for (int i = 0; i < code.size(); i++)
	{
	cout << code[i];
	}
	cout << "\n\nTest to see if we are getting all chars: " << count;
	cin.get();
	*/

	file.close();                                                                 //close code.txt file
	build_tokens(code, tokens);                                                   //sending our vectors to the build function to begin the token generation process
}
//----------------------------------------//



//PRINT FUNCTION//
void print_tokens(vector<TOKENS> tokens)                                         //printing our list of tokens. This will be replaced by a function the passes said tokens to the other components
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

/*
void errors(vector<char> code, int counter, &int linecounter)
{
counter++;
advance(list, 1);
cout << "\nErrorToken found on line: " << linecounter << "\n";
new_entry.token_name = "ErrorToken";
tokens.push_back(new_entry);
elements_delete(code, tokens, counter);
}
*/


//TOKEN BUILDER FUNCTION//
void build_tokens(vector<char> code, vector<TOKENS> tokens)                    //accepting code and token vectors for iteration and inserting
{
	int counter = 0;                                                           //counter to count how far into the code vector we go before generating a token
	static int linecounter = 1;                                                //used to print what line an error was generated on   
	auto list = code.begin();                                                  //iterator to be used for looking through the code vector
	TOKENS new_entry;                                                          //creating variable of type TOKENS that will hold our generated token



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
				new_entry.token_name = "AssignToken";
				tokens.push_back(new_entry);                                 //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);                      //call delete function to remove the characters that consituted the token    

			}
			else if (*list == ')')
			{
				counter++;
				new_entry.token_name = "DecrToken";
				tokens.push_back(new_entry);								//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    

			}
			else if (*list == '(')
			{
				counter++;
				new_entry.token_name = "IncrToken";
				tokens.push_back(new_entry);								//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    

			}
			else
			{
				counter++;
				advance(list, 1);                                                           //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);								//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
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
					new_entry.token_name = "LParenToken";
					tokens.push_back(new_entry);										//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
				}
				else
				{
					counter++;
					advance(list, 1);                                                 //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);									//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
				}

			}
			else if (*list == 'R')
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				if (*list == '#')
				{
					counter++;
					new_entry.token_name = "RParenToken";
					tokens.push_back(new_entry);									//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
				}
				else
				{
					counter++;
					advance(list, 1);                                               //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);									//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
				}
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);										//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
			}
		}
		//-----------------//


		//subtoken//
		else if (code[0] == ')')                                                             //if statements to determine what tokens, if any, exist
		{
			counter++;
			new_entry.token_name = "SubToken";
			tokens.push_back(new_entry);													//push the generated token into the tokens vector
			elements_delete(code, tokens, counter);											//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "AndToken";
				tokens.push_back(new_entry);											//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);									//call delete function to remove the characters that consituted the token    
			}
			else
			{
				counter++;
				advance(list, 1);                                                       //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);										//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "NegateToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}
			else
			{
				counter++;
				advance(list, 1);                                               //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "AddToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}
			else if (*list == 'M')
			{
				counter++;
				new_entry.token_name = "StringEscToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}
			else
			{
				counter++;
				advance(list, 1);                                                    //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);										//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "ArrayDefToken";
				tokens.push_back(new_entry);											//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);									//call delete function to remove the characters that consituted the token    
			}
			else
			{
				counter++;
				advance(list, 1);                                                     //advance in the list by 1 
				cout << "\nErrorToken found on line: " << linecounter << "\n";
				new_entry.token_name = "ErrorToken";
				tokens.push_back(new_entry);										//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
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
								new_entry.token_name = "HexToken";
								tokens.push_back(new_entry);									//push the generated token into the tokens vector
								elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
							}
							else
							{
								counter++;
								advance(list, 1);                                               //advance in the list by 1 
								cout << "\nErrorToken found on line: " << linecounter << "\n";
								new_entry.token_name = "ErrorToken";
								tokens.push_back(new_entry);									//push the generated token into the tokens vector
								elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
							}
						}
						else
						{
							counter++;
							advance(list, 1);                                                  //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);										//push the generated token into the tokens vector
							elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                        //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);											//push the generated token into the tokens vector
						elements_delete(code, tokens, counter);									//call delete function to remove the characters that consituted the token    
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                       //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);											//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);									//call delete function to remove the characters that consituted the token    
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
				advance(list, 1);                                                     //advance in the list by 1 
				if (isalpha(*list) || isalnum(*list))
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
							new_entry.token_name = "CharLitToken";
							tokens.push_back(new_entry);							//push the generated token into the tokens vector
							elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    

						}
						else
						{
							counter++;
							advance(list, 1);                                              //advance in the list by 1 
							cout << "\nErrorToken found on line: " << linecounter << "\n";
							new_entry.token_name = "ErrorToken";
							tokens.push_back(new_entry);								//push the generated token into the tokens vector
							elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
						}
					}
					else
					{
						counter++;
						advance(list, 1);                                                 //advance in the list by 1 
						cout << "\nErrorToken found on line: " << linecounter << "\n";
						new_entry.token_name = "ErrorToken";
						tokens.push_back(new_entry);									//push the generated token into the tokens vector
						elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
					}
				}
				else
				{
					counter++;
					advance(list, 1);                                                     //advance in the list by 1 
					cout << "\nErrorToken found on line: " << linecounter << "\n";
					new_entry.token_name = "ErrorToken";
					tokens.push_back(new_entry);									     //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);								//call delete function to remove the characters that consituted the token    
				}
			}

			else if (isalpha(*list) || isalnum(*list))                                   //stringlit else if statement
			{
				counter++;
				while (*list != ']')
				{
					counter++;
					advance(list, 1);												    //advance in the list by 1 
				}
				new_entry.token_name = "StringLitToken";
				tokens.push_back(new_entry);											//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);									//call delete function to remove the characters that consituted the token    
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
				counter--;
				new_entry.token_name = "IntToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}
			else if (isReal == true)
			{
				counter--;
				new_entry.token_name = "RealLitToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
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
			if (*list == 'G')
			{
				counter++;
				new_entry.token_name = "TrueToken";
				tokens.push_back(new_entry);                                   //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    

			}
			else if (*list == 'N')
			{
				counter++;
				advance(list, 1);                                              //advance in the list by 1 
				if (*list == 'G')
				{
					counter++;
					new_entry.token_name = "FalseToken";
					tokens.push_back(new_entry);                              //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
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
					new_entry.token_name = "DivToken";
					tokens.push_back(new_entry);                          //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "EOLToken";
				tokens.push_back(new_entry);                       //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
						new_entry.token_name = "RBlockToken";
						tokens.push_back(new_entry);                 //push the generated token into the tokens vector
						elements_delete(code, tokens, counter);		//call delete function to remove the characters that consituted the token    
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
						new_entry.token_name = "LBlockToken";
						tokens.push_back(new_entry);						 //push the generated token into the tokens vector
						elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "PointerToken";
				tokens.push_back(new_entry);                                    //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "EqToken";
				tokens.push_back(new_entry);                                //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
			}

			else if (*list == 'L')
			{
				counter++;
				new_entry.token_name = "LessToken";
				tokens.push_back(new_entry);                              //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);					  //call delete function to remove the characters that consituted the token    
			}

			else if (*list == 'E')
			{
				counter++;
				new_entry.token_name = "LessThanOrEqToken";
				tokens.push_back(new_entry);                             //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);					 //call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "GreaterThanOrEqToken";
				tokens.push_back(new_entry);                                    //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}

			else if (*list == 'W')
			{
				counter++;
				new_entry.token_name = "GreaterToken";
				tokens.push_back(new_entry);                                  //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
			}
		}
		//------------------------------//


		// Graph 3 ends, start Graph 4//
		//LMultiLineComment/Or Token//
		else if (code[0] == '/')                                            //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);												//advance in the list by 1 
			if (*list == '@')
			{
				counter++;
				new_entry.token_name = "LMultiLineCommentToken";
				tokens.push_back(new_entry);                                  //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
			}

			else if (*list == 'B')
			{
				counter++;
				advance(list, 1);                                        //advance in the list by 1 
				if (*list == '/')
				{
					counter++;
					new_entry.token_name = "OrToken";
					tokens.push_back(new_entry);                        //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
				}
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
				new_entry.token_name = "RMultiLineCommentToken";
				tokens.push_back(new_entry);                                     //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
			}

			else if (code[0])
			{
				while (code[0] != '\n')
				{
					counter++;
					advance(list, 1);                                            //advance in the list by 1 
				}
				new_entry.token_name = "SingleLineToken";
				tokens.push_back(new_entry);                                    //push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
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
					new_entry.token_name = "WhileToken";
					tokens.push_back(new_entry);                                //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
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
				advance(list, 1);                                      //advance in the list by 1 
				if (*list == 'B')
				{
					counter++;
					new_entry.token_name = "CaseToken";
					tokens.push_back(new_entry);                        //push the generated token into the tokens vector
					elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "MultiToken";
				tokens.push_back(new_entry);							//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    
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
					new_entry.token_name = "ElseToken";
					tokens.push_back(new_entry);						//push the generated token into the tokens vector
					elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "RealDecToken";
				tokens.push_back(new_entry);									//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);							//call delete function to remove the characters that consituted the token    
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
							new_entry.token_name = "VoidDecToken";
							tokens.push_back(new_entry);						//push the generated token into the tokens vector
							elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
								tokens.push_back(new_entry);						//push the generated token into the tokens vector
								elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
							}
						}
					}
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
								new_entry.token_name = "StringDecToken";
								tokens.push_back(new_entry);						//push the generated token into the tokens vector
								elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
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
						new_entry.token_name = "BoolDecToken";
						tokens.push_back(new_entry);							//push the generated token into the tokens vector
						elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    
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
						new_entry.token_name = "ForToken";
						tokens.push_back(new_entry);						//push the generated token into the tokens vector
						elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
					}
				}

				else if (*list == 'O')
				{
					counter++;
					advance(list, 1);									//advance in the list by 1 
					if (*list == 'N')
					{
						counter++;
						new_entry.token_name = "CharDecToken";
						tokens.push_back(new_entry);					//push the generated token into the tokens vector
						elements_delete(code, tokens, counter);			//call delete function to remove the characters that consituted the token    
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
				new_entry.token_name = "DerefToken";
				tokens.push_back(new_entry);								//push the generated token into the tokens vector
				elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
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
								new_entry.token_name = "SwitchToken";
								tokens.push_back(new_entry);						//push the generated token into the tokens vector
								elements_delete(code, tokens, counter);				//call delete function to remove the characters that consituted the token    
							}
						}
					}
				}
			}
		}
		//----------------------------------//

		//Graph 5 ends//

		// MISC Functions //
		//newline character//
		else if (code[0] == '\n')                                         //if statements to determine what tokens, if any, exist
		{
			counter++;
			linecounter++;
			advance(list, 1);											//advance in the list by 1 
			elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
		}
		//-------------------//

		//white space character//
		else if (code[0] == ' ')                                          //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);											//advance in the list by 1 
			elements_delete(code, tokens, counter);						//call delete function to remove the characters that consituted the token    
		}
		//-------------------//

		//ID Token//
		else if ((code[0] > 'a') && (code[0] < 'z'))                  //if statements to determine what tokens, if any, exist
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			new_entry.token_name = "ID_Token";
			tokens.push_back(new_entry);							//push the generated token into the tokens vector
			elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    
		}
		//------------//



		else                                                        //else that notifies the user that an error has been encountered
		{
			counter++;
			advance(list, 1);										//advance in the list by 1 
			cout << "\nErrorToken found on line: " << linecounter << " error is: " << code[0] << "\n";
			new_entry.token_name = "ErrorToken";
			tokens.push_back(new_entry);							//push the generated token into the tokens vector
			elements_delete(code, tokens, counter);					//call delete function to remove the characters that consituted the token    
		}
	}


	else                                                         //else statement to execute if we've reached the end of our code vector
	{
		print_tokens(tokens);                                    //send the tokens list to the print function
	}
}

//INITIAL FUNCTION//
void initial()
{
	cout << "This program will handle the scanner functions of our compiler.\n--PRESS ENTER TO CONTINUE--\n";
	cin.get();                               //pausing the program before execution
	vector<char> working_code;               //vector to hold the characters read in from the input file
	vector<TOKENS> tokens;                   //vector to hold the tokens that we generate
	load_code(working_code, tokens);         //call load_code function to begin reading in the code
}
//---------------//
//--END PROGRAM--//