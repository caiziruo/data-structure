//
//  queue.h
//  queue
//
//  Created by caiziruo on 05/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <iostream>
using namespace std;

template <class T>
class queue {
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(const T &x) = 0;
    virtual T deQueue() = 0;
    virtual T getHead() = 0;
    virtual ~queue() {}
};

#endif /* queue_h */
