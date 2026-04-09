#ifndef SQL_LUNG_H__
#define SQL_LUNG_H__
using namespace std;
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "../parser/parser.h"
#include "../table/table.h"

const vector<string> test = {

// 1. valid command:
"select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 2. Expected comma:
"select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 3. Expected: field name
"select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 4. Expected from:
"select lname, fname, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 5. Expected table name:
"select lname, fname, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 6. Expected condition:
"select lname, fname, major from student where",
// 7. Missing left paren:
"select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 8. Missing right paren:
"select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson",
// 9. : missing arg
"select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson",
// 10. :
"select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
// 11. : invalid cond
"select lname, fname, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson",
// 12. : missing arg
"select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson",
// 13. :missing arg
"select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or", 
// 14. :
"select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson"
};

class SQL
{
public:
    SQL();
    Table command(string comando);
    vectorlong select_recnos();
    void tablenames();
    void batch();
private:
    vector<Table> data;
    vectorlong select_recnost;
    map_sl tablemanage;
    vector<string>tablen;
    string datatxt = "databases.txt";
    static long TABLENR;
};

SQL::SQL()
{
    tablen.clear();
    string datatxt = "databases.txt";
    string line;
    int i = 0;
    ifstream database(datatxt.c_str());
    if (database.is_open())
    {
        // cout << "read file txt\n";
            while (getline (database,line))
            {
                tablen.push_back(line);
                i++;
            }
            database.close();
        // cout << "\nread file txt out\n";
    }
    tablenames();
    tablen.clear();
}

inline Table SQL::command(string comando)
{
    try
    {
        string str;
        string line;
        char s[1000];
        str = comando;
        strcpy(s, str.c_str());
        Parser parser(s);
        mmap_ss ptree;
        ptree = parser.parse_tree(); 
        // cout<<"input: ["<<s<<"]"<<endl<<endl;
        // ptree.print_lookup();
        // cout << endl<<endl;
        // cout << ptree.get("command") << endl;
        if (!ptree.contains("command"))
        {
            throw runtime_error("Expected command");
        }

        if (ptree.get("command")[0] == "make")
        {
            if (tablemanage.contains(ptree.get("table_name")[0]))
            {
                Table temp(ptree.get("table_name")[0]);
                return temp;
            }
            string tablename = ptree.get("table_name")[0];
            Table temp(tablename, ptree.get("col"));
            tablemanage.insert(tablename, TABLENR++);
            ofstream datawrite(datatxt, ios::app);
            bool exist = false;
            int i = 0;
            string line;
            vector<string> h;
            ifstream database(datatxt.c_str());
            if (database.is_open())
            {
                // cout << "read file txt\n";
                    while (getline (database,line))
                    {
                        h.push_back(line);
                        i++;
                    }
                    database.close();
                // cout << "\nread file txt out\n";
            }
            for (int j = 0; j < h.size(); j++)
            {
                if (h[j] == tablename)
                {
                    exist = true;
                }
            }
            if (!exist)
            {
                datawrite << tablename << endl;
            }
            datawrite.close();
            
            return temp;
        }
        else if (ptree.get("command")[0] == "insert")
        {
            if (!ptree.contains("values"))
            {
                string s = "values";
                throw s;
            }
            if (!ptree.contains("table_name"))
            {
                string s = "table name";
                throw s;
            }
            Table temp(ptree.get("table_name")[0]);
            temp.insert_into(ptree.get("values"));
            return temp;
        }
        else if (ptree.get("command")[0] == "select")
        {
            if (!ptree.contains("fields"))
            {
                string s = "field name";
                throw s;
            }
            if (!ptree.contains("table_name"))
            {
                string s = "table name";
                throw s;
            }
            Table temp(ptree.get("table_name")[0]);
            if (ptree.get("fields")[0] == "*")
            {
                if (!ptree.contains("where"))
                {
                    // cout << "here\n";
                    // cout << temp.select_all() << endl; 
                    temp.select_all();
                    // select_recnost = temp.select_recnos();
                    // for (int i = 0; i < temp.select_recnos().size(); i++)
                    // {
                    //     select_recnost.push_back(temp.select_recnos()[i]);
                    // }
                    select_recnost = temp.select_recnos();
                    // cout << temp.select_recnos() << endl;
                    return temp;
                }
                if (ptree.contains("where") && !ptree.contains("condition"))
                {
                    string s = "conditions";
                    throw s;
                }
                // cout << ptree.get("condition") << endl;
                // cout << temp.select(temp.get_fields(), ptree.get("condition")) << endl;
                temp.select(temp.get_fields(), ptree.get("condition"));
                // select_recnost = temp.select_recnos();
                // for (int i = 0; i < temp.select_recnos().size(); i++)
                // {
                //     select_recnost.push_back(temp.select_recnos()[i]);
                // }
                select_recnost = temp.select_recnos();
                // cout << temp.select_recnos() << endl;
            }
            else if (!ptree.contains("condition") && !ptree.contains("where"))
            {
                // cout << temp.select(ptree.get("fields")) << endl;
                temp.select(ptree.get("fields"));
                // select_recnost = temp.select_recnos();
                // for (int i = 0; i < temp.select_recnos().size(); i++)
                // {
                //     select_recnost.push_back(temp.select_recnos()[i]);
                // }
                select_recnost = temp.select_recnos();
                // cout << temp.select_recnos() << endl;
                return temp;
            }        
            else
            {
                if (ptree.contains("where") && !ptree.contains("condition"))
                {
                    string s = "conditions";
                    throw s;
                }
                
                // cout << temp.select(ptree.get("fields"), ptree.get("condition")) << endl;
                temp.select(ptree.get("fields"), ptree.get("condition"));
                // for (int i = 0; i < temp.select_recnos().size(); i++)
                // {
                //     select_recnost.push_back(temp.select_recnos()[i]);
                // }
                select_recnost = temp.select_recnos();
                // cout << temp.select_recnos() << endl;
            }
            return temp;
        }
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << '\n'; 
    }
    
    catch(string s)
    {
        select_recnost.clear();
        cout << "Expected " << s << endl; 
    }
    
    
    Table temp;
    return temp;
    
}

inline vectorlong SQL::select_recnos()
{
    return select_recnost;
}

inline void SQL::tablenames()
{
    // tablemanage.print_lookup();
    cout << "------ SQL Tables I Manage: --------" << endl;

    for (int i = 0; i < tablen.size(); i++)
    {
        cout << tablen[i] << endl;
    }
    
    cout << "---------------------------\n";
}

inline void SQL::batch()
{
    
    for (int i = 0; i < test.size(); i++)
     {
            cout << i << ": ";
          cout << ">" << test[i] << endl;
          command(test[i]);
     }
}



long SQL::TABLENR = 1;

#endif