#ifndef TOKENIZER_LUNG_H__
#define TOKENINER_LUNG_H__
#include "constants.h"
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

class Tokenizer
{
public:
    Tokenizer();
    Tokenizer(string str, int type);
    friend ostream& operator <<(ostream& outs, const Tokenizer& t);
    int type() const;
    string type_string() const;
    string token_str() const;
private:
    string _token;
    int _type;
};



#endif