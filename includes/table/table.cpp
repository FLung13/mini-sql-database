#include "table.h"

void Table::insert_into(vectorstr s)                                                                        // INSERT INTO BINARY FILE NEW RECORD
{
    open_fileRW(f, (filename+".bin").c_str());                                                              // OPEN FILE
    
    // recno.push_back(_records.write(f));
    recno.push_back(FileRecord(s).write(f));                                                                // SAVE THE RECORD NUMBERS AND WRITE TO THE FILE
    for (int i = 0; i < s.size(); i++)
    {
        indices[i].insert(s[i],recno.size()-1);                                                             // CREATE THE INDICES MULTIMAP
    }
    last_recordn = recno.back();                                                                            // SET NUMBER OF THE LAST RECORD SAVED
    f.close();                                                                                              // CLOSE FILE
}

Table Table::select(vectorstr s, char str1[], char str2[], char str3[])
{
    // cout << table_name << endl;
    // selected_records.clear();                                                                               // CLEAR SELECTED RECORDS PREVIOUSLY USED
    Table temp("_selected_table" + to_string(SERIAL), s);                                                   // CREATE A TEMPORAL TABLE
    temp.reindex(s, map_records, indices);                                                                  // REINDEX TEMPORAL TABLE WITH FIELD NAMES GIVEN
    long key = temp.map_records[str1];                                                                      // GET KEY FROM THE MAP OF RECORDS
    mmap_sl::Iterator it;                                                                                       
    mmap_sl::Iterator itend = indices[map_records[str1]].end();                                             // SET ITERATOR TO THE END OF MMAP
    if (str2[0] == '=')                                                                                     // RELATIONAL "="
    {
        selected_records = temp.indices[key][str3];
    } 
    else if (str2[0] == '>' && str2[1] == '=')                                                              // RELATION ">="
    {
        it = indices[map_records[str1]].lower_bound(str3);
        for (;it != itend; it++)
        {
            MPair<string,long> holder = *it;
            for (int i = 0; i < holder.value_list.size(); i++)
            {
                selected_records.push_back(holder.value_list[i]);
            }
        }
    } else if (str2[0] == '>')                                                                              // RELATION ">"
    {
        it = indices[map_records[str1]].upper_bound(str3);
        for (;it != itend; it++)
        {
            MPair<string,long> holder = *it;
            for (int i = 0; i < holder.value_list.size(); i++)
            {
                selected_records.push_back(holder.value_list[i]);
            }
        }
    }
    else if (str2[0] == '<' && str2[1] == '=')                                                              // RELATION "<="
    {
        it = indices[map_records[str1]].begin();
        itend = indices[map_records[str1]].upper_bound(str3);
        for (;it != itend; it++)
        {
            MPair<string,long> holder = *it;
            for (int i = 0; i < holder.value_list.size(); i++)
            {
                selected_records.push_back(holder.value_list[i]);
            }
        }
    } else if (str2[0] == '<')                                                                              // RELATION "<"
    {
        it = indices[map_records[str1]].begin();
        itend = indices[map_records[str1]].lower_bound(str3);
        for (;it != itend; it++)
        {
            MPair<string,long> holder = *it;
            for (int i = 0; i < holder.value_list.size(); i++)
            {
                selected_records.push_back(holder.value_list[i]);
            }
        }
    }
    
    vect_tbl(temp, selected_records, s);                                                                    // CONVERT SELECTED RECORDS INTO TABLE
    
    return temp;
}

Table Table::select(vectorstr s, queuetk p)                                                                 // SELECT WITH FIELDS NAME AND A QUEUE OF TOKENS
{
    Table temp("_selected_table_" + to_string(SERIAL), s);                                                   // CREATE TEMPORAL TABLE
    RPN rpn(p);                                                                                             // RPN WITH QUEUE OF TOKENS
    temp.reindex(s, map_records, indices);                                                                  // REINDEX TEMPORAL TABLE
    selected_records = rpn(s, temp.map_records, temp.indices, indices, map_records);                        // GET SELECTED RECORDS FROM RPN
    vect_tbl(temp, selected_records, s);                                                                    // CONVERT SELECTED RECORDS INTO TABLE
    return temp;
}

Table Table::select(vectorstr s, vectorstr c)                                                               // SELECT WITH FIELD NAMES AND A STRING OF CONDITIONS
{
    Table temp("_selected_table_" + to_string(SERIAL), s);                                                   // CREATE TEMPORAL TABLE
    ShuntingYard sy(c);                                                                                     // CONVERT THE STRING OF CONDTIONS TO QUEUE OF TOKENS
    queuetk p;                                                                                              
    p = sy.postfix();                                                                                       // GET QUEUE OF TOKENS FROM SY
    RPN rpn(p);                                                                                             // INITIALIZE RPN
    temp.reindex(s, map_records, indices);                                                                  // REINDEX TEMPORAL TABLE
    selected_records = rpn(s, temp.map_records, temp.indices, indices, map_records);                        // GET SELECTED RECORDS FROM RPN
    vect_tbl(temp, selected_records, s);                                                                    // CONVERT SELECTED RECORDS INTO TABLE
    return temp;
}

Table Table::select(vectorstr s)                                                                            // SELECT WITH FIELD NAMES
{
    Table temp("_selected_table_" + to_string(SERIAL), s);                                                   // CREATE TEMPORAL TABLE
    temp.reindex(s, map_records, indices);                                                                  // REINDEX TEMPORAL TABLE
    selected_records = select_all().select_recnos();
    vect_tbl(temp, selected_records, s);                                                                    // CONVERT SELECTED RECORDS INTO TABLE
    return temp;
}

void Table::vect_tbl(Table &t, vectorlong l, vectorstr s)                                                   // CONVERT SELECTED RECORDS INTO TABLE
{
    open_fileRW(f, (filename+".bin").c_str());                                                              // OPEN ORIGINAL FILE
    FileRecord r;                                                                                            
    for (int i = 0; i < selected_records.size(); i++)                                                       // FOR LOOP TO READ THE SELECTED RECORDS
    {
       r.read(f, selected_records[i]);                                                                      // READ RECORD I
       vectorstr temps;
       for (int j = 0; j < s.size(); j++)                                                                   // FOR LOOP TO GET IN ORDER OF THE FIELD NAME
       {
        temps.push_back(r._record[map_records[s[j]]]);
       }
    //    cout << temps << endl;
       t.insert_into(temps);                                                                                // INSERT RECORDS INTO NEW FILE AND TABLE
    //    cout << "temp\n";
    //    cout << temp << endl;
    //    cout << "reading record " << selected_records[i] << ": " << r << endl;
    }
    f.close();                                                                                              // CLOSE FILE
}

vector<long> Table::select_recnos()                                                                         // RETURN SELECTED RECORDS
{
    return selected_records;                                        
}

void Table::set_fields(const vectorstr fields)                                                              // SET FIELDS OF THE TABLE
{
    for (int i = 0; i < fields.size(); i++)                                                                 // FOR LOOP TO ITERATE EVERY FIELD NAME GIVEN
    {
        map_records.insert(fields[i], i);                                                                   // CREATE/OVERWRITE MAP OF THE FIELD NAMES
        field_names.push_back(fields[i]);                                                                   // PUSH TO THE FIELD NAMES VECTOR
        indices.push_back(mmap_sl());                                                                       // GIVE SPACE TO THE INDICES VECTOR
    }
}

vector<string> Table::get_fields()                                                                          // GET THE FIELD NAME FROM THE TABLE
{
    return field_names;
}

Table Table::select_all()                                                                                   // SELECT ALL RECORDS
{
    Table sall(filename);
    selected_records = sall.select_recnos();
    return sall;
}

void Table::reindex()                                                                                       // REINDEX
{
    open_fileRW(f, (filename + ".bin").c_str());                                                            // OPEN ORIGINAL FILE
    FileRecord rec;
    int i = 0;
    rec.read(f, i);                                                                                         // READ FILE
    while (!f.eof())                                                                                        // WHILE LOOP TO READ
    {
       vectorstr temps;
       for (int j = 0; j < field_names.size(); j++)                                                         // FOR LOOP TO SAVE EVERY RECORD RED
       {
        temps.push_back(rec._record[j]);
       }
    //    cout << temps << endl;
       for (int k = 0; k < temps.size(); k++)                                                               // INSERT TO THE INDICES
        {
            indices[k].insert(temps[k],i);
        }
    //    cout << "reading record " << i << ": " << rec << endl;
       i++;
       rec.read(f, i);                                                                                      // READ NEXT LINE OF THE FILE
    }
    f.close();                                                                                              // CLOSE FILE
    // cout << "reindex out\n";
}

void Table::reindex(const vectorstr fields, map_sl map, const vector<mmap_sl> &_indices)                    // REINDEX WITH NEW FIELD NAME, TEMPORAL TABLE MAP AND INDICES
{
    for (int i = 0; i < fields.size(); i++)                                                                 // FOR LOOP TO ITERATE THROUGH THE NEW FIELD NAMES ORDER
    {
        if (map.contains(fields[i]))                                                                        // CHECK IF THE FIELD NAME EXIST
        {
            long key = map_records.get(fields[i]);                                                          // REMAP
            indices[key] = _indices[map.get(fields[i])];                                                    // REMAP
            // cout << fields[i] << endl;
            // cout << map_records << endl;
            // cout << _indices[map.get(fields[i])] << endl;
            // cout << indices[key] << endl;
        }
    }
}

long Table::SERIAL = 1000;