#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "includes/sql/sql.h"

using namespace std;

const vector<string> create_list = {

/*00*/     "make table employee fields  last,       first,         dep,      salary, year",
/*01*/     "insert into employee values Blow,       Joe,           CS,       100000, 2018",
/*02*/     "insert into employee values Blow,       JoAnn,         Physics,  200000, 2016",
/*03*/     "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
/*04*/     "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018",

/*05*/     "make table student fields  fname,          lname,    major,    age",
/*06*/     "insert into student values Flo,            Yao, 	Art, 	20",
/*07*/     "insert into student values Bo, 		     Yang, 	CS, 		28",
/*08*/     "insert into student values \"Sammuel L.\", Jackson, 	CS, 		40",
/*09*/     "insert into student values \"Billy\",	     Jackson, 	Math,	27",
/*10*/     "insert into student values \"Mary Ann\",   Davis,	Math,	30",

// /*11*/     "select * from employee",
// /*12*/     "select last, first, age from employee",
// /*13*/     "select last from employee",
// /*14*/     "select * from employee where last = Johnson",
// /*15*/     "select * from employee where last=Blow and major=\"JoAnn\"",

// /*16*/     "select * from student",
// /*17*/     "select * from student where major = \"CS\" and age < 25",
// /*17*/     "select * from student where (major=CS or major=Art)",
// /*18*/     "select * from student where lname>J",
// /*19*/     "select * from student where lname>J and (major=CS or major=Art)"
// /*20*/     "select * from employee where dep = CS or year > 2024 and year < 2018 or salary >= 3"

};

const int MAKE_TABLE_COMMANDS = 11;
const int SELECT_COMMANDS = 20;

int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;
    bool debug = false;
    SQL sql;
    Table t;
    char ans;
    char line[MAX_BUFFER];
    int cn = 0;
    cout << "\n\nWrite a [C]ommand, [B]atch file, create [L]ist, e[S]pecial case,e[X]it\n";
    cin >> ans;
    while (ans != 'x' || ans != 'X')
    {
        if (ans == 'c' || ans == 'C')
        {
            cout << "Write your command (select, insert into, make)\n";
            cin >> line;
            cin.getline(line, MAX_BUFFER);
            cout << cn << ": >" << line << endl; 
            t = sql.command(line);
          cout << "records selected: "<<sql.select_recnos() << endl;
        }
        if (ans == 'b' || ans == 'B')
        {
            cout << "Calling batch function\n";
            sql.batch();
        }
        if (ans == 'l' || ans == 'L')
        {
            cout << "Create list\n";
            cout << ">" << create_list[0] << endl;
            sql.command(create_list[0]);
            cout << "table created." << endl<<endl;

            for (int i = 0; i < MAKE_TABLE_COMMANDS; i++)
            {
                cout << ">" << create_list[i] << endl;
                sql.command(create_list[i]);
            }

            cout << endl
                << endl;
            sql.tablenames();
            for (int i = MAKE_TABLE_COMMANDS; i < create_list.size(); i++)
            {
                cout << "\n>" << create_list[i] << endl;
                if (debug)
                    cout<< sql.command(create_list[i])<<endl;
                else
                    t = sql.command(create_list[i]);
                cout << "records selected: "<<sql.select_recnos() << endl;
            }
        }
        if (ans == 's' || ans == 'S')
        {
            t = sql.command("select * from employee");
            t = sql.command("select * from employee dep = CS or year > 2024 and year < 2018 or salaru >= 3");
            cout << "records selected: "<<sql.select_recnos() << endl;
        }
        
        
        if (ans == 'x' || ans == 'X')
        {
            break;
        }
        cout << "\n\nWrite a [C]ommand, [B]atch file, create [L]ist, e[S]pecial case,e[X]it\n";
        cin >> ans;
        
    }
    
        
    
    
    
    //  cout << ">" << create_list[0] << endl;
    //  sql.command(create_list[0]);
    //  cout << "basic_test: table created." << endl<<endl;

    //  for (int i = 0; i < MAKE_TABLE_COMMANDS; i++)
    //  {
    //       cout << ">" << create_list[i] << endl;
    //       sql.command(create_list[i]);
    //  }

    //  cout << endl
    //       << endl;
    //  sql.tablenames();
    //  for (int i = MAKE_TABLE_COMMANDS; i < create_list.size(); i++)
    //  {
    //       cout << "\n>" << create_list[i] << endl;
    //       if (debug)
    //            cout<< sql.command(create_list[i])<<endl;
    //       else
    //            t = sql.command(create_list[i]);
    //       cout << "basic_test: records selected: "<<sql.select_recnos() << endl;
    //  }
    //  sql.batch();

     cout << "\n\n\n----- PROGRAM END --------" << endl;
     return true;
    cout << "\n\n\n=====================" << endl;
    return 0;
}
