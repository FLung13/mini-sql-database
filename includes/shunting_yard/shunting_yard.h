#ifndef SHUNTING_YARD_LUNG_H__
#define SHUNTING_YARD_LUNG_H__
#include <iostream>
#include <iomanip>
#include <cmath>
#include "../../includes/token/token.h"
#include "../../includes/rpn/rpn.h"
#include "../../includes/bplustree/MyStack.h"
#include "../../includes/bplustree/MyQueue.h"
// #include "../../includes/token/function.h"
// #include "../../includes/token/integer.h"
// #include "../../includes/token/operator.h"
// #include "../../includes/token/rightparen.h"
// #include "../../includes/token/leftparen.h"
#include <algorithm>

using namespace std;

class ShuntingYard{
public:
    ShuntingYard(vector<string> conditions);
    ShuntingYard(const Queue<Token*> &infix): _infix(infix){}
    Queue<Token*> postfix(){return postfix(_infix);}
    Queue<Token*> postfix(const Queue<Token*> &infix);
    Queue<Token*> infix(const Queue<Token*> &infix){return _infix = infix;}

private:
    vector<string> s;
    Queue<Token*> _infix;
    Stack<Token*> opers;
    Queue<Token*> result;
};

#endif