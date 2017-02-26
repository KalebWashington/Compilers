
//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include "codegen.h"
#include <string>

using namespace std;

size_t cg::Emit1(const unsigned char c)
{
	size_t addr = _currentAddr;
	buffer[_currentAddr++] = c;
	return addr;
}

size_t  cg::Emit2(unsigned short c)
{
	size_t addr = CurrentAddr();
	unsigned char* d = (unsigned char*)&c;
	buffer[_currentAddr++] =d[0];
	buffer[_currentAddr++] =d[1];
	return addr;
}

size_t cg::Emit4(unsigned int c)
{
	size_t addr = CurrentAddr();
	cg::Emit2(c & 0xFFFF);
	cg::Emit2(c & 0xFFFF0000 );


	return addr;
}



void cg::flush()
{
	out->clear();
	out->write(buffer, CurrentAddr());
	out->flush();
}

void cg::BackPatch1(size_t line, unsigned char value)
{
	buffer[line] = value;
	return;
}

void cg::BackPatch2(size_t line, unsigned short value)
{
	buffer[line++] = (value >> 0) & 0xFF;
	buffer[line++] = (value >> 8) & 0xFF;
	return;
}


void cg::BackPatch4(size_t line, unsigned int value)
{
	buffer[line++] = (value & 0xFF);
	buffer[line++] = (value & 0xFF00);
	buffer[line++] = (value & 0xFF000);
	buffer[line++] = (value & 0xFF000);

	return;
}

void cg::Log(std::string s)
{
	if (PRINT)
		cout << s;
}

size_t cg::CurrentAddr()
{
	return cg::_currentAddr;
}
