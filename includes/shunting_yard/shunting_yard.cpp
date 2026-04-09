#include "shunting_yard.h"

ShuntingYard::ShuntingYard(vector<string> conditions){
    s = conditions;
    // int countleft = 0;
    // int countright = 0;
    for (int i = 0; i < s.size(); i++)                                                                  // FOR LOOP TO ITERATO OVER THE CONDITIONS
    {
        if (s[i] == ">" || s[i] == "<"|| s[i] == ">=" || s[i] == "<=" || s[i] == "=")                   // RELATIONAL OPERATORS
        {
            _infix.push(new Relational(s[i]));
        }
        else if (s[i] == "and" || s[i] == "or")                                                         // LOGICAL OPERATORS
        {
            _infix.push(new Logical(s[i]));
        }
        else if (s[i] == "(")                                                                           // LEFT PARENTHESIS
        {
            _infix.push(new LParen(s[i]));
        }
        else if (s[i] == ")")                                                                           // RIGHT PARENTHESIS
        {
            _infix.push(new RParen(s[i]));
        }
        else                                                                                            // TOKEN STRINGS
        {
            _infix.push(new TokenStr(s[i]));
        }
    }

    // if (countleft != countright)
    // {
    //     if (countleft < countright)
    //     {
    //         string s = "Left parenthesis";
    //         throw s;
    //     }
    //     else
    //     {
    //         string s = "Right parenthesis";
    //         throw s;
    //     }
        
        
    // }
    
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*> &infix)
{
    Queue<Token*>::Iterator it = infix.begin();
    while(it != infix.end()){
        // assert(infix.begin() && "Queue begin is nullptr");
        Token* front = *it;
        int type = front->type();                                                                               // GET TOKEN TYPE TO USE IN THE SWITCH CASE
        switch (type)
        {
            case 6:
                // Token string
                // cout << "TOKENSTR: " << static_cast<string>(front->getTokenStr()) << endl;
                result.push(front);                                                                             // PUSH TO THE QUEUE
                break;
            case 1:
                // Relational
                // cout << "RELATIONAL: " << static_cast<string>(front->getRelational()) << endl;               // CHECK PRECENDENCE AND LEFT PARENTHESIS
                while(!opers.empty() && opers.top()->getLeftParenthesis() != '(' && front->precedence() >= opers.top()->precedence()){
                    result.push(opers.pop());
                }
                opers.push(static_cast<Relational*>(front));                                                    // PUSH TO THE STACK OPERATORS
                break;
            case 5:
                // Logical
                // cout << "LOGICAL: " << static_cast<string>(front->getLogical()) << endl;                    // CHECK PRECENDENCE AND LEFT PARENTHESIS
                while(!opers.empty() && opers.top()->getLeftParenthesis() != '(' && front->precedence() >= opers.top()->precedence()){  
                    result.push(opers.pop());                                                               
                }
                opers.push(static_cast<Logical*>(front));                                                      // PUSH TO THE STACK OPERATORS
                break;
            case 15:                                                                                           // LEFT PARENTHESIS
                // Left parenthesis
                // cout << "LEFT PARENTHESIS: " << static_cast<char>(front->getLeftParenthesis()) << endl;
                opers.push(static_cast<LParen*>(front));
                break;
            case 10:                                                                                           // RIGHT PARENTHESIS
                // Right parenthesis
                while(opers.top()->getLeftParenthesis() != '('){                                               // Push every operator to the queue from the stack
                    // assert(!opers.empty());                                                                 // until you reach the left parenthesis
                    if (opers.empty())
                    {
                        string s = "Left parenthesis";
                        throw s;
                    }
                    result.push(opers.pop());
                    if (opers.empty())
                    {
                        string s = "Left parenthesis";
                        throw s;
                    }
                }
                if(opers.top()->getLeftParenthesis() == '('){                                                  // Pop left parenthesis
                    opers.pop();
                }
                break;
            default:
                break;
        }
        it++;
    }

    while(!opers.empty()){                                                                                      // Pop all the stack and push it to the queue
        if (opers.top()->getLeftParenthesis() == '(')
        {
            string s = "Right parenthesis";
            throw s;
        }
        
        result.push(opers.pop());
    }
    // Queue<Token*>::Iterator ite = result.begin();
    // cout << "========\n";
    // while (ite != result.end())
    // {
    //     cout << **ite << endl;
    //     ite++;
    // }

    return result;
}
