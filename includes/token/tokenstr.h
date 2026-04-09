#ifndef TOKENSTR_LUNG_H__
#define TOKENSTR_LUNG_H__
#include "token.h"
using namespace std;


class TokenStr:public Token{
public:
    TokenStr();
    TokenStr(const string& t);
    int type(){return 6;}
    string getTokenStr(){return s;}
    virtual void print(ostream& outs) const{
        outs << "TokenStr(" << s << ")";
    }
private:
    string s;
};

#endif