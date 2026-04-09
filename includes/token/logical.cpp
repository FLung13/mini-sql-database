#include "logical.h"


Logical::Logical(){
    s = "";
}

Logical::Logical(const string& t): Token(t){

    for (int i = 0; i < t.length(); i++)
    {
        s.push_back(tolower(t[i]));
    }
}

int Logical::precedence()
{
    if (s == "and")
    {
        return 4;
    } else if (s == "or")
    {
        return 5;
    }
    
    return 0;
}
