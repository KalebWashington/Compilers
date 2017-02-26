all: parser

w: main.cpp codegen.cpp tokens.cpp Parser.cpp scanner.cpp symTable.cpp doggieTypes.cpp
	g++ -c -Wall main.cpp 
	g++ -c -Wall codegen.cpp 
	g++ -c -Wall tokens.cpp 
	g++ -c -Wall Parser.cpp 
	g++ -c -Wall scanner.cpp 
	g++ -c -Wall symTable.cpp 
	g++ -c -Wall doggieTypes.cpp

parser: main.cpp Parser.o symTable.o doggieTypes.o scanner.o codegen.o
	g++ -g main.cpp Parser.o symTable.o doggieTypes.o scanner.o codegen.o 

test: ScannerTests.cpp scanner.o doggieTypes.o tokens.o
	g++ -g ScannerTests.cpp tokens.o scanner.o -o scannerTest && ./scannerTest

sym: SymbolTableTests.cpp symTable.o doggieTypes.o
	g++ SymbolTableTests.cpp symTable.o doggieTypes.o -o SymTableTest && ./SymTableTest

codegen.o: codegen.cpp codegen.h
	g++ -c codegen.cpp 

tokens.o: tokens.cpp tokens.h
	g++ -c tokens.cpp 

Parser.o: Parser.cpp Parser.h codegen.o
	g++ -c Parser.cpp codegen.o 

scanner.o: scanner.cpp scanner.h doggieTypes.o
	g++ -c scanner.cpp doggieTypes.o 

symTable.o: symTable.cpp symTable.h doggieTypes.o
	g++ -c symTable.cpp doggieTypes.o 

doggieTypes.o: doggieTypes.cpp doggieTypes.h 
	g++ -c doggieTypes.cpp 

clean:
	rm *o test
