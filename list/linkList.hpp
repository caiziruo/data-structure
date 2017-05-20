//
//  linkList.hpp
//  list
//
//  Created by caiziruo on 24/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef linkList_hpp
#define linkList_hpp

#include <stdio.h>

#include "list.hpp"

template <class T>
class linkList:public list<T>
{
private:
    struct node{
        T data;
        node * next;
        
        node(const T &x, node * n = NULL)
        {
            data = x;
            next = n;
        }
        node():next(NULL) {}
        ~node(){}
    };
    
    node * head;
    int currentLength;
    
    node * move(int i) const;//return the address of the i-th node.
    
public:
    linkList();
    ~linkList();
    
    void clear();
    int length() const {return currentLength;}
    void insert(int i, const T &x);
    void update(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    void invert();
};

#include <iostream>
using namespace std;

template <class T>
typename linkList<T>::node * linkList<T>::move(int i) const{
    if (i == -1)
        return head;
    node * p = head -> next;
    while (i--)
    {
        p = p -> next;
    }
    return p;
}

template <class T>
linkList<T>::linkList() {
    head = new node;
    head -> next = NULL;
    currentLength = 0;
}

template <class T>
linkList<T>::~linkList() {clear(); delete head;}

template <class T>
void linkList<T>::clear() {
    node * p = head -> next, * q;
    head -> next = NULL;
    while (p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    currentLength = 0;
}

template <class T>
void linkList<T>::insert(int i, const T &x)
{
    node * tmp, * pos = move(i - 1);
    tmp = new node(x, pos -> next);
    pos -> next = tmp;
    ++currentLength;
}

template <class T>
void linkList<T>::update(int i, const T &x)
{
    move(i) -> data = x;
}

template <class T>
void linkList<T>::remove(int i)
{
    node * pos = move(i - 1), * removepos = pos -> next;
    pos -> next = removepos -> next;
    delete removepos;
    --currentLength;
}

template <class T>
int linkList<T>::search(const T &x) const {
    int i = 0;
    node * pos = move(0);
    while (pos != NULL)
    {
        if (pos -> data != x)
        {
            pos = pos -> next;
            ++i;
        }
        else break;
    }
    if (pos == NULL)
        return -1;
    else return i;
}

template <class T>
T linkList<T>::visit(int i) const {
    return move(i) -> data;
}

template <class T>
void linkList<T>::traverse() const {
    node * pos = head -> next;
    while (pos != NULL)
    {
        cout << pos -> data << " ";
        pos = pos -> next;
    }
    cout << '\n';
}

template <class T>
void linkList<T>::invert() {
    int i;
    node * tmp = head -> next;
    node * p[currentLength];
    for (i = 0; i < currentLength; i++)
    {
        p[i] = tmp;
        tmp = tmp -> next;
    }
    for (i = currentLength - 1; i > 0; i--)
    {
        p[i] -> next = p[i - 1];
    }
    p[0] -> next = NULL;
    head -> next = p[currentLength - 1];
}

#endif /* linkList_hpp */
