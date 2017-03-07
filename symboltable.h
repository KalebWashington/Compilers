
#ifndef Symboltable_H_INCLUDED
#define Symboltable_H_INCLUDED


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>




using namespace std;

//TABLE STRUCTURE//




class Symboltable
{
public:
	struct TABLE
	{
		string name="EMPTY";                   //string to hold the name of the ID
		string type="EMPTY";                   //string to save the type of symbol
		string kind="EMPTY";                   //string to save the kind of the symbol
		int size = 1;
		int memory = 0;
		int scope;
	};
	//-----------------//


	void add_symbol(vector<Symboltable::TABLE>& symbols, Symboltable::TABLE & new_table_entry);

	void print_symbol(vector<Symboltable::TABLE>& symbols);

	bool check_id_scope(vector<Symboltable::TABLE>& symbols, string check);

	void check_id_table(vector<Symboltable::TABLE>& symbols);


};

#endif#