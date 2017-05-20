//
//  circular_linked_list.hpp
//  list
//
//  Created by caiziruo on 24/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef circular_linked_list_hpp
#define circular_linked_list_hpp

#include <iostream>
using namespace std;
#include "list.hpp"

template <class T>
class circular_linked_list:public list<T>
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
    
    node * begin;
    int currentLength;
    
    node * move(int i) const;//return the address of the i-th node.
    
public:
    circular_linked_list(const T &x);
    ~circular_linked_list();
    
    void clear();
    int length() const {return currentLength;}
    void insert(int i, const T &x);
    void update(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    
    
    class iterator{
    private:
        node * current;
    public:
        iterator(node *p) {current = p;}
        
        const T &operator*() const {return current -> data;}
        void operator++() {current = current -> next;}
        iterator &operator=(const iterator &q);
        bool operator==(const iterator &q) const {return (current == q.current);}
    };
    
    iterator get_begin() const;//initialize the iterator to the beginning node
};

template <class T>
typename circular_linked_list<T>::node * circular_linked_list<T>::move(int i) const{
    node * p = begin;
    while (i--)
    {
        p = p -> next;
    }
    return p;
}

template <class T>
circular_linked_list<T>::circular_linked_list(const T &x) {
    begin = new node;
    begin -> data = x;
    begin -> next = begin;
    currentLength = 1;
}

template <class T>
circular_linked_list<T>::~circular_linked_list() {clear(); delete begin;}

template <class T>
void circular_linked_list<T>::clear() {
    node * p = begin -> next, * q;
    begin -> next = begin;
    while (p != begin)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    currentLength = 1;
}

template <class T>
void circular_linked_list<T>::insert(int i, const T &x)
{
    node * tmp;
    if (i == 0)
    {
        tmp = new node(x, begin);
        move(currentLength-1) -> next = tmp;
        begin = tmp;
        ++currentLength;
        return;
    }
    node * pos = move(i - 1);
    tmp = new node(x, pos -> next);
    pos -> next = tmp;
    ++currentLength;
}

template <class T>
void circular_linked_list<T>::update(int i, const T &x)
{
    move(i) -> data = x;
}

template <class T>
void circular_linked_list<T>::remove(int i)
{
    if (i == 0)
    {
        node * pos = move(currentLength-1);
        begin = begin -> next;
        delete pos -> next;
        pos -> next = begin;
        --currentLength;
        return;
    }
    node * pos = move(i - 1), * removepos = pos -> next;
    pos -> next = removepos -> next;
    delete removepos;
    --currentLength;
}

template <class T>
int circular_linked_list<T>::search(const T &x) const {
    int i = 0;
    node * pos = move(0);
    while (i < currentLength)
    {
        if (pos -> data != x)
        {
            pos = pos -> next;
            ++i;
        }
        else break;
    }
    if (i == currentLength)
        return -1;
    else return i;
}

template <class T>
T circular_linked_list<T>::visit(int i) const {
    return move(i) -> data;
}

template <class T>
void circular_linked_list<T>::traverse() const {
    node * pos = begin;
    int i = 0;
    while (i < currentLength)
    {
        cout << pos -> data << " ";
        pos = pos -> next;
        ++i;
    }
    cout << '\n';
}

template <class T>
typename circular_linked_list<T>::iterator circular_linked_list<T>::get_begin() const{
    return iterator(begin);
}

template <class T>
typename circular_linked_list<T>::iterator &circular_linked_list<T>::iterator::operator=(const iterator &q)
{
    if (this == &q) return *this;
    
    current = q.current;
    return *this;
}


#endif /* circular_linked_list_hpp */
