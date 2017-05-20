//
//  calc.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef calc_h
#define calc_h

#include <iostream>
using namespace std;
#include "seq_stack.h"
#include <cmath>

class calc {
    char * expression;
    
    enum token {OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL};
    
    void BinaryOp(token op, seq_stack<int> &dataStack);
    
    token getOp(int &value);
    //return &value = 123456789 or token ()+-*/
    
public:
    calc(const char * s)
    {
        expression = new char[strlen(s) + 1];
        strcpy(expression, s);
    }
    ~calc() {delete expression;}
    
    int result();
};


int calc::result()
{
    token lastOp, topOp = EOL;
    int result_value, CurrentValue;
    seq_stack<token> opStack;
    seq_stack<int> dataStack;
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
                dataStack.push(CurrentValue);
                break;
            case CPAREN:
                while (! opStack.isEmpty() && (topOp = opStack.pop()) != OPAREN )
                    BinaryOp(topOp, dataStack);
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
                    BinaryOp(opStack.pop(), dataStack);
                opStack.push(lastOp);
                break;
            case ADD: case SUB:
                while (! opStack.isEmpty() && opStack.top() != OPAREN)
                    BinaryOp(opStack.pop(), dataStack);
                opStack.push(lastOp);
        }
    }
    
    while (! opStack.isEmpty())
    {
        BinaryOp(opStack.pop(), dataStack);
    }
    if (dataStack.isEmpty())
    {
        cout << "no result\n";
        return 0;
    }
    result_value = dataStack.pop();
    if (! dataStack.isEmpty())
    {
        cout << "lack of opera";
        return 0;
    }
    
    expression = str;
    return result_value;
}

void calc::BinaryOp(token op, seq_stack<int> &dataStack)
{
    int num1, num2;
    
    if (dataStack.isEmpty())
    {
        cerr << "lack of number.";
        exit(1);
    }
    else num2 = dataStack.pop();
    
    if (dataStack.isEmpty())
    {
        cerr << "lack of number.";
        exit(1);
    }
    else num1 = dataStack.pop();
    
    switch (op) {
        case OPAREN:
            break;
        case CPAREN:
            break;
        case VALUE:
            break;
        case EOL:
            break;
        case ADD:
            dataStack.push(num1 + num2);
            break;
        case SUB:
            dataStack.push(num1 - num2);
            break;
        case MULTI:
            dataStack.push(num1 * num2);
            break;
        case DIV:
            dataStack.push(num1 / num2);
            break;
        case EXP:
            dataStack.push(pow(num1, num2));
    }
}

calc::token calc::getOp(int &value)
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

#endif /* calc_h */
