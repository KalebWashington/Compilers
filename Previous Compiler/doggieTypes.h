#ifndef DOGGIETYPES_H
#define DOGGIETYPES_H

//Group Symbol Table Project
// Jonathan Ringer
// Jeremy Vasseur
// Washing Kaleb
// Phillip Germagliotti

#include <iostream>

enum Type { TypeYorkie = 0, TypeDalmatian, TypePoodle, TypeCorgi, TypeDachshund, TypeStray};

//not sure about the void type, depends on the size of a word in memory

const int typeSize[] = { 1, 1, 4, 4, 4, 2, 2};

enum Kind { KindVar = 0, KindFunc };

inline int TypeSize(Type type) { return typeSize[type]; }

std::ostream& operator<<(std::ostream& os, enum Type t);

std::ostream& operator<<(std::ostream& os, enum Kind k);

#endif
