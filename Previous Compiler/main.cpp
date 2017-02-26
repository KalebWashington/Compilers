//Main file for doggie parser, essentially just a wrapper for the parser itself

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include "Parser.h"
#include "Interpreter.h"
#include <sstream>
#include <fstream>
#include "Parser.h"

using namespace std;

int main() {

  fstream f("test.ds");
  ofstream o("output.x");

  if (f)
  {
	Parser p(&f, o);
	 p.Run();
	 p.Flush();
  }
  else {
	  cout << "Couldn't find file" << endl;
  }
  f.close();
  o.close();
  f.open("output.x");
  //cout << f.rdbuf();
  cout << endl;
  cout << endl << "done parsing file." << endl;
  cout << "hit any key to continue....." << endl;
  char c;
  cin >> c;

  return 0;
}
