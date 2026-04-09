#ifndef LOGICAL_LUNG_H__
#define LOGICAL_LUNG_H__
#include "token.h"
using namespace std;


class Logical:public Token{
public:
    Logical();
    Logical(const string& t);
    int type(){return 5;}
    string getLogical(){return s;}
    int precedence();
    virtual void print(ostream& outs) const{
        outs << "Logical(" << s << ")";
    }
private:
    string s;
};

#endif