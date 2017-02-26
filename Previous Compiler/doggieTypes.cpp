
//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include "doggieTypes.h"

std::ostream& operator<<(std::ostream& os, enum Type t)
{
  if (t == TypeYorkie)
    return os << "Yorkie";
  if (t == TypeDalmatian)
    return os << "Dalmatian";
  if (t == TypePoodle)
    return os << "Poodle";
  if (t == TypeCorgi)
    return os << "Corgi";
  if (t == TypeDachshund)
    return os << "Dachshund";
  if (t == TypeStray)
    return os << "Stray";
  return os << "_UNKOWN_TYPE_";
}

std::ostream& operator<<(std::ostream& os, enum Kind k)
{
  if (k == KindVar)
    return os << "var";
  else if (k == KindFunc)
    return os << "func";
  return os << "_UNKOWN_KIND_";

}


