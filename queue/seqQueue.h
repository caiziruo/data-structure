//
//  seqQueue.cpp
//  queue
//
//  Created by caiziruo on 05/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef seqQueue_h
#define seqQueue_h

#include "queue.h"
#include <iostream>
using namespace std;

template <class T>
class seqQueue:public queue<T> {
private:
    T * elem;
    int maxSize;
    int front, rear;
    
    void doubleSpace();
    
public:
    seqQueue(int size = 10){
        elem = new T[size];
        maxSize = size;
        front = rear = 0;
    }
    
    ~seqQueue() {delete [] elem;}
    
    bool isEmpty() {return front == rear;}
    
    void enQueue(const T &x);
    
    T deQueue();
    
    T getHead() {return elem[(front + 1) % maxSize];}
};



template <class T>
void seqQueue<T>::doubleSpace() {
    T * tmp = elem;
    
    elem = new T[2 * maxSize];
    
    for (int i = 1; i < maxSize; ++i)
        elem[i] = tmp[(front + i) % maxSize];
    
    front = 0;
    rear = maxSize - 1;
    maxSize *= 2;
    
    delete tmp;
}


<#return type#> <#function name#>(<#function parameters#>) {
    <#statements#>
}
template <class T>
void seqQueue<T>::enQueue(const T &x) {
    if ((rear + 1) % maxSize == front)
        doubleSpace();
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <class T>
T seqQueue<T>::deQueue() {
    front = (front + 1) % maxSize;
    return elem[front];
}


#endif
