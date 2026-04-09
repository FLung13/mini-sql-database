#include "tokenstr.h"


TokenStr::TokenStr(){
    s = "";
}

TokenStr::TokenStr(const string& t):Token(t), s(t){

}