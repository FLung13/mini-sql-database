#ifndef RELATIONAL_LUNG_H__
#define RELATIONAL_LUNG_H__
#include "token.h"
using namespace std;


class Relational:public Token{
public:
    Relational();
    Relational(const string& t);
    int type(){return 1;}
    string getRelational(){return s;}
    int precedence();
    virtual void print(ostream& outs) const{
        outs << "Relational(" << s << ")";
    }
private:
    string s;
};

#endif