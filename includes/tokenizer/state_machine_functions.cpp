#include "state_machine_functions.h"

void init_table(int _table[][MAX_COLUMNS]){
    for(int i = 0; i < MAX_ROWS; i++){
        for(int j = 0; j < MAX_COLUMNS; j++){
            _table[i][j] = -1;
        }
    }
}

void mark_success(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 1;
}

void mark_fail(int _table[][MAX_COLUMNS], int state){
    _table[state][0] = 0;
}

bool is_success(int _table[][MAX_COLUMNS], int state){
    if(_table[state][0]){
        return true;
    }
    return false;
}

void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state){
    for (int i = from; i < to; i++)
    {
        _table[row][i] = state;
    }
}

void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state){
    int pos = 0;
    while (columns[pos])
    {
        _table[row][columns[pos]] = state;
        pos++;
    }
}

void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state){
    table[row][column] = state;
}

void print_table(int _table[][MAX_COLUMNS]){
    int row, column;

    for (row = 0; row < 9; row++) // For loop to display Table
    {
        for (column = 0; column < 128; column++)
            cout << "|" << _table[row][column] << "|";
        cout << endl;
    }

}

void show_string(char s[], int _pos){
    for(int i = 0; i < _pos; i++){
        cout << s[i];
    }
    cout << "   " << "pos: " << _pos << endl; 
    for(int j = 0; 0 < _pos-1; j++){
        cout << " ";
    }
    cout << "^";
}
