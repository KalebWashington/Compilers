//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>
#include "tokens.h"

std::string lexeme(enum Token token)
{
  if (token == EoLToken) return "!";
  else if (token == AddToken) return "#";
  else if (token == SubToken) return "_/";
  else if (token == MultToken) return "<3";
  else if (token == DivToken) return "VV";
  else if (token == ModToken) return "{}";
  else if (token == IncrToken) return "/T";
  else if (token == DecrToken) return "\\T";
  else if (token == AssignToken) return "/|";
  else if (token == LessToken) return "<}";
  else if (token == GreaterToken) return "{>";
  else if (token == EqToken) return " <>";
  else if (token == NegateToken) return ":3";
  else if (token == AndToken) return "N'";
  else if (token == OrToken) return "//";
  else if (token == TrueToken) return "OO";
  else if (token == FalseToken) return "XX";
  else if (token == HexToken) return "@";
  else if (token == CharLitToken) return "^";
  else if (token == StringLitToken) return "$";
  else if (token == StringEscToken) return "*";
  else if (token == VoidDecToken) return " Stray";
  else if (token == BoolDecToken) return " Dalmatian";
  else if (token == IntDecToken) return " Poodle";
  else if (token == CharDecToken) return " Yorkie";
  else if (token == RealDecToken) return " Corgi";
  /*else if (token == StringDecToken) return " Dachshund";*/
  else if (token == NameToken) return " someName";
  else if (token == VoidToken) return " Stray";
  else if (token == BoolToken) return " OO";
  else if (token == IntToken) return "232";
  else if (token == CharToken) return "^d^";
  else if (token == RealToken) return "5.2";
  else if (token == StringToken) return "$d$";
  else if (token == LParenToken) return "@=";
  else if (token == RParenToken) return "=@";
  else if (token == SeparatorToken) return "::";
  else if (token == ArrayDefToken) return "|";
  else if (token == PointerDefToken) return "..";
  else if (token == DerefToken) return "--";
  else if (token == SingleLineCommentToken) return " PANT\n";
  else if (token == LMultiLineCommentToken) return " GRR";
  else if (token == RMultiLineCommentToken) return " BARK";
  else if (token == LBlockToken) return " SQUIRREL";
  else if (token == RBlockToken) return " Nevermind...";
  else if (token == IfToken) return " Sniff";
  else if (token == ElseToken) return " Sneeze";
  else if (token == SwitchToken) return " NAPTIME";
  else if (token == CaseToken) return " Bed";
  else if (token == DefaultToken) return " Doghouse";
  else if (token == BreakToken) return " Wake!";
  else if (token == WhileToken) return " Chase";
  else if (token == ForToken) return " Rollover";
  else if (token == FromToken) return " From";
  else if (token == ToToken) return " To";
  else if (token == RepeatToken) return " Scratch";
  else if (token == UntilToken) return " NOFLEAS";
  else if (token == InputIntToken) return " FeedPoodle";
  else if (token == InputCharToken) return " FeedYorkie";
  else if (token == InputRealToken) return " FeedCorgi";
  /*else if (token == InputStringToken) return " FeedDachshund";*/
  else if (token == InputBoolToken) return " FeedDalmatian";
  else if (token == PrintIntToken) return " SpeakPoodle";
  else if (token == PrintCharToken) return " SpeakYorkie";
  else if (token == PrintRealToken) return " SpeakCorgi";
  /*else if (token == PrintStringToken) return " SpeakDachshund";*/
  else if (token == PrintBoolToken) return " SpeakDalmation";
  else if (token == LessOrEqualToken) return "<}<>";
  else if (token == GreaterOrEqualToken) return "{><>";
  else if (token ==  NotEqualToken) return ":3<>";
  else if (token == PositiveToken) return "+&";
  else if (token == NegativeToken) return "-&";
  else if (token == BedEndToken) return "?";
  else if (token == AddressOfToken) return "|P";
  else if (token == ErrorToken) return "ErrorToken";
  return "Error";
}

std::ostream& operator<<(std::ostream& os, enum Token token)
{
  if (token == EoLToken) return os << "EoLToken";
  else if (token == AddToken) return os << "AddToken";
  else if (token == SubToken) return os << "SubToken";
  else if (token == MultToken) return os << "MultToken";
  else if (token == DivToken) return os << "DivToken";
  else if (token == ModToken) return os << "ModToken";
  else if (token == IncrToken) return os << "IncrToken";
  else if (token == DecrToken) return os << "DecrToken";
  else if (token == AssignToken) return os << "AssignToken";
  else if (token == LessToken) return os << "LessToken";
  else if (token == GreaterToken) return os << "GreaterToken";
  else if (token == EqToken) return os << "EqToken";
  else if (token == NegateToken) return os << "NegateToken";
  else if (token == AndToken) return os << "AndToken";
  else if (token == OrToken) return os << "OrToken";
  else if (token == TrueToken) return os << "TrueToken";
  else if (token == FalseToken) return os << "FalseToken";
  else if (token == HexToken) return os << "HexToken";
  else if (token == CharLitToken) return os << "CharLitToken";
  else if (token == StringLitToken) return os << "StringLitToken";
  else if (token == StringEscToken) return os << "StringEscToken";
  else if (token == VoidDecToken) return os << "VoidDecToken";
  else if (token == BoolDecToken) return os << "BoolDecToken";
  else if (token == IntDecToken) return os << "IntDecToken";
  else if (token == CharDecToken) return os << "CharDecToken";
  else if (token == RealDecToken) return os << "RealDecToken";
 /* else if (token == StringDecToken) return os << "StringDecToken";*/
  else if (token == NameToken) return os << "NameToken";
  else if (token == VoidToken) return os << "VoidToken";
  else if (token == BoolToken) return os << "BoolToken";
  else if (token == IntToken) return os << "IntToken";
  else if (token == CharToken) return os << "CharToken";
  else if (token == RealToken) return os << "RealToken";
  else if (token == StringToken) return os << "StringToken";
  else if (token == LParenToken) return os << "LParenToken";
  else if (token == RParenToken) return os << "RParenToken";
  else if (token == SeparatorToken) return os << "SeperatorToken";
  else if (token == ArrayDefToken) return os << "ArrayDefToken";
  else if (token == PointerDefToken) return os << "PointerDefToken";
  else if (token == DerefToken) return os << "DerefToken";
  else if (token == SingleLineCommentToken) return os << "SingleLineCommentToken";
  else if (token == LMultiLineCommentToken) return os << "LMultiLineCommentToken";
  else if (token == RMultiLineCommentToken) return os << "RMultiLineCommentToken";
  else if (token == LBlockToken) return os << "LBlockToken";
  else if (token == RBlockToken) return os << "RBlockToken";
  else if (token == IfToken) return os << "IfToken";
  else if (token == ElseToken) return os << "ElseToken";
  else if (token == SwitchToken) return os << "SwitchToken";
  else if (token == CaseToken) return os << "CaseToken";
  else if (token == WhileToken) return os << "WhileToken";
  else if (token == ForToken) return os << "ForToken";
  else if (token == FromToken) return os << "FromToken";
  else if (token == ToToken) return os << "ToToken";
  else if (token == RepeatToken) return os << "RepeatToken";
  else if (token == UntilToken) return os << "UntilToken";
  else if (token == InputIntToken) return os << "InputIntToken";
  else if (token == InputCharToken) return os << "InputCharToken";
  else if (token == InputRealToken) return os << "InputRealToken";
 /* else if (token == InputStringToken) return os << "InputStringToken";*/
  else if (token == InputBoolToken) return os << "InputBoolToken";
  else if (token == PrintIntToken) return os << "PrintIntToken";
  else if (token == PrintCharToken) return os << "PrintCharToken";
  else if (token == PrintRealToken) return os << "PrintRealToken";
 /* else if (token == PrintStringToken) return os << "PrintStringToken";*/
  else if (token == PrintBoolToken) return os << "PrintBoolToken";
  else if (token == LessOrEqualToken) return os << "LessOrEqualToken";
  else if (token == GreaterOrEqualToken) return os << "GreaterOrEqualToken";
  else if (token ==  NotEqualToken) return os << " NotEqualToken";
  else if (token == PositiveToken) return os << "PositiveToken";
  else if (token == NegativeToken) return os << "NegativeToken";
  else if (token == BedEndToken) return os << "BedEndToken";
  else if (token == AddressOfToken) return os << "AddressOfToken";
  else if (token == ErrorToken) return os << "ErrorToken";
  return os << "Error";
}

std::ostream& operator<<(std::ostream& os, TokenInfo token)
{
  return os << "{ token: " << token.token << " lex: " << token.value.c_str() << " }";
}
