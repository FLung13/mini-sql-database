#ifndef TABLE_LUNG_H__
#define TABLE_LUNG_H__
using namespace std;
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "../../includes/binary_files/file_record.h"
#include "../../includes/binary_files/utilities.h"
#include "typedefs.h"
#include "../../includes/token/token.h"

class Table
{
public:
    Table()
    {
    }

    Table(const string& s)                                                                          // FILENAME CTOR
    {
        SERIAL += 2;
        string line;
        filename = s;
        table_name = s;
        last_recordn = 0;
        int i = 0;
        open_fileRW(f, (filename + ".bin").c_str());
        ifstream readfiletxt(table_name +"_fields.txt");                                            // READ A TXT FILE WITH THE FIELD NAMES AND FILL TABLE MAP AND INDICES
        if (readfiletxt.is_open())
        {
        // cout << "read file txt\n";
            while (getline (readfiletxt,line) )                                                     // GET NEW LINE FROM THE TXT FILE
            {
                field_names.push_back(line);
                map_records.insert(field_names[i], i);                                              // INSERT FIELDS TO THE MAP 
                indices.push_back(mmap_sl());
                i++;
            }
            readfiletxt.close();
        // cout << "\nread file txt out\n";
        }
        int j = 0;
        FileRecord rec;
                                                                                                    //the famous Golden While Loop:
        rec.read(f, j);                                                                             //read the first record
        while (!f.eof())
        {
            selected_records.push_back(j);
            recno.push_back(j);
            j++;
            rec.read(f, j);                                                                         //read next record.
        }
        f.close();
        // set_fields(field_names);
        
        reindex();
    }

    Table(const string& str, const vectorstr fields)                                                // TABLE CTOR WITH TABLE NAME AND FIELD NAMES
    {
        SERIAL += 2;                                                            
        filename = str;
        table_name = str;
        last_recordn = 0;
        set_fields(fields);                                                                         // SET FIELDS TO THE TABLE
        open_fileW(f, (table_name + ".bin").c_str());                                               // ERASE ALL INFORMATION OF THE FILE
        f.close();
        ofstream filefields((table_name + "_fields.txt").c_str());                                  // CREATE A TXT FILE WITH THE FIELD NAMES
        
        for (int i = 0; i < fields.size(); i++)                                                     // WRITE TO THE FILE
        {
            filefields << fields[i] << endl;
        }
        filefields.close();                                                                         // CLOSE FILE
    }

    void insert_into(vectorstr s);
    Table select(vectorstr s, char str1[], char str2[], char str3[]);
    Table select(vectorstr s, queuetk p);
    Table select(vectorstr s, vectorstr c);
    Table select(vectorstr s);
    void vect_tbl(Table &t, vectorlong l, vectorstr s);
    vector<long> select_recnos();
    void set_fields(const vectorstr fields);
    vector<string> get_fields();
    Table select_all();
    void reindex();
    void reindex(const vectorstr fields, map_sl map, const vector<mmap_sl> &_indices);
    // Table select_all() const;

    friend ostream& operator<<(ostream& outs, const Table& t)
    {
        outs << "\nTable name: " << t.filename << ", records: " << t.recno.size() << endl; 
        outs << setw(25) << "record";
        for (int i = 0; i < t.field_names.size(); i++)
        {
            outs << setw(25) << t.field_names[i]; 
        }
        outs << endl << endl;
        
        fstream l;
        FileRecord rec;
        open_fileRW(l, (t.filename+".bin").c_str());
        int i = 0;
        //the famous Golden While Loop:
        rec.read(l, i);     //read the first record
        while (!l.eof())
        {
            outs <<setw(25)<< i << rec << endl;
            i++;
            rec.read(l, i);         //read next record.
        }
        outs << endl;
        l.close();
        // for (int i = 0; i < t.recno.size(); i++)
        // {
        //    outs << setw(25) << i << t. << endl;
        // }
        return outs;
    }


private:

    fstream f;
    string filename;
    vectorlong recno;
    vectorlong selected_records;
    vectorstr field_names;
    vector<mmap_sl> indices;
    map_sl map_records;
    long last_recordn;
    string table_name;
    static long SERIAL;

};




#endif