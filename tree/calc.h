//
//  calc.h
//  tree
//
//  Created by caiziruo on 08/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef calc_h
#define calc_h

#include <iostream>
using namespace std;
#include <cmath>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"



class calc
{
public:
    enum Type {DATA, ADD, SUB, MULTI, DIV, EXP, OPAREN, CPAREN, EOL};
    
    struct node
    {
        Type type;
        int data;
        node * lchild, * rchild;
        
        node (Type t, int d = 0, node * lc = NULL, node * rc = NULL)
        {
            type = t;
            data = d;
            lchild = lc;
            rchild = rc;
        }
    };
    
    node * root;
    
    node * create(const char * &s);
    
    Type getToken(const char * &s, int &value);

    int result(node * t);

    int size(node * t) const
    {
        if (t == NULL) return 0;
        return 1 + size(t -> lchild) + size(t -> rchild);
    }
    
    char type2char(const Type t) const {
        switch(t) {
            case ADD: return '+';
            case SUB: return '-';
            case MULTI: return '*';
            case DIV: return '/';
            default: return '\0';
        }
    }

    Type char2type(const char t) const {
        switch(t) {
            case '+': return ADD;
            case '-': return SUB;
            case '*': return MULTI;
            case '/': return DIV;
            default: return DATA;
        }
    }
    
    void midOrder(node * t) const {
        if (t != NULL && t -> type != DATA) {
            if (t -> type > SUB && (t -> lchild -> type == ADD || t -> lchild -> type == SUB)) {
                cout << "(";
                midOrder(t -> lchild);
                cout << ")";
            }
            else midOrder(t -> lchild);
            cout << type2char(t -> type);
            midOrder(t -> rchild);
            if (t -> type > SUB && (t -> rchild -> type == ADD || t -> rchild -> type == SUB)) {
                cout << "(";
                midOrder(t -> rchild);
                cout << ")";
            }
        }
        else if (t != NULL) {
            cout << t -> data;
        }
    }

public:
    calc() {root = NULL;}
    calc(const char * s) {root = create(s);}
    int result() {
        if (root == NULL) return 0;
        return result(root);
    }
    void preOrder() const;
    int size() const {return size(root);}

    void createTree();
    void midOrder() const {
        if (root != NULL)
            midOrder(root);
    }
};






void calc::createTree() {
    linkQueue<node *> que;
    node * tmpnode = NULL;
    char tmpchar = '\0';
    int tmpint = 0;

    cout << "\ninput the type of root node:(0 means number, 1 means operator)";
    cin >> tmpint;
    cout << "\ninput the root node:";

    if (tmpint == 0) {
        cin >> tmpint;
        root = new node(DATA, tmpint);
        return;
    }
    else {
        cin >> tmpchar;
        root = new node(char2type(tmpchar), 0);
    }
    que.enQueue(root);

    while (! que.isEmpty())
    {
        tmpnode = que.deQueue();
        cout << "\ninput the two sons of " << type2char(tmpnode -> type) << ":";
        cout << "\ninput the type of the left son:";
        cin >> tmpint;
        cout << "\ninput the left son:";
        if (tmpint == 0) {
            cin >> tmpint;
            tmpnode -> lchild = new node(DATA, tmpint);
        }
        else {
            cin >> tmpchar;
            que.enQueue(tmpnode -> lchild = new node(char2type(tmpchar), 0));
        }

        cout << "\ninput the type of the right son:";
        cin >> tmpint;
        cout << "\ninput the right son:";
        if (tmpint == 0) {
            cin >> tmpint;
            tmpnode -> rchild = new node(DATA, tmpint);
        }
        else {
            cin >> tmpchar;
            que.enQueue(tmpnode -> rchild = new node(char2type(tmpchar), 0));
        }
    }
    
    cout << "create completed!\n";
}


calc::node * calc::create(const char * &s)
{
    calc::node * p = NULL, * root = NULL;
    
    Type returnType;
    int value;
    
    while (*s) {
        returnType = calc::getToken(s, value);
        switch (returnType) {
            case DATA: case OPAREN:
                if (returnType == DATA)
                    p = new calc::node(DATA, value);
                else p = create(s);
                if (root != NULL)
                {
                    node * tmp = root;
                    while (tmp -> rchild != NULL) {
                        tmp = tmp -> rchild;
                    }
                    tmp -> rchild = p;
                }
                break;
            case CPAREN: case EOL: return root;
            case ADD: case SUB:
                if (root == NULL)
                    root = new node(returnType, 0, p);
                else root = new node(returnType, 0, root);
                break;
            case MULTI: case DIV:
                if (root == NULL)
                    root = new node(returnType, 0, p);
                else if (root -> type == MULTI || root -> type == DIV || root -> type == EXP)
                    root = new node(returnType, 0, root);
                else root -> rchild = new node(returnType, 0, root -> rchild);
                break;
            case EXP: 
                if (root == NULL)
                    root = new node(returnType, 0, p);
                else {
                    node * tmp = root;
                    while (tmp -> rchild -> rchild != NULL) {
                        tmp = tmp -> rchild;
                    }
                    tmp -> rchild = new node(returnType, 0, tmp -> rchild);
                }
                break;
        }
    }
    return root;
}

calc::Type calc::getToken(const char * &s, int &data)
{
    char type;
    
    while (*s == ' ') ++s;
    
    if (*s >= '0' && *s <= '9') {
        data = 0;
        while (*s >= '0' && *s <= '9') {
            data = data * 10 + *s - '0';
            ++s;
        }
        return DATA;
    }

    if (*s == '\0') return EOL;
    
    type = *s;
    ++s;
    switch(type) {
        case '+':return ADD;
        case '-':return SUB;
        case '*':return MULTI;
        case '/':return DIV;
        case '(':return OPAREN;
        case ')':return CPAREN;
        case '^':return EXP;
        default:return EOL;
    }
}

int calc::result(node * t) {
    int num1, num2;
    if (t -> type == DATA) return t -> data;
    num1 = result(t -> lchild);
    num2 = result(t -> rchild);
    switch(t -> type){
        case ADD: t -> data = num1 + num2; break;
        case SUB: t -> data = num1 - num2; break;
        case MULTI: t -> data = num1 * num2; break;
        case DIV: t -> data = num1 / num2; break;
        case EXP: t -> data = pow(num1, num2); break;
        default: break;
    }
    return t -> data;
}

void calc::preOrder() const {
    link_stack<node *> s;
    node * current = NULL;
    
    cout << "pre order traverse:";
    s.push(root);
    while (! s.isEmpty()) {
        current = s.pop();
        if (current -> type == DATA) cout << current -> data << " ";
        if (current -> type == ADD) cout << "+ ";
        if (current -> type == SUB) cout << "- ";
        if (current -> type == MULTI) cout << "* ";
        if (current -> type == DIV) cout << "/ ";
        if (current -> rchild != NULL) s.push(current -> lchild);
        if (current -> lchild != NULL) s.push(current -> rchild);
    }
}

#endif /* calc_h */
