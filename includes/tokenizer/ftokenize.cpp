#include "ftokenize.h"

FTokenizer::FTokenizer(char* fname){
    _f.open(fname);
    if (_f.fail()){
        cout<<"file failed to open."<<endl;
        assert(false);
    }
    _pos = 0;
    _more = true;
    _blockPos = 0;
    get_new_block();
}


Tokenizer FTokenizer::next_token(){
    Tokenizer t;
    if(_stk.done()){
        if(!get_new_block()){
            _more = false;
            return Tokenizer();
        }
    }
    _stk >> t;
    return t;
}

bool FTokenizer::more(){
    return _more;
}

int FTokenizer::pos()
{
    return _pos;
}

int FTokenizer::block_pos()
{
    return _blockPos;
}

bool FTokenizer::get_new_block(){
    if(_f.eof()){
        _f.close();
        return false;
    }
    cout << "\nNEW BLOCK-----------------------------" << endl;
    char fileblock[MAX_BLOCK];
    _f.read(fileblock, MAX_BLOCK-1);
    fileblock[_f.gcount()] = '\0';
    // cout << "buffer: " << fileblock << endl;
    // cout << "count: " << _f.gcount() << endl;
    _stk.set_string(fileblock);
    return true;
}

FTokenizer& operator>>(FTokenizer&f, Tokenizer& t){
    t = f.next_token();
    return f;
}