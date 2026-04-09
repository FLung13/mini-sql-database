#ifndef TOKEN_LUNG_H__
#define TOKEN_LUNG_H__
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Token{
public:
    Token():s(""){};
    Token(const string& t):s(t){};
    virtual int type(){return -1;}
    virtual char getLeftParenthesis(){return '\0';}
    virtual char getRightParenthesis(){return '\0';}
    virtual string getTokenStr(){return "";}
    virtual string getRelational(){return "";}
    virtual string getLogical(){return "";}
    virtual int precedence(){return 0;}
    virtual void print(ostream& outs) const{
        outs << s;
    }

    friend ostream& operator <<(ostream& outs, const Token& _t){
        _t.print(outs);

        return outs;
    }

private:
    string s;
};

#endif