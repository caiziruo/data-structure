//
//  duLinkList.hpp
//  list
//
//  Created by caiziruo on 23/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef duLinkList_hpp
#define duLinkList_hpp
#include <iostream>
using namespace std;
#include "list.hpp"

template <class T>
class duLinkList:public list <T>
{
private:
struct node{
        T data;
        node * prev, * next;
        
        node(const T &x, node * p = NULL, node * n = NULL)
        {
            data = x;
            next = n;
            prev = p;
        }
        node():next(NULL), prev(NULL){}
        ~node(){}
    };
    
    node * head, * tail;
    int currentLength;
    
    node * move(int i) const;//return the address of the i-th node.
public:
    duLinkList();
    ~duLinkList() {clear(); delete head; delete tail;}
    
    void clear();
    int length() const {return currentLength;}
    void insert(int i, const T &x);
    void update(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    
    duLinkList operator+(const duLinkList &q);
    duLinkList &operator=(const duLinkList &q);
};

template <class T>
typename duLinkList<T>::node * duLinkList<T>::move(int i) const
{
    node * p = head -> next;
    
    
    while (i--)
        p = p -> next;
    return p;
}

template <class T>
duLinkList<T>::duLinkList()
{
    head = new node;
    head -> next = tail = new node;
    tail -> prev = head;
    currentLength = 0;
}

template <class T>
void duLinkList<T>::clear()
{
    node * p = head -> next, * q;
    head -> next = tail;
    tail -> prev = head;
    while (p != tail)
    {
        q = p -> next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

template <class T>
void duLinkList<T>::insert(int i, const T &x)
{
    node * pos, *tmp;
    
    pos = move(i);
    tmp = new node(x, pos -> prev, pos);
    pos -> prev -> next = tmp;
    pos -> prev = tmp;
    
    ++currentLength;
}

template <class T>
void duLinkList<T>::update(int i, const T &x)
{
    move(i) -> data = x;
}

template <class T>
void duLinkList<T>::remove(int i)
{
    node * pos;
    
    pos = move(i);
    pos -> prev -> next = pos -> next;
    pos -> next -> prev = pos -> prev;
    
    delete pos;
    --currentLength;
}

template <class T>
int duLinkList<T>::search(const T &x) const
{
    node * p = head -> next;
    int i = 0;
    
    while (p != tail && p -> data != x)
    {
        p = p -> next;
        ++i;
    }
    if (p == tail)
        return -1;
    else return i;
}

template <class T>
T duLinkList<T>::visit(int i) const
{
    return move(i) -> data;
}

template <class T>
void duLinkList<T>::traverse() const
{
    node * p = head -> next;
    while (p != tail) {
        cout << p -> data << " ";
        p = p -> next;
    }
    cout << '\n';
}

template <class T>
duLinkList<T> duLinkList<T>::operator+(const duLinkList<T> &q) {
    duLinkList<T> p;
    for (int i = 0; i < currentLength; i++){
        p.insert(i, (*this).visit(i));
    }
    for (int i = 0; i < q.length(); i++){
        p.insert(i + currentLength, q.visit(i));
    }
    return p;
}

template <class T>
duLinkList<T> &duLinkList<T>::operator=(const duLinkList<T> &q) {
    if (this == &q) return *this;
    
    for (int i = 0; i < q.length(); i++)
    {
        (*this).insert(i, q.visit(i));
    }
    return *this;
}

#endif /* duLinkList_hpp */
