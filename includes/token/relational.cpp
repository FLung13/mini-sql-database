#include "relational.h"


Relational::Relational(){
    s = "";
}

Relational::Relational(const string& t):Token(t), s(t){

}

int Relational::precedence()
{
    return 3;
}
