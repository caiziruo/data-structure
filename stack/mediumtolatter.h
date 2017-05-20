//
//  mediumtolatter.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef mediumtolatter_h
#define mediumtolatter_h

#include <iostream>
using namespace std;

#include "seq_stack.h"
#include <cmath>
#include <cstring>

class z2h {
    char * expression;
    
    enum token {OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL};
    
    char token2char(token a);
    
    token getOp(int &value);
    //return &value = 123456789 or token ()+-*/
    
public:
    z2h(const char * s)
    {
        expression = new char[strlen(s) + 1];
        strcpy(expression, s);
    }
    ~z2h() {delete expression;}
    
    void result();
};


char z2h::token2char(token a)
{
    if (a == ADD) return '+';
    else if (a == SUB) return '-';
    else if (a == MULTI) return '*';
    else if (a == DIV) return '/';
    else if (a == EXP) return '^';
    return '\0';
}

void z2h::result()
{
    token lastOp, topOp = EOL;
    int  CurrentValue;
    seq_stack<token> opStack;
    
    char * str = expression;
    
    while (true)
    {
        lastOp = getOp(CurrentValue);
        if (lastOp == EOL)
            break;
        switch (lastOp)
        {
            case EOL:
                break;
            case VALUE:
                cout << CurrentValue << ' ';
                break;
            case CPAREN:
                while (! opStack.isEmpty() && (topOp = opStack.pop()) != OPAREN )
                    cout << token2char(topOp);
                if (topOp != OPAREN)
                    cerr << "lack of left paren. " << endl;
                break;
            case OPAREN:
                opStack.push(OPAREN);
                break;
            case EXP:
                opStack.push(EXP);
                break;
            case MULTI: case DIV:
                while (! opStack.isEmpty() && opStack.top() >= MULTI)
                    cout << token2char(opStack.pop());
                opStack.push(lastOp);
                break;
            case ADD: case SUB:
                while (! opStack.isEmpty() && opStack.top() != OPAREN)
                    cout << token2char(opStack.pop());
                opStack.push(lastOp);
        }
    }
    
    while (! opStack.isEmpty())
        cout << token2char(opStack.pop());
    expression = str;
    cout << endl;
}
z2h::token z2h::getOp(int &value)
{
    while (* expression)
    {
        while ( * expression && * expression == ' ')
            ++expression;
        
        if (* expression <= '9' && * expression >= '0')
        {
            value = 0;
            while (* expression >= '0' && * expression <= '9')
            {
                value = value * 10 + * expression - '0';
                ++expression;
            }
            return VALUE;
        }
        
        switch (* expression)
        {
            case '(':
                ++expression; return OPAREN;
            case ')':
                ++expression; return CPAREN;
            case '+':
                ++expression; return ADD;
            case '-':
                ++expression; return SUB;
            case '*':
                ++expression; return MULTI;
            case '/':
                ++expression; return DIV;
            case '^':
                ++expression; return EXP;
        }
    }
    return EOL;
}


#endif /* mediumtolatter_h */
