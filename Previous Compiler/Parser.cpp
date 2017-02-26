
//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti


#include "Parser.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace opcode;

int to_int(string &s)
{
	int result;
	stringstream ss;
	ss << s;
	ss >> result;
	return result;
}

template<typename T>
std::string to_string( const T &n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

TokenInfo Parser::GetNextToken()
{
	if (s.HasToken())
		currentToken = s.NextToken();
	return currentToken;
}

bool Parser::Yorkie(enum Type &t)
{
	Expr0(t);
	return false;
}

bool Parser::Corgi(enum Type &t)
{
	Expr0(t);
	return false;
}

bool Parser::Dalmatian(enum Type &t)
{
	Expr0(t);
	return false;
}

bool Parser::ArrayDeclaration(enum Type t)
{
	if (Match(ArrayDefToken))
	{
		if (currentToken.token == IntToken)
		{
			int num = to_int(currentToken.value);
			GetNextToken();
			if (Match(ArrayDefToken))
			{
				if (Match(EoLToken))
				{
					//TODO: add num records to symbol table
					return true;
				}
				//TODO handle else's
			}
		}
	}
	return false;
}

bool Parser::ArrayLHS(enum Type t, std::string name)
{
	if (Match(ArrayDefToken))
	{
		int arraySize = 0;

		//arrays cannot be dynamically allocated on the stack
		if (currentToken.token == IntToken)
		{
			int size = to_int(currentToken.value);

			table.AddArray(name, t, size);

			if (Match(ArrayDefToken))
			{

			}
		}
	}

	return false;
}

bool Parser::Poodle(int &value)
{
	//TODO emit code
	if(currentToken.token == IntToken) {
		int size = to_int(currentToken.value);
		GetNextToken();
		//TODO emit size
		c.Emit1(LDM4);
		c.Emit4(size);
		return true;
	}
	else if (currentToken.token == NameToken)
	{
		Record r = table.FindRecord(currentToken.value);
		if(r.type == TypePoodle) {
			//TODO emit code for finding record at specific scope
			c.Emit1(LDM2);
			c.Emit2(r.offset);
			//want to store the value to that location
			c.Emit1(LDLR4);

			return true;
		}
	}
	return false;
}

bool Parser::ReturnType(enum Type &returnType)
{
	bool parsedCorrectly = false;

	if (Stray(returnType))
	{
		c.Log("Type:Stray");
		returnType = TypeStray;
		parsedCorrectly = true;
	}
	else if (Type(returnType))
	{
		parsedCorrectly = true;
	}
	return parsedCorrectly;
}

//god help us
bool Parser::Doghouse()
{
	size_t s;
	if(Match(DefaultToken))
	{
		return true;
	}
	else if(BlockStatement(s))
	{
		return true;
	}
	else if(Match(BreakToken))
	{
		return true;
	}
	return false;

}
bool Parser::BedStatements(size_t &lines)
{
	size_t s, sum = 0;
	while (!Match(BreakToken))
	{
		if (Statement(s))
		{
			sum += s;
		}
		else
			return false;
	}
	lines = sum;
	return true;
}
bool Parser::BedLabel()
{
	if (Match(CaseToken))
	{
		if (Match(IntToken))
		{
			if (Match(BedEndToken))
			{
				return true;
			}
		}
	}
	return false;
}
bool Parser::Bed(enum Type t)
{
	size_t s;
	if(BedLabel())
	{
		if(BedStatements(s))
		{
			if(Match(BreakToken))
			{
				//TODO jump to end of switch statement
				c.Emit1(JMP);
				c.Emit2(s);
				//TODO build up address index array for switch statement

				return true;
			}
		}
	}
	return false;
}
bool Parser::Beds(enum Type t)
{
	if(Bed(t))
	{
		return true;
	}
	return false;
}
bool Parser::BlockBeds(enum Type t)
{
	if(Doghouse())
	{
		return true;
	}
	else if(Beds(t))
	{
		return true;
	}
	return false;
}
bool Parser::NapTimeStatement()
{
	enum Type t = TypeStray;
	if(Match(SwitchToken))
	{
		if(Expr(t))
		{
			//TODO save value on stack
			if(Match(LBlockToken))
			{
				if(BlockBeds(t))
				{

					//todo: everything

					return true;
				}
			}
		}
	}
	return false;
}

//done
bool Parser::Statement(size_t &lines)
{
	enum Type t = TypeStray;
	if(FeedStatement())
	{
		// TODO feed statement
	}
	else if(SpeakStatement())
	{
		// TODO speak statement
	}
	
	else if(Expr(TypeStray))
	{
		return true;
	}
	else if(Loop())
	{
		return true;
	}
	else if(SniffStatement())
	{
		return true;
	}
	else if(NapTimeStatement())
	{
		return true;
	}
	else if (ReturnType(t))
	{
		//function or variable
		size_t dontcare;
		this->Declaration(t, dontcare);
	}

	if (Match(EoLToken))
	{
		//hey!, end of a line, how cute
		return true;
	}
	return false;
}

bool Parser::BlockStatement(size_t &lines){
	size_t tmp, sum = 0;
	if(Match(LBlockToken))
	{
		c.Log(" Block (");
		while (!Match(RBlockToken))
		{
			Match(EoLToken);
			sum += Statement(tmp);
			Match(EoLToken);
		}
		c.Log(")");
		return true;
	}
	else if(Statement(lines))
	{
		return true;
	}

	return false;
}

//done
bool Parser:: Loop()
{
	if (RollOverLoop())
	{	
		return true;
	}
	else if (ChaseLoop())
	{
		return true;
	}
	else if(ScratchLoop())
	{
		return true;	
	}

	return false;

}

bool Parser::Stray(enum Type& t)
{
	if (Match(VoidToken))
	{
		t = TypeStray;
		return true;
	}
	return false;
}

bool Parser::Predicate()
{
	enum Type evaluated = TypeDalmatian;
	Expr(evaluated);
	return evaluated == TypeDalmatian;
}

bool Parser::Parameters(vector<Parameter>& params)
{
	enum Type t;

	if (Match(LParenToken))
	{
		do {
			if (Type(t))
			{
				if (currentToken.token == NameToken)
				{
					//we have a parameter
					Parameter p;
					p.type = t;
					p.name = currentToken.value;
					p.isArray = false;
					p.numOfElements = 1;

					params.push_back(p);
					GetNextToken();
				}
			}
		} while (Match(SeparatorToken));

		if (!Match(RParenToken)) {
			//error
			cout << "Expected closing bone, instead got " << currentToken.value;
			return false;
		}
		return true;
	}

	return false;
}

bool Parser::FunctionDeclaration(enum Type returnType, size_t& pcline)
{
	size_t size;
	//add this so we can add parameters to it
	vector<Parameter> params;
	if (Parameters(params))
	{
		c.Log(" Function ( Params: ");
		Match(RParenToken);

		if (currentToken.token == NameToken)
		{


			//set acces link
			//Record r =
			//function being declared
			table.AddFunction(currentToken.value, returnType);
			//make access link
			c.Emit1(PUSL);
			c.Emit1(STLR2);
			c.Emit2(table.MostCurrentStackSize());
			//push L again
			c.Emit1(PUSL);
			bool isMain = false;
			//check to see if it is the main function
			if (currentToken.value == "walk") {
				//this is the main function
				pcline = c.CurrentAddr();
				isMain = true;
			}

			//add all the parameters
			for (size_t i = 0; i < params.size(); ++i)
			{

				Parameter p = params[i];
				c.Log(p.name + ":" + to_string(p.type) + ",");
				table.AddParameter(p.name, p.type, p.isArray, p.numOfElements);
			}
			c.Log(" ) Name: " +  currentToken.value + " Body: (");
			GetNextToken();
			if (BlockStatement(size))
				return true;
			c.Log (" ) ) ");
			if (isMain)
			{
				//add halt instruction to gtfo
				c.Emit1(HALT);
			}
		}
	}
	return false;
}

bool Parser::Declaration(enum Type typeDeclared, size_t& pcline)
{
	c.Log(" Defined a " + to_string(typeDeclared) + " ");
	if (FunctionDeclaration(typeDeclared, pcline))
	{
		return true;
	}
	else if (currentToken.token == NameToken)
	{
		std::string name = currentToken.value;
		GetNextToken();
		VariableDeclaration(typeDeclared, name);
		return true;
	}
	return false;
}

bool Parser::VariableEnding(enum Type t, std::string name)
{
	//it was declared, we need enter the value
	table.AddVariable(name, t);
	if (Match(EoLToken))
	{
		c.Log(" End;");
		return true;
	}
	else if (RHS(t, name))
	{

		return true;
	}

	return false;
}

bool Parser::RHSContinued(enum Type t)
{
	if (Match(EoLToken))
	{
		c.Log("End of Line.\r\n");
		//ending previous declaration
		return true;
	}
	else if (Match(SeparatorToken))
	{
		c.Log(", ");
		if (currentToken.token == NameToken)
		{
			string name = currentToken.value;

			GetNextToken();
			//read in next
			VariableDeclaration(t, name);

			return true;
		}

	}

	return false;
}

//lil' helper
bool Parser::Match( enum Token t)
{
	if (currentToken.token == t)
	{
		GetNextToken();
		return true;
	}

	return false;
}


bool Parser::Literal(enum Type &t)
{
	if(currentToken.token == IntToken)
	{
		int val = to_int(currentToken.value);
		GetNextToken();
		c.Log(" (Int: " + to_string(val) + ")");
		//EMIT
		c.Emit1(LDM4);
		c.Emit4(val);

		return true;
	}
	else if(currentToken.token == CharToken)
	{
		char tmp;
		stringstream ss;
		ss << currentToken.value;
		ss >> tmp;
		GetNextToken();
		c.Log(" (Char: " + currentToken.value + ")");
		//EMIT
		c.Emit1(LDM1);
		c.Emit1(tmp);

		return true;
	}
	else if(currentToken.token == RealToken)
	{
		float tmp;
		stringstream ss;
		ss << currentToken.value;
		ss >> tmp;
		GetNextToken();
		string toPrint = to_string(tmp);
		c.Log(" (Float: " + toPrint + ")");
		//EMIT
		c.Emit1(LDM4);

		//convert this guy to an int, eh
		float f = tmp;
		int *i;
		i = (int *) &f;
		c.Emit4(*i);

		return true;
	}
	else if(currentToken.token == BoolToken)
	{
		char tmp;
		if (currentToken.value == "XX")
			tmp = 0;
		else
			tmp = 1;

		GetNextToken();
		string s = (tmp ? "OO" : "XX");
		c.Log(" (Char: " + s + ")");
		//EMIT
		c.Emit1(LDM1);
		c.Emit1(tmp);

		return true;
	}
	return false;
}

bool Parser::Type(enum Type &t)
{
	//if(Match(StringDecToken))
	//{
	//	return true;
	//}
	if(Match(IntDecToken))
	{
		t = TypePoodle;
		return true;
	}
	else if(Match(BoolDecToken))
	{
		t = TypeDalmatian;
		return true;
	}
	else if(Match(RealDecToken))
	{
		t = TypeCorgi;
		return true;
	}
	else if(Match(CharDecToken))
	{
		t = TypeYorkie;
		return true;
	}

	return false;
}

bool Parser::Expr0(enum Type t)
{
	if (Match(FetchToken))
	{
		c.Log ("Function (");
		if (FunctionCall())
		{
		}

		c.Log(")");

		return true;
	}
	else if (Match(LParenToken))
	{
		c.Log(" Expr ( ");
		if (Expr(t))
		{
			if (Match(RParenToken))
			{
				c.Log (" )");
				return true;
			}
			else 
				cout << "ERROR" << endl;

			return false;
		}

	}
	else if (currentToken.token == NameToken)
	{
		string name = currentToken.value;
		Record r = table.FindRecord(currentToken.value);
		GetNextToken();

		if (Match(ArrayDefToken))
		{
			c.Log(" Array[");
			//go to where this is delcared
			c.Emit1(PUSL);
			//dereference to where 
			for (size_t i = table.CurrentScope(); i > r.scope; ++i)
				c.Emit1(DER);
			if (Expr(TypePoodle))
			{

				if (Match(ArrayDefToken))
				{
					c.Log("]");
					size_t typesize = TypeSize(r.type);
					if (typesize == 4)
					{
						//find scope this is declared in
						//Find offset of value
						c.Emit2(LDM4);
						c.Emit4(4);
						c.Emit1(MUL);
					}

				}

			}
		}
		else 
		{
			c.Log (" NameToken: " + name + " ");
			c.Emit1(LDLR4);
			c.Emit2(r.offset);
		}

		return true;
	}
	else if (Literal(t))
	{

		return true;
	}

	return false;
}

bool Parser::Expr1(enum Type t)
{
	if (Match(NegateToken))
	{
		c.Log("Negate (");
		if (Expr0(t))
		{

		}
		c.Log(" )");

		//emit and code
		c.Emit1(NEG);
		return true;
	}
	else if (Match(IncrToken))
	{
		c.Log("Increment (");
		if (Expr0(t))
		{

		}
		c.Log(" )");

		c.Emit1(INC);
	}
	else
		return Expr0(t);

	return false;
}
bool Parser::Expr2(enum Type t)
{

	if (Expr1(t))
	{
		if (Match(MultToken))
		{
			c.Log (" <3 ");
			if (Expr2(t))
			{
			}

			//emit and code
			c.Emit1(MUL);
		}
		else if (Match(DivToken))
		{
			c.Log (" VV ");
			if (Expr2(t))
			{
			}

			//emit and code
			c.Emit1(DIV);
		}
		else if (Match(ModToken))
		{
			c.Log (" {} ");
			if (Expr2(t))
			{
			}

			//emit and code
			c.Emit1(MOD);
		}
		return true;
	}

	return false;
}

bool Parser::Expr3(enum Type t)
{
	if (Expr2(t))
	{
		if (Match(AddToken))
		{
			c.Log (" + ");
			if (Expr4(t))
			{

			}

			//emit and code
			c.Emit1(ADD);
		}
		else if (Match(SubToken))
		{
			c.Log (" - ");
			if (Expr4(t))
			{

			}

			//emit and code
			c.Emit1(SUB);
		}

		return true;
	}

	return false;

}
bool Parser::Expr4(enum Type t)
{
	if (Expr3(t))
	{
		if (Match(EqToken))
		{
			c.Log(" == ");
			if (Expr4(t))
			{
			}

			//emit and code
			c.Emit1(SUB);
			c.Emit1(TZE);
		}

		return true;
	}

	return false;
}

bool Parser::Expr6(enum Type t)
{
	if (Expr5(t))
	{
		if (Match(AssignToken))
		{
			c.Log (" Assign ");
			if (Expr5(t))
			{
			}
		
			//TODO find record location
			//TODO store value in record
		}

		return true;
	}

	return false;
}
bool Parser::Expr5(enum Type t)
{
	if (Expr4(t))
	{
		if (Match(AndToken))
		{
			c.Log (" AND ");
			if (Expr5(t))
			{
			}

			//emit and code
			c.Emit1(AND);
		}
		return true;
	}

	return false;
}

bool Parser::FunctionCall()
{
	if (Match(FetchToken))
	{

	}

	return false;
}

bool Parser::Expr(enum Type t)
{
	if (Expr6(t)) {
		//do some shit
		if (Match(OrToken))
		{
			c.Log (" OR ");
			if (Expr(t))
			{

			}
		}
		return true;
	}
	return false;
}


bool Parser::RHS(enum Type t, std::string idName)
{
	if (Match(AssignToken))
	{
		c.Log("Assign (");

		this->Expr(t);
		//then we need to assign the value to the variable
		Record r = table.FindRecord(idName);
		//want to push the memory location onto the stack
		c.Emit1(LDM2);
		c.Emit2(r.offset);
		//want to store the value to that location
		c.Emit1(STLR4);
		c.Log(") to (" + r.name + " )");

		return this->RHSContinued(t);
	}
	return false;
}

bool Parser::VariableDeclaration(enum Type t, std::string idName)
{
	c.Log( "\""+ idName + "\" ");
	if (Match(ArrayDefToken))
	{ 
		c.Log(" [");
		int value;
		if (Poodle(value))
		{
			if (Match(ArrayDefToken))
			{
				//was able to parse the entire array definition
				table.AddArray(idName, t, value);
				c.Log(to_string(value) + "]");
			}
		}

		return true;
	}
	else if (VariableEnding(t, idName))
		return true;
	else {
		//ERROR

	}

	return false;
}

bool Parser::Declarations(size_t &pcline)
{
	enum Type typeDeclared;
	while (s.HasToken())
	{
		if (Match( EoLToken))
		{
			//parse the other declarations, no code gen
			c.Log("EoL");
		}
		else if (ReturnType(typeDeclared))
		{
			//function or variable
			this->Declaration(typeDeclared, pcline);
		}
	}

	return false;
}

//done on speaks
bool Parser::SpeakStatement () 
{
	if (SpeakPoodle())
	{
		return true;
	}
	else if (SpeakCorgi())
	{
		return true;
	}
	else if(SpeakYorkie())
	{
		return true;	
	}

	else if (SpeakDalmatian())
	{
		return true;
	}

	return false;
}
bool Parser:: SpeakPoodle()
{
	if(Match(PrintIntToken))
	{
		//output tree to screen, if wanted
		c.Log("SpeakPoodle (");
		//try to evaluate the following expression
		if(Expr(TypePoodle))
		{		
			c.Emit1(OUTI);
			//then output a new line
			c.Emit1(LDM1);
			c.Emit1('\n');
			c.Emit1(OUTC);
			c.Log(")");
			return true;
		}


	}
	return false;


}
bool Parser:: SpeakCorgi()
{
	if(Match(PrintRealToken))
	{	
		c.Log("SpeakCorgi (");
		if(Expr(TypeCorgi))
		{
			c.Emit4(OUTR);
			c.Log(")");
		}
	}
	return false;
}
bool Parser:: SpeakYorkie()
{
	if(Match(PrintCharToken))
	{	
		c.Log("SpeakYorkie(");
		if(Expr(TypeYorkie))
		{
			c.Emit1(OUTC);
			c.Log(")");
		}
	}
	return false;
}
bool Parser:: SpeakDalmatian()
{
	if(Match(PrintBoolToken))
	{	
		c.Log("SpeakDalmatian(");
		if(Expr(TypeDalmatian))
		{
			c.Emit1(TNZ);
			c.Emit1(BYES);
			size_t falsebranch = c.Emit2(0);
			//branch to the false case, falls through to the true
			c.Emit1(LDM1);
			c.Emit1('X');
			c.Emit1(LDM1);
			c.Emit1('X');
			c.Emit1(OUTC);
			c.Emit1(OUTC);
			c.Emit1(JMPD);
			size_t wheretheEndGoes = c.Emit2(0);
			size_t startOfFalse = c.Emit1(LDM1);
			c.Emit1('O');
			c.Emit1(LDM1);
			c.Emit1('O');
			c.Emit1(OUTC);
			c.Emit1(OUTC);

			size_t endOfFalsebranch = c.CurrentAddr();

			//backpatch like a boss
			c.BackPatch2(falsebranch, startOfFalse-falsebranch);
			c.BackPatch2(wheretheEndGoes, endOfFalsebranch);
		}

		else
		{
			return false;
		}
	}
	return false;
}

//TODO: care
bool Parser:: RollOverLoop()
{
	int dontcare;
	size_t blockSize;
	if(Match(ForToken))
	{
		c.Log ("ForToken (");
		enum Type t;
		if (Type(t))
		{

			if(currentToken.token == NameToken)
			{
				c.Log(" Var:" + to_string(t) + " \"" + currentToken.value + "\" ");
				string name = currentToken.value;

				//add record			
				if (!table.AddVariable(currentToken.value, t))
					//record wasn't able to be added
						//ERROR
							return false;

				Record r = table.FindRecord(currentToken.value);
				GetNextToken();
				if(Match(FromToken))
				{
					c.Log(" From ");
					if (Poodle(dontcare)) //TODO Evaluate the poodles
					{
						//store value on stack, to record location
						c.Emit1(STLR4);
						c.Emit2(r.offset);

						if(Match(ToToken))
						{
							c.Log (" To ");
							//put it back on the stack
							size_t predicateStart = c.CurrentAddr();
							c.Emit1(LDLR4);
							c.Emit2(r.offset);
							if (Poodle(dontcare))
							{
								c.Emit1(SUB);
								c.Emit1(TNG);
								c.Emit1(BNO);
								size_t toBeBackPatched = c.Emit2(0);

								//determine if we should the loop
								if(BlockStatement(blockSize))
								{
									//increment step
									c.Emit1(LDLR4);
									c.Emit2(r.offset);
									c.Emit1(INC);
									c.Emit1(STLR4);
									c.Emit2(r.offset);

									//compare to see if still valid, just go back up to predicate
									c.Emit1(JMP);
									c.Emit2(toBeBackPatched);
									size_t endOfBlock = c.CurrentAddr();
									c.BackPatch4(toBeBackPatched, endOfBlock - toBeBackPatched);
								}

							}
						}
					}
				}
			}
		}
	}

	return false;

}

//done
bool Parser:: ChaseLoop()
{
	size_t blockSize;
	if (Match(WhileToken))
	{
		c.Log("WhileToken (");

		size_t predicateAddress = c.CurrentAddr();
		if (Predicate())
		{

			c.Emit1(BNO);
			size_t toBeBackPatched = c.Emit2(0);
			if (BlockStatement(blockSize))
			{
				//TODO
				c.Emit1(JMP);
				c.Emit2(predicateAddress);
				size_t endOfBlock = c.CurrentAddr();
				c.BackPatch2(toBeBackPatched, endOfBlock-toBeBackPatched);
			}
			else
				return false;
		}

		c.Log(")");
	}

	return false;
}

//done maybe
bool Parser::FeedStatement()
{
	if(FeedPoodle())
	{
		return true;
	}
	else if(FeedCorgi())
	{
		return true;
	}
	else if(FeedYorkie())
	{
		return true;
	}
	else if(FeedDalmatian())
	{
		return true;
	}
	return false;
}

bool Parser::FeedPoodle()
{

	if(Match(InputIntToken))
	{
		c.Log("FeedPoodle (");
		enum Type typeOfVar = TypeStray;
		if(Expr0(typeOfVar))
		{

			if (typeOfVar != TypePoodle)
			{
				//ERROR, try to read in into to non-interger
				return false;
			}
			else 
			{
				//variable was of type poodle, read in number
				c.Emit2(INPUTI);
				c.Log(")");

			}
			//comment odo
		}
	}

	return false;
}

bool Parser::FeedCorgi()
{

	if(Match(InputRealToken))
	{
		c.Log("FeedCorgi (");
		enum Type typeOfVar = TypeStray;
		if(Expr0(typeOfVar))
		{

			if(typeOfVar != TypeCorgi)
			{
				//Error
				return false;
			}
			else
			{
				//variable was type Corgi, read in number
				c.Emit2(INPUTR);
				c.Log(")");
			}
		}
	}

	return false;

}

bool Parser::FeedYorkie()
{
	if(Match(InputIntToken))
	{
		c.Log("FeedYorkie (");
		enum Type typeOfVar = TypeStray;
		if(Expr0(typeOfVar))
		{

			if(typeOfVar != TypeYorkie)
			{
				//Error
				return false;
			}
			else
			{
				//variable was type Yotkie, read in number
				c.Emit2(INPUTC);
				c.Log(")");
			}
		}
	}

	return false;

}


bool Parser::FeedDalmatian()
{
	if(Match(InputIntToken))
	{
		c.Log("FeedDalmatian (");
		enum Type typeOfVar = TypeStray;
		if(Expr0(typeOfVar))
		{

			if(typeOfVar != TypeDalmatian)
			{
				//Error
				return false;
			}

			if(c.Emit2(INPUTC) == 0)
			{
				c.Emit1(STLR1);
				c.Log(")");
				return true;
			}
			else if(c.Emit2(INPUTC) == 1)
			{
				c.Emit1(STLR1);
				c.Log(")");
				return true;
			}
			//comment todo
		}
	}
	return false;
}

bool Parser::ScratchLoop()
{
	size_t s;
	if(Match(RepeatToken))
	{
		size_t predicateAddress = c.CurrentAddr();
		c.Log("ScratchLoop (");
		if(BlockStatement(s))
		{
			c.Emit1(JMP);
			c.Emit2(predicateAddress);
			size_t endOfBlock = c.CurrentAddr();

			if(Match(UntilToken))
			{
				c.Log("Until (");
				if(Predicate())
				{
					//comment todo
					c.Emit1(BNO);
					size_t toBeBackPatched = c.Emit2(0);
					c.BackPatch2(toBeBackPatched, endOfBlock-toBeBackPatched);
				}
			}
		}
	}
	return false;
}

bool Parser::SniffStatement()
{
	size_t s;
	if(Match(IfToken))
	{
		c.Log("If (");
		size_t predicateAddress = c.CurrentAddr();
		if(Predicate())
		{
			c.Emit1(BNO);
			size_t toBeBackPatched = c.Emit2(0); //placeholder
			//we evaluated the expresion, only continue if it was true
			if(BlockStatement(s))
			{
				if (Match(ElseToken))
				{
					c.Log("Else (");
					c.Emit1(JMP);
					size_t toBeEndOfElse = c.Emit2(0); //placeholder
					size_t beginningOfElse = c.CurrentAddr();

					if(BlockStatement(s))
					{
						//else block was parsed
						c.BackPatch2(toBeBackPatched, beginningOfElse-toBeBackPatched); // set else brach to go here
						c.BackPatch2(toBeEndOfElse , beginningOfElse-toBeEndOfElse);	// set if branch to leave body altogether
					}
				}
				else
				{
					//was not an else statement
					//backpatch to this location]
					size_t endOfBlock = c.CurrentAddr();
					c.BackPatch2(toBeBackPatched, endOfBlock-toBeBackPatched);
				}
			}
			else
				return false;
		}
	}
	return false;
}

bool Parser::Comparator(){
	if (currentToken.token == LessToken)
	{
		return true;
	}
	else if (currentToken.token == GreaterToken)
	{
		return true;
	}
	else if (currentToken.token == EqToken)
	{
		return true;
	}
	else if (currentToken.token == NotEqualToken)
	{
		return true;
	}
	else if (currentToken.token == GreaterOrEqualToken)
	{
		return true;
	}
	else if (currentToken.token == LessOrEqualToken)
	{
		return true;
	}
	return false;
}

void Parser::Run()
{
	//start of program
	c.Emit1(LDM2);
	size_t PCLocation = c.Emit2(0);
	c.Emit1(POPP);
	size_t PClineNum =0;

	//start reading tokens
	GetNextToken();
	Declarations(PClineNum);

	//backpatch the start of the program
	c.BackPatch2(PCLocation, PClineNum);

	//EndProgram
	c.Emit1(HALT);
	c.Emit1(HALT);
	c.Emit1(HALT);
	c.Emit1(HALT);
}

void Parser::Flush()
{
	c.flush();
}

