//
//  check_pascal.h
//  stack
//
//  Created by caiziruo on 05/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef check_pascal_h
#define check_pascal_h

#include <iostream>
#include <fstream>
#include "seq_stack.h"
using namespace std;

class check_pascal {
private:
    ifstream fin;   //files to be checked
    int currentLine;
    int Errors;
    
    enum wordtype {BEGIN, END, IF, THEN, ELSE, OTHERS, ENDOFFILE};
    
    struct Word {wordtype word; int TheLine;};
    
    //enum CommentType {SlashSlash, SlashStar}; //  or  /* */
    bool CheckMatch(seq_stack<Word>);
    //char GetNextSymbol();
    wordtype NextWord();
    void wordtype2word(wordtype);
    //void PutBackChar(char ch);
    //void SkipComment(enum CommentType type);
    //void SkipQuote(char type);
public:
    check_pascal(const char * s);
    
    int CheckBalance();
};

class nopascalFile {};

check_pascal::check_pascal(const char * s)
{
    fin.open(s);
    if (! fin)
        throw nopascalFile();
    
    currentLine = 1;
    Errors = 0;
}

void check_pascal::wordtype2word(wordtype a)
{
    switch (a)
    {
        case OTHERS:
        break;
        case ENDOFFILE:
        break;
        case BEGIN:
        cout << "begin";
        break;

        case END:
        cout << "end";
        break;

        case IF:
        cout << "if";
        break;

        case THEN: 
        cout << "then";
        break;

        case ELSE:
        cout << "else";
        break;
    }
    return;
}

int check_pascal::CheckBalance()
{
    struct Word node;
    seq_stack<Word> st;
    wordtype CurrentWord, Match, LastWord = OTHERS;
    
    while ( (CurrentWord = NextWord()) >= 0 )
    {
        switch (CurrentWord)
        {
            case OTHERS:
                break;
                
            case ENDOFFILE:
                if (st.isEmpty())
                {
                    return Errors;
                }
                while ( ! st.isEmpty() )
                {
                    Errors++;
                    node = st.pop();
                    cout << "The \"";
                    wordtype2word(node.word);
                    cout <<  "\" in the " << node.TheLine << "-th line" << "does not match\n";
                }
                return Errors;
                
            case BEGIN: 
                node.word = CurrentWord;
                node.TheLine = currentLine;
                st.push(node);
                LastWord = BEGIN;
                break;
                
            case END:
                if (st.isEmpty())
                {
                    Errors ++;
                    cout << "The " << currentLine << "-th line has a unnecessary \"end\"" << endl;
                }
                else
                {
                    node = st.pop();
                    Match = node.word;
                    if (Match != BEGIN)
                    {
                        ++Errors;
                        cout << "The \"end\" in the " << currentLine << "-th line does not match to the \"";
                        wordtype2word(Match);
                        cout << "\" in the " << node.TheLine << "-th line." << endl;
                    }
                }
                LastWord = END;
                break;

            case IF: 
                node.word = CurrentWord;
                node.TheLine = currentLine;
                st.push(node);
                LastWord = IF;
                break;

            case THEN:
                if (st.isEmpty())
                {
                    Errors++;
                    cout << "The " << currentLine << "-th line has a unnecessary \"then\"" << endl;
                }
                else
                {
                    node = st.pop();
                    Match = node.word;
                    if (Match != IF)
                    {
                        ++Errors;
                        cout << "The \"then\" in the " << currentLine << "-th line does not match to the \"";
                        wordtype2word(Match);
                        cout << "\" in the " << node.TheLine << "-th line." << endl;
                    }
                }
                LastWord = THEN;
                break;

            case ELSE:
                if (st.isEmpty() && LastWord != THEN)
                {
                    Errors++;
                    cout << "The " << currentLine << "-th line has a unnecessary \"else\"" << endl;
                }
                else
                {
                    if (LastWord != THEN)
                    {
                        ++Errors;
                        cout << "The \"else\" in the " << currentLine << "-th line does not match" << endl;
                    }
                }
                break;
        }
    }
    return Errors;
}


check_pascal::wordtype check_pascal::NextWord()
{
    char ch;

    if ( (ch = fin.get()) == EOF )
        return ENDOFFILE;
    
    while ( ch == '\n' || ch == ' ' )
    {
        if (ch == '\n')
            ++currentLine;
        ch = fin.get();
    }
    
    if (ch == EOF)
        return ENDOFFILE;
    
    switch(ch)
    {
        case 'b':
            if (
                (ch = fin.get()) == 'e' && (ch = fin.get()) == 'g' && (ch = fin.get()) == 'i' && (ch = fin.get()) == 'n' && ((ch = fin.get()) == ' ' || ch == '\n' || ch == EOF)
                )
            {
                fin.putback(ch);
                return BEGIN;
            }
            break;
        case 'e':
            if (
                (ch = fin.get()) == 'n'
                )
            {
                if (
                    (ch = fin.get()) == 'd' && ( (ch = fin.get()) == ' ' || ch == '\n' || ch == EOF)
                    )
                {
                    fin.putback(ch);
                    return END;
                }
            }
            else if (
                     ch == 'l' && (ch = fin.get()) == 's' && (ch = fin.get()) == 'e' && ((ch = fin.get()) == ' ' || ch == '\n' || ch == EOF)
                     )
            {
                fin.putback(ch);
                return ELSE;
            }
            break;
        case 'i':
            if (
                (ch = fin.get()) == 'f' && ( (ch = fin.get()) == '\n' || ch == ' ' || ch == EOF)
                )
            {
                fin.putback(ch);
                return IF;
            }
            break;
        case 't':
            if (
                (ch = fin.get()) == 'h' && (ch = fin.get()) == 'e' && (ch = fin.get()) == 'n' && ((ch = fin.get()) == ' ' || ch == '\n' || ch == EOF)
                )
            {
                fin.putback(ch);
                return THEN;
            }
            break;
    }
    
    if (ch == ' ' || ch == '\n' || ch == EOF)
        fin.putback(ch);
    return OTHERS;
}


#endif /* check_pascal_h */
