#include "Symbol.h" //including SymbolTable functions
#include "Scanner.h" //including Scanner functions
#include "Parser.h"


#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm>



//function to copy token vector-probably won't need this, we'll keep it for now//
void duplicator(vector<Scanner::TOKENS>& scanner_tokens, vector<Parser::TOKENS>& parser_tokens)
{
	for (int i = 0; i < scanner_tokens.size(); i++)
	{
		Parser::TOKENS new_entry;
		new_entry.token_name = scanner_tokens.at(i).token_name;
		parser_tokens.push_back(new_entry);

	}
}
//




//INT MAIN//
int main()
{

	Scanner scanner;
	Symbol symbols;
	Parser parser;
	

	vector<Symbol::TABLE> symbol_table;

	vector<char> working_code;               
	vector<Scanner::TOKENS> tokens;
	//vector<Parser::TOKENS> parser_tokens;
	scanner.load_code(working_code, tokens);
	
	//duplicator(scanner_tokens, parser_tokens);  
	

	//for testing
	//cout << "\nscanner size: "<<scanner_tokens.size()<<"\n";
	//cout << "\nparser size: " << parser_tokens.size() << "\n";
	
	

	
	parser.match(tokens);
	
	
	



	
	
	
	
	
	
	



	system("pause");


	return 0;
}