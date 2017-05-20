//
//  lattertoresult.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef lattertoresult_h
#define lattertoresult_h


#include <iostream>
using namespace std;
#include "seq_stack.h"
#include <cmath>


class h2result
{
private:
    char * expression;
    
    enum token {OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL};
    
    token getOp(int &value);
    
public:
    h2result(const char * s)
    {
        expression = new char[strlen(s) + 1];
        strcpy(expression, s);
    }
    ~h2result() {delete expression;}
    
    int result();
};

int h2result::result()
{
    token lastOp;
    int CurrentValue;
    seq_stack<int> dataStack;
    
    char * str = expression;
    
    while (true)
    {
        lastOp = getOp(CurrentValue);
        if (lastOp == EOL)
            break;
        int num2;
        int num1;
        switch (lastOp)
        {
            case OPAREN:
                break;
            case CPAREN:
                break;
            case EOL:
                break;
            case VALUE:
                dataStack.push(CurrentValue);
                break;
            case EXP:
                num2 = dataStack.pop();
                num1 = dataStack.pop();
                dataStack.push(pow(num1, num2));
                break;
            case MULTI:
                num2 = dataStack.pop();
                num1 = dataStack.pop();
                dataStack.push(num1 * num2);
                break;
            case DIV:
                num2 = dataStack.pop();
                num1 = dataStack.pop();
                dataStack.push(num1 / num2);
                break;
            case ADD:
                num2 = dataStack.pop();
                num1 = dataStack.pop();
                dataStack.push(num1 + num2);
                break;
            case SUB:
                num2 = dataStack.pop();
                num1 = dataStack.pop();
                dataStack.push(num1 - num2);
                break;
        }
        
    }
    expression = str;
    return dataStack.pop();
}

h2result::token h2result::getOp(int &value)
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


#endif /* lattertoresult_h */
