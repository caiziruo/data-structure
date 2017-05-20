//
//  closeHashTable.hpp
//  hashTable
//
//  Created by caiziruo on 25/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef closeHashTable_hpp
#define closeHashTable_hpp

#include <iostream>
#include "hashTable.hpp"

template <class T>
class closeHashTable:public hashTable<T> {
private:
    struct node {
        T data;
        int state;      //0 - empty, 1 - active, 2 - deleted
        
        node() {state = 0;}
    };
    
    node * array;
    int size, activeNumber, deletedNumber;
    void biggersize();
    int maximumDeletedNumber;
    
public:
    closeHashTable(int length = 97, int maxdelete = 10, int (* f) (const T &x) = hashTable<T>::defaultKey);
    ~closeHashTable() {delete [] array;}
    bool find(const T &x) const;
    bool insert(const T &x);
    bool remove(const T &x);
    
    
    void rehash();
    void traverse() const;
};

template <class T>
closeHashTable<T>::closeHashTable(int length, int maxdelete, int (* f) (const T &x)) {
    size = 0;
    for (int i = length; ; i++) {
        int j;
        for (j = 2; j < i/2 + 1; j++) {
            if (i % j == 0) break;
        }
        if (j == i/2 + 1) {size = i; break;}
    }

    array = new node[size];
    hashTable<T>::key = f;
    activeNumber = 0;
    deletedNumber = 0;
    maximumDeletedNumber = maxdelete;
}

template <class T>
void closeHashTable<T>::biggersize() {
    int biggertmpsize = 0;
    for (int i = 2 * size; ; i++) {
        int j;
        for (j = 2; j < i/2 + 1; j++) {
            if (i % j == 0) break;
        }
        if (j == i/2 + 1) {biggertmpsize = i; break;}
    }

    node * tmp = array;
    array = new node[biggertmpsize];
    for (int i = 0; i < size; ++i) {
        array[i].data = tmp[i].data;
        array[i].state = tmp[i].state;
    }
    size = biggertmpsize;
    delete [] tmp;
    rehash();
}

template <class T>
bool closeHashTable<T>::insert(const T &x) {
    if (activeNumber >= size / 2) biggersize();
    if (deletedNumber >= maximumDeletedNumber) rehash();

    int initPos, pos;

    initPos = pos = hashTable<T>::key(x) % size;
    do {
        if (array[pos].state != 1) {
            array[pos].data = x;
            array[pos].state = 1;
            activeNumber++;
            return true;
        }
        if (array[pos].state == 1 && array[pos].data == x) {activeNumber++; return true;}
        pos = (pos + 1) % size;
    } while (pos != initPos);

    return false;
}

//                pos = (pos + 2 * i - 1) % size;
//template <class T>
//bool closeHashTable<T>::insert(const T &x) {
//    int pos;
//
//    pos = hashTable<T>::key(x) % size;
//    int i = 1;
//    while (i < size) {
//        if (array[pos].state != 1) {
//            array[pos].data = x;
//            array[pos].state = 1;
//            return true;
//        }
//        if (array[pos].state == 1 && array[pos].data == x) return true;
//        pos = (pos + 2 * i - 1) % size;
//        i++;
//    }
//    return false;
//}

template <class T>
bool closeHashTable<T>::remove(const T &x) {
    int initPos, pos;

    initPos = pos = hashTable<T>::key(x) % size;
    do {
        if (array[pos].state == 0) return false;
        if (array[pos].state == 1 && array[pos].data == x) {
            array[pos].state = 2; 
            deletedNumber++;
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);

    return false;
}

template <class T>
bool closeHashTable<T>::find(const T &x) const {
    int initPos, pos;

    initPos = pos = hashTable<T>::key(x) % size;
    do {
        if (array[pos].state == 0) return false;
        if (array[pos].state == 1 && array[pos].data == x) return true;
        pos = (pos + 1) % size;
    } while (pos != initPos);

    return false;
}

template <class T>
void closeHashTable<T>::rehash() {
    node * tmp = array;

    array = new node[size];
    for (int i = 0; i < size; ++i) {if (tmp[i].state == 1) insert(tmp[i].data);}
        delete [] tmp;
}

template <class T>
void closeHashTable<T>::traverse() const {
    for (int i = 0; i < size; ++i) {
        if (array[i].state == 1) std::cout << array[i].data << " ";
    }
}



#endif /* closeHashTable_hpp */
