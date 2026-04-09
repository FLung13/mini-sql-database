#ifndef PARSER_LUNG_H__
#define PARSER_LUNG_H__
using namespace std;
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "../../includes/tokenizer/stokenize.h" 
#include "../../includes/table/typedefs.h"

class Parser
{
    public:
    
    Parser(char* s);

    mmap_ss parse_tree();

    void set_string(char* s);

    int get_column(string t);

    bool get_parse_tree();

    void build_keyword_list();
    
     void make_table();

    private:
    
    mmap_ss Ptree;
    map_sl keywords;
    string original;
    bool fail = true;
    vector<string>input_q;
    enum keys {ZERO, SELECT, FROM, STAR, WHERE, SYM, INSERT, MAKE, 
            CREATE, FIELDS, VALUES, INTO, TABLE};
    static int _table[MAX_ROWS][MAX_COLUMNS];

};

#endif