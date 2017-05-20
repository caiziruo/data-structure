//
//  circularLinkQueue.hpp
//  queue
//
//  Created by caiziruo on 06/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef circularLinkQueue_hpp
#define circularLinkQueue_hpp

#include "queue.h"
#include <iostream>
using namespace std;

template <class T>
class circularLinkQueue:public queue<T> {
private:
    struct node {
        T data;
        node * next;
        node(const T &x, node * N = NULL){
            data = x;
            next = N;
        }
        node(): next(NULL) {}
        ~node() {}
        
    };
    int queueLength;
    node * front, * rear;
    
public:
    circularLinkQueue();
    
    ~circularLinkQueue();
    
    bool isEmpty() {return queueLength == 0;}
    
    void enQueue(const T &x);
    
    T deQueue();
    
    int getLength() {return queueLength;}
    
    T getHead();
    
};

template <class T>
circularLinkQueue<T>::circularLinkQueue() {
    rear = front = NULL;
    queueLength = 0;
}

template <class T>
circularLinkQueue<T>::~circularLinkQueue() {
    if (front == NULL) return;
    front = rear -> next;
    if (front == rear){
        delete front;
        return;
    }
    rear -> next = NULL;
    node * tmp = front;
    while (front != NULL) {
        front = front -> next;
        delete tmp;
        tmp = front;
    }
}

template <class T>
void circularLinkQueue<T>::enQueue(const T &x) {
    if (rear == NULL){
        node * tmp = new node(x);
        tmp -> next = tmp;
        rear = front = tmp;
    }
    else {
        if (queueLength == 0) {
            front -> data = x;
        }
        else if (rear -> next == front){
            node * tmp = new node(x, front);
            rear -> next = tmp;
            rear = tmp;
        }
        else {
            rear = rear -> next;
            rear -> data = x;
        }
    }
    queueLength += 1;
}

template <class T>
T circularLinkQueue<T>::deQueue() {
    if (queueLength == 1) {
        queueLength = 0;
        return front -> data;
    }
    node * tmp = front;
    front = front -> next;
    queueLength -= 1;
    return tmp -> data;
}

template <class T>
T circularLinkQueue<T>::getHead() {
    return front -> data;
}



#endif /* circularLinkQueue_hpp */
