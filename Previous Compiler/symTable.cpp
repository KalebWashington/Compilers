//Group Symbol Table Project
// Jonathan Ringer
// Jeremy Vasseur
// Washing Kaleb
// Phillip Germagliotti

#include "symTable.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

std::ostream& operator<<(std::ostream& os, Record r)
{
 return os << r.name << " " << r.type << " " << r.scope;
}

template<typename T>
std::string to_string( const T& n)
{
  std::ostringstream stm;
  stm << n;
  return stm.str();
}


//push elements of a record size_to an array, so we can align columns later
static vector<string> prsize_tRecord(Record* const r) {
  vector<string> result;

  result.push_back(to_string(r->name));
  result.push_back(to_string(r->type));
  result.push_back(to_string(r->scope));
  result.push_back(to_string(r->size));
  result.push_back(to_string(r->kind));

  return result;
}

SymTable::SymTable()
{
  currentScope = 0;
  mostCurrentFuncNdx = 0;
}

SymTable::~SymTable() {};

size_t SymTable:: StackSize(const string &name) const {
  for (int i = this->records.size() - 1; i >= 0; i--) {
    if (records[i].name == name && records[i].kind == KindFunc) {
      //found record, now find variables declared at that scope
      size_t size = 0;
      size_t correctScope = records[i].scope + 1;
      for (size_t j = i + 1; j < records.size() && records[j].scope == correctScope; ++j)
        size += records[j].size;

      return size;
    }
  }

  //nothing was found, return false
  return 0;
}

bool SymTable::AddToStack(size_t size) 
{
  //cout << "adding " << size << endl;
  if (this->HasCurrent()) {
    MostCurrentFunc().size += size;
    return false;
  }
  return true;
}

	bool SymTable::SetCurrentFuncsName( std:: string newName)
	{
		MostCurrentFunc().name = newName;
		return false;
	}
bool SymTable::AddArray(const std::string &name, enum Type type, size_t num) 
{
  return AddRecord(name, type, KindVar, true, false, num);
}

bool SymTable::AddVariable(const std::string &name, enum Type type) 
{
  return AddRecord(name, type, KindVar, false, false, 1);
}

bool SymTable::AddParameter(const std::string &name, enum Type type, bool isArray, size_t numOfElements) {
  //cout << MostCurrentFunc().name << endl;
  if (mostCurrentFuncNdx != 0) 
    return AddRecord(name, type, KindVar, isArray, true, numOfElements);

  //most current scope was recently cleared... error
  return false;
}

bool SymTable::RecordExists(const string &name, size_t scope) const {
  for (int i = this->records.size() - 1; i >= 0; i--) {
    if (records[i].name == name && records[i].scope == scope)
      return true;
  }

  //nothing was found, return false
  return false;
}

//record name + scope is used to identify a given record
bool SymTable::RecordExists(const string &name) const {
  //iterate through and see if we can't find something by the correct name and scope
  for (int i = this->records.size() - 1; i >= 0; i--) {
    if (records[i].name == name)
      return true;
  }

  //nothing was found, return false
  return false;
}

Record SymTable::FindRecord(const string &name) const
{
  for (int i = records.size() - 1; i >= 0; --i)
    if (records[i].name == name)
      return records[i];

  Record a;
  //nothing was found, return default case
  return a;
}

Record SymTable::FindRecord(const string &name, Kind kind) const
{
  for (int i = records.size() - 1; i >= 0; i--)
    if (records[i].name == name && records[i].kind == kind)
      return records[i];

  Record a;
  //nothing was found, return default case
  return a;
}

Record SymTable::FindRecord(const string &name, size_t scope) const
{
  for (int i = records.size() - 1; i >= 0; i--)
    if (records[i].name == name && records[i].scope == scope)
      return records[i];

  Record a;
  //nothing was found, return default case
  return a;
}


//will return true if it successfully removed
//bool SymTable::RemoveLast() {
//
//  if (this->IsEmpty())
//    return false;
//
//  Record r = records[records.size() - 1];
//
//  //if we remove a function, we need to return to the previous scope
//  if (r.Kind() == KindFunc)
//    currentScope--;
//  offsets[currentScope] -= r.Size();
//
//  records.pop_back();
//
//  //nothing was found, return false
//  return true;
//}

bool SymTable::IsEmpty() {
  return records.size() < 1;
}

bool SymTable::AddFunction(const string &name, Type type)
{
  return AddRecord(name, type, KindFunc, false, false, 1);
}

//returns true if it successfully added a record, returns false it a record already exists
bool SymTable::AddRecord(const string &name, Type type, Kind kind, bool isArray, bool isParameter, size_t numOfElements = 1)
{
  Record r;
  //check to make sure that the id is unique
  if (RecordExists(name, currentScope))
    return false;

  r.isArray = isArray && kind == KindVar;
  r.isParameter = isParameter && kind == KindVar;
  r.name = name;
  r.type = type;
  r.parentNdx = mostCurrentFuncNdx;
  if (kind == KindVar){
    r.size = TypeSize(type) * numOfElements;
    r.offset = this->CurrentOffset();
    r.numOfElements = numOfElements;
    AddToStack(r.size);
  }
  else {
    r.size = 0;
    r.offset = 0;
  }

  r.scope = currentScope;
  r.kind = kind;
  this->Add(r);
  if (kind == KindFunc)
    mostCurrentFuncNdx =records.size() -1;

  //cout << "current:" <<  MostCurrentFunc().name << endl;
  //id is unique, add to table

  //increment scope if it was a function
  if (kind == KindFunc) {
    this->IncrementScope();
  }
  //if it was a variable, increase stack size of function

  //cout << this->AlignedTableString() << endl;
  return true;
}

size_t SymTable::CurrentOffset()
{
  //if there is no current entry, then start at 0
  if (offsets.size() == currentScope)
    offsets.push_back(0);
  //sanity check
  if (offsets.size() >= (size_t)currentScope)
    return this->offsets[currentScope];
  return 0;
}

void SymTable::Add(Record r)
{
  records.push_back(r);
  
  //sanity check
  if (offsets.size() <= (size_t)currentScope)
	  offsets.push_back(0);
  //increment offset for next element
  if (offsets.size() >= (size_t)currentScope)
    offsets[currentScope] += r.size;
}

//deletes all records at the top level scope
void SymTable::ReturnToPreviousScope()
{
  //cannot return from topmost level scope
  if (currentScope <= 0)
    return;

  //remove all records of the scope we are leaving
  for (int i = records.size() - 1; i >= 0; i--)
    if (records[i].scope == currentScope)
      records.pop_back();

  this->DecrementScope();
  //TODO most current func needs to be set to parent scope
}

bool SymTable::SetCurrentFuncsLocation(size_t location)
{
	MostCurrentFunc().size = location;
	return true;
}

size_t SymTable::CurrentScope()
{
	return currentScope;
}

size_t SymTable::MostCurrentStackSize()
{
	return MostCurrentFunc().size;
}

void SymTable::IncrementScope()
{
  ++currentScope;
  //make sure it has an offset value
  if (offsets.size() == currentScope)
    offsets.push_back(0);
  else
    offsets[currentScope] = 0;
}

//handles removal of a scope
void SymTable::DecrementScope()
{
  if (records.size() > 0 && currentScope > 0)
    offsets[currentScope--] = 0;
  if (HasCurrent())
    mostCurrentFuncNdx = MostCurrentFunc().parentNdx;
}

//returns record table with aligned columns
std::string SymTable::AlignedTableString() 
{
  vector< vector<string> > cells;
  size_t widths[8];                    //widths of the columns

  //header
  vector<string> header;
  header.push_back("Name");
  header.push_back("Type");
  header.push_back("Scope");
  header.push_back("Size");
  header.push_back("Kind");
  cells.push_back(header);

  //split records size_to cells
  for (vector<Record>::iterator it = records.begin(); it != records.end(); it++)
    cells.push_back(prsize_tRecord(&(*(it))));

  //find the greatest width in each column
  for (size_t i = 0; i < RECORD_ELEMENTS; ++i) {
    size_t w = 0;
    for (size_t j = 0; j < cells.size(); ++j) {
      size_t a =cells[j][i].length();
      w = a > w ? a : w;
    }
    widths[i] = w;
  }

  //set all cells in a given column to the same width
  for(size_t i = 0; i < RECORD_ELEMENTS; ++i) 
    for (size_t j = 0; j < cells.size(); ++j)
      cells[j][i].resize(widths[i],' ');

  //concat all the rows
  stringstream ss;
  for (size_t i = 0; i < cells.size(); ++i) {
    for(size_t j = 0; j < cells[i].size(); ++j)
      ss << cells[i][j] << "  ";
    ss << endl;
  }

  return ss.str();
}


