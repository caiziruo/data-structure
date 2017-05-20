//
//  dual_circular_linked_list.hpp
//  list
//
//  Created by caiziruo on 24/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef dual_circular_linked_list_hpp
#define dual_circular_linked_list_hpp

#include <iostream>
using namespace std;

#include "list.hpp"

template <class T>
class dual_circular_linked_list:public list<T>
{
private:
    struct node{
        T data;
        node *prev, * next;
        
        node(const T &x, node * p = NULL, node * n = NULL)
        {
            data = x;
            prev = p;
            next = n;
        }
        node():next(NULL) {}
        ~node(){}
    };
    
    node * begin;
    int currentLength;
    
    node * move(int i) const;//return the address of the i-th node.
    
public:
    dual_circular_linked_list(const T &x);
    ~dual_circular_linked_list();
    
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
        void operator--() {current = current -> prev;}
        bool operator==(const iterator &q) const {return (current == q.current);}
        node * get_address() {return current;}
    };
    
    iterator get_begin() const;//initialize the iterator to the beginning node
    void erase_data(iterator &q);
    void update_data(iterator &q, const T &x);
    void insert_data(iterator &q, const T &x);
};

template <class T>
typename dual_circular_linked_list<T>::node * dual_circular_linked_list<T>::move(int i) const{
    node * p = begin;
    while (i--)
    {
        p = p -> next;
    }
    return p;
}

template <class T>
dual_circular_linked_list<T>::dual_circular_linked_list(const T &x) {
    begin = new node;
    begin -> data = x;
    begin -> next = begin;
    begin -> prev = begin;
    currentLength = 1;
}

template <class T>
dual_circular_linked_list<T>::~dual_circular_linked_list() {clear(); delete begin;}

template <class T>
void dual_circular_linked_list<T>::clear() {
    node * p = begin -> next, * q;
    begin -> next = begin;
    begin -> prev = begin;
    while (p != begin)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    currentLength = 1;
}

template <class T>
void dual_circular_linked_list<T>::insert(int i, const T &x)
{
    node * tmp;
    
    node * pos = move(i);
    tmp = new node(x, pos -> prev, pos);
    pos -> prev -> next = tmp;
    pos -> prev = tmp;
    if (i == 0) begin = tmp;
    ++currentLength;
}

template <class T>
void dual_circular_linked_list<T>::update(int i, const T &x)
{
    move(i) -> data = x;
}

template <class T>
void dual_circular_linked_list<T>::remove(int i)
{
    if (i == 0)
    {
        node * pos = begin -> prev;
        begin = begin -> next;
        delete pos -> next;
        pos -> next = begin;
        begin -> prev = pos;
        --currentLength;
        return;
    }
    node * pos = move(i - 1), * removepos = pos -> next;
    pos -> next = removepos -> next;
    delete removepos;
    pos -> next -> prev = pos;
    --currentLength;
}

template <class T>
int dual_circular_linked_list<T>::search(const T &x) const {
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
T dual_circular_linked_list<T>::visit(int i) const {
    return move(i) -> data;
}

template <class T>
void dual_circular_linked_list<T>::traverse() const {
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
typename dual_circular_linked_list<T>::iterator dual_circular_linked_list<T>::get_begin() const{
    return iterator(begin);
}

template <class T>
void dual_circular_linked_list<T>::erase_data(iterator &q) {
    if (q.get_address() == begin)
        begin = begin -> next;
    node * p = q.get_address() -> prev;
    p -> next = q.get_address() -> next;
    ++q;
    delete q.get_address() -> prev;
    q.get_address() -> prev = p;
    --currentLength;
}

template <class T>
void dual_circular_linked_list<T>::update_data(iterator &q, const T &x) {
    q.get_address() -> data = x;
}

template <class T>
void dual_circular_linked_list<T>::insert_data(iterator &q, const T &x) {
    node * tmp = new node(x, q.get_address() -> prev, q.get_address());
    q.get_address() -> prev -> next = tmp;
    q.get_address() -> prev = tmp;
    if (q.get_address() == begin)
        begin = tmp;
    ++currentLength;
    --q;
}

#endif /* dual_circular_linked_list_hpp */
