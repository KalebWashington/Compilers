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



int main()
{
	
	Symbol test;
	
	vector<Symbol::TABLE> symbol_table;

	test.add_symbol(symbol_table);
	test.check_id_table(symbol_table);
	
	system("pause");


	return 0;
}