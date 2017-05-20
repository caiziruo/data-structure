//
//  linkQueue.h
//  queue
//
//  Created by caiziruo on 06/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef linkQueue_h
#define linkQueue_h

#include "queue.h"
#include <iostream>
using namespace std;

template <class T>
class linkQueue:public queue<T> {
private:
    struct node {
        T data;
        node * next;
        node(const T &x, node * N = NULL){
            data = x;
            next = N;
        }
        node(): next(NULL) {}
        ~node(){}
    };
    
    node * front, * rear;
    
public:
    linkQueue() {front = rear = NULL;}
    
    ~linkQueue();
    
    bool isEmpty() {return front == NULL;}
    
    void enQueue(const T &x);
    
    T deQueue();
    
    T getHead() {return front->data;}
    
};

template <class T>
linkQueue<T>::~linkQueue() {
    node * tmp = front;
    while (tmp != NULL){
        front = front -> next;
        delete tmp;
        tmp = front;
    }
}

template <class T>
void linkQueue<T>::enQueue(const T &x) {
    if (rear == NULL)
        front = rear = new node(x);
    else{
        rear -> next = new node(x);
        rear = rear -> next;
    }
}

template <class T>
T linkQueue<T>::deQueue() {
    node * tmp = front;
    T value = front -> data;
    front = front -> next;
    if (front == NULL)
        rear = NULL;
    delete tmp;
    return value;
}


#endif /* linkQueue_h */
