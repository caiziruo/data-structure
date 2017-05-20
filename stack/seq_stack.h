//
//  seq_stack.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef seq_stack_h
#define seq_stack_h

#include <iostream>
using namespace std;
#include "stack.h"

template <class T>
class seq_stack:public stack<T> {
private:
    T * data;
    int top_p;
    int maxSize;
    void doubleSpace();
    
public:
    seq_stack(int initSize = 10){
        data = new T[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    ~seq_stack() {delete [] data;}
    
    bool isEmpty() const {return top_p == -1;}
    
    void push(const T &x){
        if (top_p == maxSize - 1)
            doubleSpace();
        data[++top_p] = x;
    }
    
    T pop() {return data[top_p--];}
    T top() const {return data[top_p];}
};

template <class T>
void seq_stack<T>::doubleSpace() {
    T * tmp = data;
    
    data = new T[2 * maxSize];
    
    for (int i = 0; i < maxSize; ++i)
        data[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
}

#endif /* seq_stack_h */
