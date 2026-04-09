#include "rpn.h"

RPN::RPN(){

}

RPN::RPN(Queue<Token*> postfix): _postfix(postfix){
    
}

vector<long> RPN::operator()(vector<string> s, Map<string, long> &tempmap, vector<MMap<string, long>> &tempindices, vector<MMap<string, long>> &indices, Map<string, long> &map){
    Queue<Token*>::Iterator it = _postfix.begin();
    string Relation;
    string condition;
    string field;
    string Logical;
    vector<long> temporal_sr;
    vector<long> vecone;
    vector<long> vectwo;
    long key;
    mmap_sl::Iterator mmit;
    mmap_sl::Iterator itend;
    // debug = true;
    for(it; it != _postfix.end(); it++){
        // assert(_postfix.begin() && "Queue begin is nullptr");
        Token* front = *it;
        int type = static_cast<Token*>(front)->type();                                  // Get the type of the token to use in the switch case
        temporal_sr.clear();                                                            // Clear previously used vector of long
        vecone.clear();                                                                 // Clear previously used vector of long
        vectwo.clear();                                                                 // Clear previously used vector of long
        switch (type)
        {
        case 1:                                                                         // RELATIONAL
            if (debug)
            {
                cout << "RELATIONAL: " << static_cast<string>(front->getRelational()) << endl;
            }
            Relation = front->getRelational();                                          // Gets relational operator
            field = tempvectors.front();                                                // Get field names
            tempvectors.erase(tempvectors.begin());                                     // Erase from the vector the fields names
            if (tempvectors.empty())
            {
                string s = "Condition / Field name";
                throw s;
            }
            condition = tempvectors.front();                                            // Get conditions
            tempvectors.erase(tempvectors.begin());                                     // Erase from the vector the conditions
            key = tempmap[field];                                                       // Get key for the field in the map
            itend = indices[map[field]].end();                                          // Setting iterator to the end of the mmap of the key field 
            // cout << indices[map[field]] << endl << endl;
            if (Relation == "=")                                                        // Relational "="
            {
                temporal_sr = tempindices[key][condition];
            } 
             else if (Relation == ">=")                                                 // Relational ">="
            {
                mmit = indices[map[field]].lower_bound(condition);                      // Use lower bound to iterate and now when to finsh
                for (;mmit != itend; mmit++)
                {
                    MPair<string,long> holder = *mmit;
                    for (int i = 0; i < holder.value_list.size(); i++)
                    {
                        temporal_sr.push_back(holder.value_list[i]);
                    }
                }
            } 
            else if (Relation == ">")                                                   // Relational ">"
            {
                // cout << indices[map[field]] << endl;
               mmit = indices[map[field]].upper_bound(condition);                       // Use upper bound to iterate and now when to finsh
                // cout << *mmit << endl;
                for (;mmit != itend; mmit++)
                {
                    // cout << *mmit << endl;
                    MPair<string,long> holder = *mmit;
                    for (int i = 0; i < holder.value_list.size(); i++)
                    {
                        temporal_sr.push_back(holder.value_list[i]);
                    }
                }
            }
            else if (Relation == "<=")                                                  // Relational "<="
            {
                mmit = indices[map[field]].begin();                                     // Setting iterator to the beginning of the mmap of the key field 
                itend = indices[map[field]].upper_bound(condition);                     // Use upper bound to iterate and now when to finsh
                for (;mmit != itend; mmit++)
                {
                    MPair<string,long> holder = *mmit;
                    for (int i = 0; i < holder.value_list.size(); i++)
                    {
                        temporal_sr.push_back(holder.value_list[i]);
                    }
                }
            } 
            else if (Relation == "<")                                                   // Relational "<"
            {
                // cout << "Relational <\n\n";
                mmit = indices[map[field]].begin();                                     // Setting iterator to the beginning of the mmap of the key field 
                // cout << indices[map[field]] << endl;
                itend = indices[map[field]].lower_bound(condition);                     // Use lower bound to iterate and now when to finsh
                for (;mmit != itend; mmit++)
                {
                    MPair<string,long> holder = *mmit;
                    for (int i = 0; i < holder.value_list.size(); i++)
                    {
                        temporal_sr.push_back(holder.value_list[i]);
                    }
                }
            } 
            else
            {
                string s = "Relational";
                throw s;
            }
            result.push(temporal_sr);
            break;
        case 5:                                                                         // LOGICAL
            if (debug)
            {
                cout << "LOGICAL: " << static_cast<string>(front->getLogical()) << endl;
            }
            Logical = front->getLogical();                                              // Get "AND" / "OR"
            vecone = result.pop();                                                      //Pop twice
            if (result.empty())
            {
                string s = "Condition";
                throw s;
            }
            vectwo = result.pop();
            // cout << "vecone: " << vecone << endl;
            // cout << "vectwo: " << vectwo << endl;
            if (Logical == "and")                                                      // Check logical "AND"
            {
                // cout << "and\n"; 
                for (int i = 0; i < vectwo.size(); i++)                                // For loop to i[N]tersect the selected records
                {
                    bool equal = false;
                    for (int j = 0; j < vecone.size(); j++)
                    {
                        if (vectwo[i] == vecone[j])
                        {
                            equal = true;
                        }
                    }
                    if (equal)
                    {
                        temporal_sr.push_back(vectwo[i]);
                    }
                }
            } 
            else if (Logical == "or")                                                  // Check logical "OR"
            {
                // cout << "or\n"; 
                if (vectwo.size() < vecone.size())                                     // Check which one is bigger also checks for (empty or not)
                {
                    temporal_sr = vecone;
                    for (int i = 0; i < vectwo.size(); i++)                            // For loop to [U]nion the selected records
                    {
                        bool alrthere = false;
                        for (int j = 0; j < temporal_sr.size(); j++)
                        {
                            if (vectwo[i] == temporal_sr[j])
                            {
                                alrthere = true;
                            }
                        }
                        if (!alrthere)
                        {
                            temporal_sr.push_back(vectwo[i]);
                        }
                    }
                }
                else
                {
                    temporal_sr = vectwo;
                    for (int i = 0; i < vecone.size(); i++)                            // For loop to [U]nion the selected records
                    {
                        bool alrthere = false;
                        for (int j = 0; j < temporal_sr.size(); j++)
                        {
                            if (vecone[i] == temporal_sr[j])
                            {
                                alrthere = true;
                            }
                        }
                        if (!alrthere)
                        {
                            temporal_sr.push_back(vecone[i]);
                        }
                    }
                }
            }
            if (temporal_sr.size() > 0)                                                // Sort the selected records in ascendant order
            {
                sort(temporal_sr.begin(), temporal_sr.end());
            }
            result.push(temporal_sr);                                                 // Push to the result stack
            
            break;
            case 6:
            tempvectors.push_back(front->getTokenStr()); // String tokens
            break;
        }

    }
    if(result.size() > 1){
        string s = "Relational / Logical";
        throw s;
    }
    temporal_sr = result.pop();
    if (temporal_sr.size() > 0)                                                // Sort the selected records in ascendant order
    {
        sort(temporal_sr.begin(), temporal_sr.end());
    }
    result.push(temporal_sr);
    return result.top();
}

void RPN::set_input(Queue<Token*> postfix){ // Set input of posfix
    _postfix = postfix;
}
