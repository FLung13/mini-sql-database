#include "LParen.h"


LParen::LParen(){
    s = "(";
}

LParen::LParen(const string& t):Token(t), s("("){

}

int LParen::precedence()
{
    return 2;
}
