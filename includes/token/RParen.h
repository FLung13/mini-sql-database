#ifndef RIGHTPAREN_LUNG_H__
#define RIGHTPAREN_LUNG_H__
#include "token.h"
using namespace std;


class RParen:public Token{
public:
    RParen();
    RParen(const string& t);
    int type(){return 10;}
    char getRightParenthesis(){return s[0];}
    int precedence();
    virtual void print(ostream& outs) const{
        outs << "RightParen(" << s << ")";
    }
private:
    string s;
};

#endif