#ifndef TYPEDEFS_LUNG_H__
#define TYPEDEFS_LUNG_H__
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../bplustree/MyQueue.h"
#include "../bplustree/MyStack.h"
#include "../token/LParen.h"
#include "../token/relational.h"
#include "../token/RParen.h"
#include "../token/tokenstr.h"
#include "../token/logical.h"
#include "../rpn/rpn.h"
#include "../shunting_yard/shunting_yard.h"
#include <cmath>
#include <queue>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

typedef Map<string, string> map_ss;
typedef MMap<string, string> mmap_ss;

typedef Map<string, long> map_sl;
typedef MMap<string, long> mmap_sl;


typedef vector<string> vectorstr;
typedef vector<long> vectorlong;
typedef Queue<string> queuestr;
typedef Queue<Token *> queuetk;

// enum TokenType
// {
//     TOKEN,
//     LPAREN,
//     RPAREN,
//     TOKEN_STR,
//     OPERATOR,
//     RELATIONAL,
//     LOGICAL,
//     RESULT_SET,
//     TOKEN_NUMBER,
//     TOKEN_ALPHA,
//     TOKEN_SPACE,
//     TOKEN_OPERATOR,
//     TOKEN_PUNC,

//     TOKEN_UNKOWN,
//     TOKEN END

// };



#endif