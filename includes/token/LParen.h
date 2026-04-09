#ifndef LEFTPAREN_LUNG_H__
#define LEFTPAREN_LUNG_H__
#include "token.h"
using namespace std;

class LParen:public Token{
public:
    LParen();
    LParen(const string& t);
    int type(){return 15;}
    char getLeftParenthesis(){return s[0];}
    int precedence();
    virtual void print(ostream& outs) const{
        outs << "LeftParen(" << s << ")";
    }
private:
    string s;
};

#endif