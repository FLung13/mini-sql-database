#include "stokenize.h"

STokenizer::STokenizer(){
    _pos = 0;
    _buffer[0] = '\0';
    make_table(_table);
}

STokenizer::STokenizer(char str[]){
    _pos = 0;
    strcpy(_buffer,str);
    make_table(_table);
    // print_table(_table);
}

bool STokenizer::done(){
    return !more();
}

bool STokenizer::more(){
    // cout << "pos: " << _pos << endl;
    bool result = _pos <= strlen(_buffer);
    if(!result){
        _pos = 0;
    }
    return result;
}

void STokenizer::set_string(char str[]){
    strcpy(_buffer, str);

}

void STokenizer::make_table(int _table[][MAX_COLUMNS]){
    init_table(_table);
    mark_fail(_table,0);
    mark_fail(_table,7);
    mark_fail(_table, 6);
    mark_success(_table, 10);
    mark_success(_table, 8);
    mark_success(_table, 25);
    mark_success(_table, 13);
    for(int i = 1; i < 6; i++){
        mark_success(_table, i);
    }
    mark_cells(0, _table, ALFA, TOKEN_ALPHA);
    mark_cells(0, _table, OPERATORS, TOKEN_OPERATOR);
    mark_cells(0, _table, SPACES, TOKEN_SPACE);
    mark_cells(0, _table, PUNC, TOKEN_PUNC);
    mark_cells(0, _table, COMILLAS, TOKEN_COMILLAS);
    mark_cells(0, _table, STAR, TOKEN_STAR);
    mark_cells(0, _table, PAREN, TOKEN_PAREN);
    mark_cells(TOKEN_COMILLAS, _table, ALFA, TOKEN_COMILLAS);
    mark_cells(TOKEN_COMILLAS, _table, SPACES, TOKEN_COMILLAS);
    mark_cells(TOKEN_COMILLAS, _table, PUNC, TOKEN_COMILLAS);
    mark_cells(TOKEN_COMILLAS, _table, COMILLAS, 10);
    mark_cells(TOKEN_ALPHA, _table, ALFA, TOKEN_ALPHA);
    mark_cells(TOKEN_OPERATOR, _table, OPERATORS, TOKEN_OPERATOR);

    mark_cells(0, _table, DIGITS, TOKEN_NUMBER);                   //state [0] --- DIGITS ---> [1]
    mark_cell(0, _table, 46, 5);                                  //state [0] --- '.' ------> [7] 
    mark_cells(TOKEN_NUMBER, _table, DIGITS, TOKEN_NUMBER);        //state [1] --- DIGITS ---> [1]
    mark_cell(1, _table, 46, 7);                                   //state [1] --- '.' ------> [7] 
    mark_cells(7, _table, DIGITS, 8);                              //state [7] --- DIGITS ---> [8]
    mark_cells(8, _table, DIGITS, 8);                              //state [8] --- DIGITS ---> [8]

}

bool STokenizer::get_t(char input[], int& pos, int& state, int table[][MAX_COLUMNS], string& token){

    string temps;
    int last_succesful_pos = 0;
    bool succesful_state = false;
    state = table[0][input[pos]];
    if(state == -1){
        pos++;
        return false;
    }
    if(input[pos] < 0){
        temps = temps + input[pos];
        pos = pos + 1;
        token = temps;
        return true;
    }
    
    while(state != -1 && input[pos] != '\0'){
        
        if (input[pos] != '\"')
        {
            temps = temps + input[pos];
        }
        
        pos++;
        if(table[state][0]){
            last_succesful_pos = pos;
            succesful_state = true;
            token = temps;
        }
        state = table[state][input[pos]];
    }
    if (succesful_state)
    {   
        pos = last_succesful_pos;
        return true;
    } 
    return false;
}


bool STokenizer::get_token(int& start_state, string& token){
    return get_t(_buffer, _pos, start_state, _table, token);
}

STokenizer& operator>>(STokenizer&s, Tokenizer& t){

    string temp = "";
    int sstate = s._table[0][s._buffer[s._pos]];
    int type = sstate;
    if (s._pos == strlen(s._buffer)){
        s._pos++;
        return s;
    }
    s.get_token(sstate, temp);
    //type = sstate;
    t = Tokenizer(temp, type);
    // cout << "buffer: " << s._buffer << endl;
    return s;
}


int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];