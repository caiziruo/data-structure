//
//  link_stack.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef link_stack_h
#define link_stack_h

#include <iostream>
using namespace std;
#include "stack.h"

template <class T>
class link_stack:public stack<T> {
private:
    struct node {
        T data;
        node * next;
        node(const T &x, node * N = NULL) {data = x; next = N; }
        node():next(NULL) {}
        ~node() {}
    };
    node * begin;
    
public:
    link_stack() {begin = NULL;}
    ~link_stack();
    
    bool isEmpty() const {return begin == NULL;}
    void push(const T &x) {node * tmp = new node(x, begin); begin = tmp; }
    
    T pop() {
        node * tmp = begin;
        T x = tmp -> data;
        begin = begin -> next;
        delete tmp;
        return x;
    }
    
    T top() const {return begin -> data; }
};

template <class T>
link_stack<T>::~link_stack() {
    node * tmp;
    while (begin != NULL) {
        tmp = begin;
        begin = begin -> next;
        delete tmp;
    }
}

#endif /* link_stack_h */
