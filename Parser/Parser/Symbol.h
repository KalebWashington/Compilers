#ifndef Symbol_H_INCLUDED
#define Symbol_H_INCLUDED

//INCLUDES//
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
//#include <locale>               //don't believe we need this, going to comment out for now to ensure it isn't broken
//-------//


using namespace std;


class Symbol
{

public:

	//TABLE STRUCTURE//
	struct TABLE
	{
		string name;                   //string to hold the name of the ID
		string type;                   //string to save the type of symbol
		string kind;                   //string to save the kind of the symbol
		int size = 1;
		int memory = 0;
		int scope;
	};
	//-----------------//


	//ADD NEW ENTRY FUNCTION//
	void add_symbol(vector<TABLE>& symbols);


	//PRINT SYMBOL TABLE FUNCTION//
	void print_symbol(vector<TABLE>& symbols);


	//PRINT CURRENT SCOPE FUNCTION//
	void print_scope(vector<TABLE>& symbols);


	//CHECK FOR ID AT SCOPE FUNCTION//
	void check_id_scope(vector<TABLE>& symbols);


	//CHECK FOR ID IN TABLE//
	void check_id_table(vector<TABLE>& symbols);



	//EXAMINE ATTRIBUTES//
	void look_at_attrib(vector<TABLE>& symbols);


	//DELETE ID IN TABLE//
	void delete_id_table(vector<TABLE>& symbols);



	//SYMBOL TABLE MENU FUNCTION//
	void symbol_table_menu();

};

#endif