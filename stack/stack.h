//
//  stack.h
//  stack
//
//  Created by caiziruo on 02/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef stack_h
#define stack_h


#include <iostream>
using namespace std;

template <class T>
class stack {
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const T &x) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual ~stack() {}
};

#endif /* stack_h */
