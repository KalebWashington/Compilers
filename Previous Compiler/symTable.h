#ifndef SYMTABLE_H
#define SYMTABLE_H
//Group Symbol Table Project
// Jonathan Ringer
// Jeremy Vasseur
// Washing Kaleb
// Phillip Germagliotti

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include "doggieTypes.h"

//patch for c++11 equivalent function
template<typename T>
std::string to_string( const T& n);

/*
template<typename T>
struct optional {
T value;
bool hasValue;
} optional;
*/
template<typename T>
std::string to_string( const T& n);

struct Parameter {
public:
	std::string name;
	enum Type type;
	bool isArray;
	size_t numOfElements;
};

struct Record {
public:
	std::string name;
	Type type;
	size_t scope;
	size_t parentNdx;
	enum Kind kind;
	size_t size;
	size_t line_addr;        //function location
	size_t offset;           //local offset, for variable
	bool isParameter;
	bool isArray;
	size_t numOfElements;
};

//std::ostream& operator<<(std::ostream& os, Record r);

#define RECORD_ELEMENTS 5

//END Type definitions

class SymTable
{
private:
	std::vector<Record> records;   //"table" of records
	std::vector<size_t> offsets;      //will give an offset for a given scope level as the index
	size_t currentScope;         //determines which scope we append new records to
	void DecrementScope();    //used to handle offset information when leaving a scope
	void IncrementScope();    //inserts a new offset value
	void Add(Record r);
	size_t CurrentOffset();
	size_t mostCurrentFuncNdx;
	Record& MostCurrentFunc() {return records[mostCurrentFuncNdx]; }
	bool AddRecord(const std::string &name, Type type, Kind kind, bool isArray, bool isParameter, size_t numOfElems);

public:
	SymTable();
	~SymTable();

	bool IsEmpty();
	bool AddToStack(size_t);
	bool HasCurrent() { return mostCurrentFuncNdx != 0;}
	size_t CurrentScope();

	//returns true if it successfully added a record, returns false it a record already exist
	bool AddFunction(const std::string &name, Type type);
	bool SetCurrentFuncsName( std:: string);
	bool SetCurrentFuncsLocation(size_t location);

	bool AddVariable(const std::string &name, Type type);

	//add an array
	bool AddArray(const std::string &name, Type type, size_t num);

	//Adds a parameter to the most current declared function, will error if still in global scope
	bool AddParameter(const std::string &name, Type type, bool, size_t);

	//finds the most recent function with the given name, then returns the size of all parameters and local variables.
	//returns -1 if records could not be found
	size_t StackSize(const std::string &name) const;
	size_t MostCurrentStackSize();

	//returns the number of parameters for the most recent function
	size_t NumOfParameters(const std::string &name);

	//record name + scope is used to identify a given record
	bool RecordExists(const std::string &name) const;
	bool RecordExists(const std::string &name, size_t scope) const;

	Record FindRecord(const std::string &name) const;

	Record FindRecord(const std::string &name, Kind kind) const;

	Record FindRecord(const std::string &name, size_t scope) const;

	//will return true if it successfully removed
	//not sure where this method to be useful, because individual records wouldnt fall out of scope.... oh well
	//bool RemoveLast();

	//deletes all records at the top level scope
	void ReturnToPreviousScope();

	//returns record table with aligned columns
	std::string AlignedTableString();
};

#endif
