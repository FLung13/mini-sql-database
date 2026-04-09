#include "RParen.h"


RParen::RParen(){
    s = ")";
}

RParen::RParen(const string& t):Token(t), s(")"){

}

int RParen::precedence()
{
    return 1;
}