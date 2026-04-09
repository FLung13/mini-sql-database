#include "parser.h"


Parser::Parser(char* s)
{
    set_string(s);                                                                                  // TOKENIZE THE CHARACTERS
    make_table();                                                                                   // MAKE STATE MACHINE (TABLE)
    build_keyword_list();                                                                           // BUILD KEYWORDS MAP
}

mmap_ss Parser::parse_tree()
{
    get_parse_tree();                                                                               // BUILDS A MMAP OR PARSE TREE WITH THE KEYWORDS
    return Ptree;
}

inline void Parser::set_string(char *s)
{
    bool mfn = false;                                                                               // MISSING FIELD NAME
    input_q.clear();                                                                                // CLEAR PREVIOUSLY USED STRING TOKENIZER INPUT
    Ptree.clear();                                                                                  // CLEAR PREVIOUSLY USED PTREE
    STokenizer stk(s);                                                                              // STRING TOKENIZE THE CHARACTER ARRAY
    Tokenizer t;
    stk >> t;
    while(stk.more()){                                                                              // WHILE TO GET THE INPUT_QUEUE (STRING TOKENS)
        if (t.type() == TOKEN_NUMBER || t.type() == TOKEN_ALPHA || t.type() == TOKEN_OPERATOR || t.type() == TOKEN_COMILLAS || t.type() == TOKEN_PAREN || t.type() == TOKEN_STAR)
        {
            mfn = false;
            input_q.push_back(t.token_str());
        }
        else if (t.type() == TOKEN_PUNC)
        {
            // input_q.push_back(t.token_str());
            if (mfn)
            {
                string s = "field name";
                throw s;
            }
            
            mfn = true;
        }
        
        // cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
        // cout << input_q << endl;
        t = Tokenizer();
        stk>>t;

        
    }
    // cout << input_q << endl;
}

inline int Parser::get_column(string t)
{
    if (keywords.contains(t))                                                                           // CHECK IF CONTAINS KEYWORD
    {
        // cout << "returning keyword" << endl;
        return keywords[t];
    }else if (t == "*")                                                                                 // CHECK FOR STAR (*)
    {
        // cout << "returning keyword" << endl;
        return keywords["star"];
    }
    
    else                                                                                                // EVERYTHING ELSE IS A SYMBOL
    {
        return SYM;
    }    
}

inline bool Parser::get_parse_tree()
{
    bool from = false;
    bool select = false;
    bool fields = false;
    int state = 0;                                                                                                   // INITIALIZE STATE
    for (int i = 0; i < input_q.size(); i++)                                                                         // LOOP THROUGH THE INPUT QUEUE
    {
        string token(input_q[i]);                                                                                    // CREATE A STRING WITH THE TOKEN FROM INPUT QUEUE
        state = _table[state][get_column(token)];                                                                   // GET NEW STATE WITH TOKEN
        // cout << state << endl;
        
        switch (state)                                                                                              // SWITCH CASE FOR THE MMAP
        {
        case 1:
            Ptree["command"] += token;                                                                              // COMMMAND "SELECT"
            select = true;
            break;
        case 7:
            Ptree["command"] += token;                                                                              // COMMAND "MAKE"
            from = true;
            break;
        case 6:
            Ptree["command"] += token;                                                                              // COMMAND "INSERT"
            from = true;
            break;
        case SYM:                                                                                               
            if (Ptree.contains("where"))
            {
                Ptree["condition"] += token;                                                                        // SYMBOL CONDITIONS
            }
            else
            {   
                fields = true;
                Ptree["fields"] += token;                                                                           // SYMBOL FIELDS
            }
            break;
        case 24: case 32:
            Ptree["condition"] += token;                                                                            // SYMBOL CONDTIONS
            break;
        case 3: case 18:
            fields = true;
            Ptree["fields"] += token;                                                                               // FIELD NAMES
            break;
        case 2: case 19: case 21:
            // Ptree["from"] += token;
            from = true;
            break;
        case 4: case 23: case 31:
            Ptree["where"].push_back("yes");                                                                        // WHERE "YES"
            break;
        case 15: case 29: case 20: case 22:
            Ptree["table_name"] += token;                                                                           // TABLE NAME
            break;
        case 17:
            Ptree["values"] += token;                                                                               // INSERT VALUE
            break;
        case 40:
            Ptree["col"] += token;                                                                                  // CREATING THE TABLE WITH THIS FIELD NAMES
            break;
        default:
            break;
        }
    }
    
    
    if (select && !fields)                                                                                          // FIELD NAMES MISSING
    {
        string s = "field name";
        throw s;
    }
    if (select && !from && fields)                                                                                  // FROM MISSING
    {
        string s = "from";
        throw s;
    }
    
    // cout << Ptree << endl;
    
    return false;
}

inline void Parser::build_keyword_list()                                                                            // BUILD KEYWORD MAP/LIST
{
    keywords.insert("select", SELECT);
    keywords.insert("from", FROM);
    keywords.insert("star", STAR);
    keywords.insert("where", WHERE);
    keywords.insert("sym", SYM);
    keywords.insert("insert", INSERT);
    keywords.insert("make", MAKE);
    keywords.insert("create", CREATE);
    keywords.insert("fields", FIELDS);
    keywords.insert("values", VALUES);
    keywords.insert("into", INTO);
    keywords.insert("table", TABLE);
    keywords.insert("comma", 45);
}

inline void Parser::make_table()                                                                                     // MAKE THE STATE MACHINE(TABLE)
{
    init_table(_table);

    for (int i = 0; i < 5; i++)
    {
        mark_fail(_table, i);
    }
    
    mark_success(_table, 5);
    mark_cell(0, _table, SELECT, SELECT);
    mark_cell(0, _table, INSERT, INSERT);
    mark_cell(0, _table, MAKE, MAKE);
    mark_cell(0, _table, CREATE, CREATE);
    mark_cell(INSERT, _table, INTO, INTO);
    mark_cell(INTO, _table, SYM, 15);
    mark_cell(15, _table, VALUES, 16);
    mark_cell(16, _table, SYM, 17);
    mark_cell(17, _table, SYM, 17);
    mark_cell(SYM, _table, VALUES, VALUES);
    mark_cell(VALUES, _table, SYM, SYM);
    mark_cell(SELECT, _table, STAR, STAR);
    mark_cell(SELECT, _table, SYM, 18);
    mark_cell(18, _table, SYM, 18);
    mark_cell(18, _table, FROM, 21);
    mark_cell(21, _table, SYM, 22);
    mark_cell(22, _table, SYM, 22);
    mark_cell(22, _table, WHERE, 23);
    mark_cell(23, _table, SYM, 24);
    mark_cell(24, _table, SYM, 24);
    mark_cell(STAR, _table, FROM, 19);
    mark_cell(FROM, _table, SYM, SYM);
    mark_cell(19, _table, SYM, 20);
    mark_cell(20, _table, WHERE, 31);
    mark_cell(31, _table, SYM, 32);
    mark_cell(32, _table, SYM, 32);
    mark_cell(20, _table, SYM, 20);
    mark_cell(SYM, _table, WHERE, WHERE);
    mark_cell(SYM, _table, FROM, FROM);
    mark_cell(MAKE, _table, TABLE, TABLE);
    mark_cell(TABLE, _table, SYM, 29);
    mark_cell(29, _table, FIELDS, 30);
    mark_cell(30, _table, SYM, 40);
    mark_cell(40, _table, SYM, 40);    
}

int Parser::_table[MAX_ROWS][MAX_COLUMNS];