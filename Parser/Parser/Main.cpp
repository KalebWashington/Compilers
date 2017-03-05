#include "Symbol.h" //including SymbolTable functions
#include "Scanner.h" //including Scanner functions


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

//using namespace std;


//just testing things at this point
int main()
{

	Scanner input_code;
	Symbol symbols;

	vector<Symbol::TABLE> symbol_table;

	vector<char> working_code;               
	vector<Scanner::TOKENS> tokens;                 

	input_code.load_code(working_code, tokens);
	
	cout << "\n\n\n"<<tokens.at(2).token_name<<"\n\n"; //testing to see if we can reach the tokens


	
	
	
	
	
	//testing
	
	//symbols.add_symbol(symbol_table);
	
	
	//symbols.print_scope(symbol_table);
	



	system("pause");


	return 0;
}