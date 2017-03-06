#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "Scanner.h"
#include "Symboltable.h"
#include "Parser.h"

using namespace std;

struct TOKENS
{
	string token_name;
};

int main()
{
	int count = 0;                                                                  //counter to assist in reading from the inFile
	int i = 0;
	vector<char> code;
	char ch;                                                                        //character to temporarily hold the character retrieved from the code.txt inFile
	fstream inFile, outFile;
	
	
	inFile.open("code.txt", ios::in);												//ifstream for the inFile we'll be using to read from

	if (!inFile)                                                                      //if we can't open the inFile print a warning and exit
	{
		cout << "\n--Could not open inFile--\n--Press Enter to exit--\n";
		cin.get();
		exit(EXIT_FAILURE);
	}

	//outFile.open("output.txt", ios::out);												//ifstream for the inFile we'll be using to read from



	ch = inFile.peek();
	while (ch != EOF)                                                              //if we aren't at the end of the inFile, do this
	{
		ch = inFile.get();                                                           //retrieving the character from the inFile
		code.push_back(ch);                                                        //pushing the character into the vector
	}

	Parser p(code);//send char vector to Parser
	p.scannerRun();
	
	code = p.sendCharVector();

	cout << "this is size of code from main: " << code.size() << endl;

	ofstream textout("output.txt", ios::out);
	textout.write((const char*)&code[0], code.size()-1);
	
	inFile.close();                                                                 //close code.txt inFile
	textout.close();

	cin.get();
	return 0;
}