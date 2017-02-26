#ifndef CODEGEN_H
#define CODEGEN_H

#include <iostream>

#define PRINT true

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

class cg {
private:

	char buffer[256 *256];
	size_t _currentAddr;
	std::ostream* out;

public:
	cg(std::ostream& out) { this->out = &out; _currentAddr = 0;}

	void flush();

	//Emits the instruction/operand to the output stream
	//Returns the line which was written to.
	size_t Emit1(const unsigned char c);
	size_t Emit2(const unsigned short c);
	size_t Emit4(const unsigned int c);

	//outputs syntax to screen, if the tree is wanted to be viewed.
	void Log(std::string);
	size_t CurrentAddr();
	void BackPatch1(size_t line, unsigned char value);
	void BackPatch2(size_t line, unsigned short value);
	void BackPatch4(size_t line, unsigned int value);
};

#endif
