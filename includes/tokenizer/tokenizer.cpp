#include "tokenizer.h"

Tokenizer::Tokenizer(){
    _token = "";
    _type = 0;
}

Tokenizer::Tokenizer(string str, int type){
    _token = str;
    _type = type;
}

ostream& operator<<(ostream& outs, const Tokenizer& t){
    outs << "|" << t.token_str() << "|";
    // outs << t.token_str();
    return outs;
}

int Tokenizer::type() const{
    return _type;
}

string Tokenizer::type_string() const{
    switch (_type)
    {
    case 1:
        return "NUMBER";
    case 2:
        return "ALPHA";
    case 3:
        return "SPACE";
    case 4:
        return "OPERATOR";
    case 5:
        return "PUNC";
    case 6:
        return "COMILLAS";
    case 13:
        return "PARENTESIS";
    case 25:
        return "STAR";
    case -1:
        return "UNKNOWN";
    case -2:
        return "END";
    default:
    return "UNKNOWN";
    }
}

string Tokenizer::token_str() const{
    return _token;
}