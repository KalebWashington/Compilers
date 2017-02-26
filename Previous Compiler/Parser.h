#ifndef PARSER_H
#define PARSER_H

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include "scanner.h"
#include "tokens.h"
#include "symTable.h"
#include "doggieTypes.h"
#include "Interpreter.h"
#include "codegen.h"
#include <iostream>
#include <string>
#include <vector>

class Parser
{
private:
	Scanner s;
	SymTable table;
	cg c;

	TokenInfo currentToken;
	TokenInfo GetNextToken();

	//this will compare the current token to t, if they are the same
	//it will grab the next token and return true. Otherwise 
	//returns false.
	bool Match(enum Token t);

	//Below are methods that try to consume tokens to match their definition
	bool BedLabel();
	bool Declarations(size_t&);
	bool Parameters(std::vector<Parameter>&);
	bool ArrayLHS(enum Type, std::string);
	bool Statements();
	bool Loop();
	bool Doghouse();
	bool NapTimeStatement();
	bool FeedPoodle();
	bool FeedCorgi();
	bool FeedYorkie();
	bool FeedDalmatian();
	bool ScratchLoop();
	bool FeedStatement();
	bool SniffStatement();
	/*bool SneezeStatement();*/
	bool SpeakStatement();
	bool SpeakPoodle();
	bool SpeakCorgi();
	bool SpeakYorkie();
	/*bool SpeakDachshund();*/
	bool SpeakDalmatian();
	bool RollOverLoop();
	bool ChaseLoop();
	bool Comparator();
	bool FunctionCall();
	//these methods will try to fulfill some type requirement or
	//the operation needs additional information to implement.
	bool FunctionDeclaration(enum Type, size_t&);
	bool Declaration(enum Type, size_t&);
	bool ArrayDeclaration(enum Type);
	bool VariableEnding(enum Type, std::string n);
	bool RHS(enum Type, std::string);
	bool RHSContinued(enum Type);
	//pass TypeStray if the type is irrelevant
	bool Expr6(enum Type);
	bool Expr5(enum Type);
	bool Expr4(enum Type);
	bool Expr3(enum Type);
	bool Expr2(enum Type);
	bool Expr1(enum Type);
	bool Expr0(enum Type);
	bool Expr(enum Type);
	bool Beds(enum Type);
	bool Bed(enum Type);
	bool BlockBeds(enum Type);
	bool Predicate();
	bool VariableDeclaration(enum Type, std::string);

	//these methods return the type which they were able to determine.
	bool Literal(enum Type&);
	bool ReturnType(enum Type&);
	bool Stray(enum Type&);
	bool Type(enum Type&);
	bool Poodle();
	bool Poodle(int&);  //checks for literal
	bool Dalmatian(enum Type&);
	bool Corgi(enum Type&);
	bool Yorkie(enum Type&);
	bool TypeDeclaration(enum Type&);
	bool Statement(size_t&);     //reads just a single line
	bool BlockStatement(size_t&);//reads-in a single line, or block
	bool BedStatements(size_t&); //reads in lines until a break

public:

	Parser(std::iostream *stream, std::ostream& out) : s(stream), c(out) { };
	void Run();
	void Flush();
};

#endif
