//Unit Test File

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include <sstream>
#include "scanner.h"
#include "QUnit.hpp"

using namespace std;

int main()
{
  QUnit::UnitTest qunit(std::cerr, QUnit::normal);

  stringstream ss;
  Scanner s(&ss);

  TokenInfo t;
  int tmp;
  for (int i = 1; i < NUM_OF_TOKENS; ++i) {
    if (i == StringLitToken || i == CharLitToken || i == VoidToken || i == CharToken || i == StringToken || i == BoolToken)
      continue;
    ss.clear();
    ss << lexeme((Token)i);
    ss.flush();
    cout << lexeme((Token)i) << " pushed on" << endl;
    t = s.NextToken();
    tmp = (int)t.token;
    //cout << tmp << ", " <<i << endl;
    QUNIT_IS_EQUAL(tmp, i);
    cout << t.value << endl;
    //cout << "remaining: " << ss<<endl;
    cout << endl;
    ss.str(std::string(""));
    ss.clear();

  }


  return 0;
}

