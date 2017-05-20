//
//  BernoulliQueue.hpp
//  priorityqueue
//
//  Created by caiziruo on 12/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef BernoulliQueue_hpp
#define BernoulliQueue_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class BernoulliQueue {
private:
    struct node {
        T data;
        int size;
        node * next;
        node * sons; // B0
        node(const T &x, int si = 0, node * n = NULL, node * s = NULL):data(x), size(si), next(n), sons(s) {}
        ~node() {}
    };
    
    node * root;
    
    void merge(node * t);
    void clear(node * t){
        if (t != NULL) {
            clear(t -> sons);
            clear(t -> next);
            delete t;
        }
    }
public:
    BernoulliQueue() {root = NULL;}
    ~BernoulliQueue() {clear(root);}
    
    void enQueue(const T &x);
    T deQueue();
    void merge(const BernoulliQueue &bernoulli);
    void levelTraverse() const;
};

template <class T>
void BernoulliQueue<T>::merge(const BernoulliQueue &bernoulli) {
    node * tmp, * tmpnext;
    tmp = bernoulli.root;
    while (tmp != NULL) {
        tmpnext = tmp -> next;
        tmp -> next = NULL;
        merge(tmp);
        tmp = tmpnext;
    }
    bernoulli.root = NULL;
}

template <class T>
void BernoulliQueue<T>::enQueue(const T &x) {
    node * tmp = new node(x);
    merge(tmp);
}

template <class T>
T BernoulliQueue<T>::deQueue() {
    if (root -> next == NULL) {
        T x = root -> data;
        node * tmp = root;
        root = root -> sons;
        delete tmp;
        return x;
    }

    node * min = root, * minpre = root, * tmp = root -> next;
    while (tmp != NULL) {
        if (min -> data > tmp -> data) min = tmp;
        tmp = tmp -> next;
    }
    if (min == root) {
        if (root -> size == 0) {
            T x = root -> data;
            tmp = root;
            root = root -> next;
            delete tmp;
            return x;
        }
        else {
            T x = root -> data;
            node * tmpson = root -> sons, * tmpsonnext = root;
            root = root -> next;
            delete tmpsonnext;
            while (tmpson != NULL) {
                tmpsonnext = tmpson -> next;
                tmpson -> next = NULL;
                merge(tmpson);
                tmpson = tmpsonnext;
            }
            return x;
        }
        
    }
    else {
        while (minpre -> next != min) {
            minpre = minpre -> next;
        }
        tmp = min -> sons;
        T x = min -> data;
        minpre -> next = min -> next;
        delete min;
        while (tmp != NULL) {
            min = tmp -> next;
            tmp -> next = NULL;
            merge(tmp);
            tmp = min;
        }
        return x;
    }
}

template <class T>
void BernoulliQueue<T>::merge(node * t) {
    if (root == NULL) {root = t; return;}

    else if (root -> next == NULL) {
        if (t -> size < root -> size) {t -> next = root; root = t; return;}
        else if (t -> size == root -> size) {
            if (t -> data < root -> data) {
                if (t -> size == 0) {
                    t -> sons = root;
                    root = t;
                    ++t -> size;
                    return;
                }
                else {
                    node * tmp = t -> sons;
                    while (tmp -> next != NULL) tmp = tmp -> next;
                    tmp -> next = root;
                    root = t;
                    ++t -> size;
                    return; 
                }
            }
            else {
                if (root -> size == 0) {
                    root -> sons = t;
                    ++root -> size;
                    return;
                }
                else {
                    node * tmp = root -> sons;
                    while (tmp -> next != NULL) tmp = tmp -> next;
                    tmp -> next = t;
                    ++root -> size;
                    return; 
                }
            }
        }
        else {root -> next = t; return;}
    }

    else {
        if (t -> size < root -> size) {t -> next = root; root = t; return;} //t < root
        else if (t -> size == root -> size) { // t == root
            t -> next = root -> next; 
            root -> next = t;
            while (root -> next != NULL && root -> size == root -> next -> size) {
                t = root -> next;
                if (root -> data <= t -> data) {
                    root -> next = t -> next; 
                    t -> next = NULL;
                    if (root -> size == 0) {root -> sons = t; root -> size++;}
                    else {
                        node * tmp = root -> sons;
                        while (tmp -> next != NULL) tmp = tmp -> next;
                        tmp -> next = t;
                        root -> size++;
                    }
                }
                else {   //root becomes one of the son of t 
                    root -> next = NULL;  
                    if (t -> size == 0) {t -> sons = root; t -> size++; root = t;}
                    else {
                        node * tmp = t -> sons;
                        while (tmp -> next != NULL) tmp = tmp -> next;
                        tmp -> next = root;
                        t -> size++;
                        root = t;
                    }
                }
            }
            return;
        }
        else { //t > root
            node * tmp = root, * tmpnext = root -> next;
            while (t -> size > tmpnext -> size) {
                tmp = tmp -> next;
                tmpnext = tmp -> next;
                if (tmpnext == NULL) {tmp -> next = t; return;}
            }
            if (t -> size < tmpnext -> size) {tmp -> next = t; t -> next = tmpnext;}
            else {
                t -> next = tmpnext;
                tmp -> next = t;
                while (tmpnext != NULL && t -> size == tmpnext -> size) {
                    if (t -> data <= tmpnext -> data) {
                        t -> next = tmpnext -> next;
                        tmpnext -> next = NULL;
                        node * tmpson = t -> sons;
                        while (tmpson -> next != NULL) tmpson = tmpson -> next;
                        tmpson -> next = tmpnext;
                        t -> size++;
                        tmpnext = t -> next;
                    }
                    else {
                        tmp -> next = tmpnext;
                        t -> next = NULL;
                        node * tmpson = tmpnext -> sons;
                        while (tmpson -> next != NULL) tmpson = tmpson -> next;
                        tmpson -> next = t;
                        tmpnext -> size++;
                        t = tmpnext;
                        tmpnext = tmpnext -> next;
                    }
                }
                return;
            }
        } 
    }
}

template <class T>
void BernoulliQueue<T>::levelTraverse() const {
    linkQueue<node *> que;
    que.enQueue(root);
    node * current;

    while (! que.isEmpty()) {
        current = que.deQueue();
        cout << current -> data << " ";
        if (current -> sons != NULL) que.enQueue(current -> sons);
        if (current -> next != NULL) que.enQueue(current -> next);
    }
}


#endif /* BernoulliQueue_hpp */
