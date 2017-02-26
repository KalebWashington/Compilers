//Unit Test File

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include <sstream>
#include "QUnit.hpp"
#include "symTable.h"
#include "doggieTypes.h"

using namespace std;

int main()
{
  QUnit::UnitTest qunit(std::cerr, QUnit::normal);

  SymTable st;
  const Record *r;

  QUNIT_IS_EQUAL(st.StackSize("a"), 0);

  QUNIT_IS_FALSE(st.RecordExists("a"));
  st.AddVariable("a", TypePoodle);

  QUNIT_IS_TRUE(st.RecordExists("a"));

  r = st.FindRecord("a");

  QUNIT_IS_EQUAL(r->scope, 0);

  st.AddFunction("b", TypePoodle);
  st.AddVariable("a", TypePoodle);
  st.AddVariable("c", TypePoodle);
  st.AddVariable("d", TypePoodle);
  st.AddVariable("e", TypePoodle);
  st.AddVariable("f", TypePoodle);
  r = st.FindRecord("a");
  QUNIT_IS_EQUAL(r->scope, 1);
  QUNIT_IS_FALSE(st.AddVariable("a", TypePoodle));

  st.ReturnToPreviousScope();

  cout << st.AlignedTableString() << endl;
  st.AddVariable("d", TypePoodle);
  st.AddFunction("c", TypePoodle);
  st.AddParameter("param1", TypeDalmatian, false, 1);
  cout << st.AlignedTableString() << endl;
  return 0;
}

