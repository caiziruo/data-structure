//
//  balance.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef balance_h
#define balance_h

#include <iostream>
#include <fstream>
#include "seq_stack.h"

using namespace std;

class balance {
private:
    ifstream fin;   //files to be checked
    int currentLine;
    int Errors;
    
    struct Symbol {char Token; int TheLine;};
    
    enum CommentType {SlashSlash, SlashStar}; //  or  /* */
    bool CheckMatch(char Symb1, char Symb2, int Line1, int Line2);
    char GetNextSymbol();
    void PutBackChar(char ch);
    void SkipComment(enum CommentType type);
    void SkipQuote(char type);
    char NextChar();
    
public:
    balance(const char * s);
    int CheckBalance();
};

class nobalanceFile {};

balance::balance(const char * s)
{
    fin.open(s);
    if (! fin)
        throw nobalanceFile();
    
    currentLine = 1;
    Errors = 0;
}

int balance::CheckBalance()
{
    struct Symbol node;
    seq_stack<Symbol> st;
    char LastChar, Match;
    
    while (( LastChar = GetNextSymbol() ))
    {
        switch (LastChar)
        {
            case '(': case '[': case '{':
                node.Token = LastChar;
                node.TheLine = currentLine;
                st.push(node);
                break;
                
            case ')': case ']': case '}':
                if (st.isEmpty())
                {
                    Errors ++;
                    cout << "the " << currentLine << "-th line has a unnecessary" << LastChar << endl;
                }
                else {
                    node = st.pop();
                    Match = node.Token;
                    if (! CheckMatch(Match, LastChar, node.TheLine, currentLine))
                        ++Errors;
                }
                break;
        }
    }
    
    while ( ! st.isEmpty() )
    {
        Errors++;
        node = st.pop();
        cout << "symbol in the" << node.TheLine << "-th line" << node.Token << "does not match\n";
    }
    return Errors;
}

bool balance::CheckMatch(char Symb1, char Symb2, int Line1, int Line2)
{
    if (
        (Symb1 == '(' && Symb2 != ')') || (Symb1 == '[' && Symb2 != ']') || (Symb1 == '{' && Symb2 != '}')
        )
    {
        cout << "The symbol " << Symb2 << " in the " << Line2 << "-th line "  << "does not match the symbol " << Symb1 <<  " in the " << Line1 << "-th line." << "\n";
        return false;
    }
    else return true;
}

char balance::GetNextSymbol()
{
    char ch;
    while ( (ch = NextChar()) )
    {
        if ( ch == '/')
        {
            ch = NextChar();
            if (ch == '*')
                SkipComment(SlashStar);
            else if ( ch == '/' )
                SkipComment(SlashSlash);
            else PutBackChar(ch);
        }
        else if (ch == '\'' || ch == '"')
            SkipQuote(ch);
        else if (ch == '{' || ch == '[' || ch == '(' || ch == ')' || ch == ']' || ch == '}')
            return ch;
    }
    return NULL;
}

char balance::NextChar()
{
    char ch;
    if ( (ch = fin.get()) == EOF )
        return NULL;
    
    if (ch == '\n')
        currentLine++;
    return ch;
}

void balance::PutBackChar(char ch)
{
    fin.putback(ch);
    if (ch == '\n')
        currentLine--;
}

void balance::SkipQuote(char type)
{
    char ch;
    while ((ch = NextChar() ))
    {
        if (ch == type)
            return;
        else if (ch == '\n')
        {
            Errors++;
            cout << "missing closing quote at line " << currentLine << endl;
            return;
        }
        else if (ch == '\\')
            ch = NextChar();
    }
}

void balance::SkipComment(enum CommentType type)
{
    char ch, flag;
    
    if (type == SlashSlash)
    {
        while ( (ch = NextChar()) && (ch != '\n') );
        return;
    }
    flag = ' ';
    while ( ( ch = NextChar()) != char(NULL))
    {
        if (flag == '*' && ch == '/') return;
        flag = ch;
    }
    Errors++;
    cout << "Comment is unterminated!" << endl;
}

#endif /* balance_h */
