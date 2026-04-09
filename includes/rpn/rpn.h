#ifndef RPN_LUNG_H__
#define RPN_LUNG_H__
using namespace std;
#include <iostream>
#include <iomanip>
#include "assert.h"
#include <cmath>
#include <algorithm>
#include <string>
#include "../../includes/table/typedefs.h"
#include "../../includes/token/token.h"
#include "../../includes/bplustree/MyStack.h"
#include "../../includes/bplustree/MyQueue.h"

class RPN{
public: 
    RPN();
    RPN(Queue<Token*> postfix);
    vector<long> operator()(vector<string> s, Map<string, long> &tempmap, vector<MMap<string, long>> &tempindices, vector<MMap<string, long>> &indices, Map<string, long> &map);
    void set_input(Queue<Token*> postfix);
private:
    vector<string> tempvectors;
    Queue<Token*> _postfix;
    Stack<vector<long>> result;
    bool debug = false;
};

#endif