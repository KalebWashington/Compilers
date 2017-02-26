#ifndef TOKENS_H
#define TOKENS_H

//Jonathan Ringer
//Kaleb Washington
//Jeremy Vasseur
//Phillip Germagliotti

#include <iostream>

// This file defines the tokens that are available in the doggiestyle language

#define NUM_OF_TOKENS 70
                                    //C-keyword   Doggie
enum Token  { EoLToken = 1,         //;           !
              LessOrEqualToken,     //<=          <}<>
              GreaterOrEqualToken,  //>=          {><>
              NotEqualToken,        //!=          :3<>
              PositiveToken,        //+num        +&
              NegativeToken,        //-num        -&
              BedEndToken,          //            ?
              AddressOfToken,       //            |P
              AddToken,             //+           #
              SubToken,             //-           _/
              MultToken,            //*           <3
              DivToken,             ///           VV
              ModToken,             //%           {}
              IncrToken,            //++          /T
              DecrToken,            //--          \T
              AssignToken,          //=           /|
              LessToken,            //<           <}
              GreaterToken,         //>           {>
              EqToken,              //==          <>
              NegateToken,          //!           :3
              AndToken,             //&&          N'
              OrToken,              //||          //
              TrueToken,            //true        oo
              FalseToken,           //false       xx
              HexToken,             //0x          @
              CharLitToken,         //'           ^
              StringLitToken,       //"           $
              StringEscToken,       //\           *
              VoidDecToken,         //void        Stray
              BoolDecToken,         //bool        Dalmatian
              IntDecToken,          //int         Poodle
              CharDecToken,         //char        Yorkie
              RealDecToken,         //double      Corgi
           /*   StringDecToken,*/       //string      Dachshund
              NameToken,            //<id>        <id>
              VoidToken,            //????        ????
              BoolToken,            //true/false  oo/xx
              IntToken,             //52          52
              CharToken,            //'c'         ^c^
              RealToken,            //52.1        52.1 
              StringToken,          //"hello"     $hello$
              LParenToken,          //(           8=
              RParenToken,          //)           =8
              SeparatorToken,       //,           ::
              ArrayDefToken,        //[           |
              PointerDefToken,      //*           ..
              DerefToken,           //*           --
              SingleLineCommentToken,////         PANT
              LMultiLineCommentToken,///*         GRR
              RMultiLineCommentToken,//*/         BARK 
              LBlockToken,          //{           SQUIRREL
              RBlockToken,          //}           NEVERMIND... 
              IfToken,              //if          SNIFF
              ElseToken,            //else        SNEEZE
              SwitchToken,          //switch      NAPTIME
              CaseToken,            //case        BED
              BreakToken,           //break       Wake
              DefaultToken,         //default     Doghouse
              WhileToken,           //while       CHASE
              ForToken,             //for         ROLLOVER
              FromToken,            // ----       FROM
              ToToken,              // ----       TO
              RepeatToken,          // ----       SCRATCH
              UntilToken,           // ----       NOFLEAS
              InputIntToken,        // ---        FEEDPOODLE
              InputCharToken,       // ---        FEEDYORKIE
              InputRealToken,       // ----       FEEDCORGI
             /* InputStringToken,*/     // ----       FEEDDACHSHUND
              InputBoolToken,       // ----       FEEDDALMATION
              PrintIntToken,        // ---        SPEAKPOODLE
              PrintCharToken,       // ---        SPEAKYORKIE
              PrintRealToken,       // ----       SPEAKCORGI
              /*PrintStringToken, */    // ----       SPEAKDACHSHUND
              PrintBoolToken,       // ----       SPEAKDALMATION
              ErrorToken,           //parse error
              FetchToken,           //-----         ----
              };

typedef struct  {
  Token token;
  std::string value;
} TokenInfo;

std::string lexeme(enum Token);
std::ostream& operator<<(std::ostream& os, enum Token);
std::ostream& operator<<(std::ostream& os, TokenInfo token);

#endif
