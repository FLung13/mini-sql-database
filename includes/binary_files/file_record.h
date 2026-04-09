#ifndef FILE_RECORD_LUNG_H__
#define FILE_RECORD_LUNG_H__
using namespace std;
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

class FileRecord{
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    FileRecord(){
        // _record[0] = '\0';
        for (int i = 0; i < MAX; i++)
        {
            _record[i][0] = '\0';
        }
        recno = -1;
        // infono = 4;
        // sizew = 0;
    }

    FileRecord(char str[]){
        strncpy(_record[0], str, MAX);
    }
    FileRecord(string s){
        strncpy(_record[0], s.c_str(), MAX);
    }
    
    FileRecord(vector<string> s){
        for (int i = 0; i < s.size(); i++)
        {
            strncpy(_record[i], s[i].c_str(), MAX);   
        }
        // infono = s.size();
        for (int i = s.size(); i < MAX; i++)
        {
            _record[i][0] = '\0';
        }
        
    }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs,
                               const FileRecord& r);

    static const int MAX = 100;
    int recno;
    char _record[MAX+1][MAX+1];
    // char _twod_record[MAX+1][MAX+1];
    // int infono;
    // int sizew;
};

#endif