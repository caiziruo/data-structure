//
//  seqList.hpp
//  list
//
//  Created by caiziruo on 23/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef seqList_hpp
#define seqList_hpp

#include <iostream>
using namespace std;

#include "list.hpp"

class OutOfBound{};
class IllegalSize{};

template <class elemType>
class seqList:public list <elemType>
{
    private:
    elemType * data;
    int currentLength;
    int maxSize;
    
    void doubleSpace();
    
public:
    seqList(int initSize = 10);
    ~seqList() {delete [] data;}
    void clear() {currentLength = 0;}
    int length() const {return currentLength;}
    
    void insert(int i, const elemType &x);
    void update(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
    
    seqList operator+(const seqList &q);
    seqList &operator=(const seqList &q);
};

template <class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType * tmp = data;
    
    maxSize *= 2;
    data = new elemType[maxSize];
    
    for (int i = 0; i < currentLength; ++i)
        data[i] = tmp[i];
    delete [] tmp;
}

template <class elemType>
seqList<elemType>::seqList(int initSize)
{
    if (initSize <= 0)
        throw IllegalSize();
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x)
{
    if (i < 0 || i > currentLength)
        throw OutOfBound();
    if (currentLength == maxSize)
        doubleSpace();
    for (int j = currentLength; j > i; j--)
        data[j] = data[j - 1];
    data[i] = x;
    ++currentLength;
}

template <class elemType>
void seqList<elemType>::update(int i, const elemType &x)
{
    if (i < 0 || i > currentLength - 1)
        throw OutOfBound();
    data[i] = x;
}

template <class elemType>
void seqList<elemType>::remove(int i)
{
    if (i < 0 || i > currentLength - 1)
        throw OutOfBound();
    for (int j = i; j < currentLength - 1; j++)
        data[j] = data[j + 1];
    --currentLength;
}

template <class elemType>
int seqList<elemType>::search(const elemType &x) const
{
    int i;
    for (i = 0; i < currentLength && data[i] != x; ++i);
    if (i == currentLength) return -1; else return i;
}

template <class elemType>
elemType seqList<elemType>::visit(int i) const
{
    if (i < 0 || i > currentLength - 1)
        throw OutOfBound();
    return data[i];
}

template <class elemType>
void seqList<elemType>::traverse() const
{
    cout << endl;
    for (int i = 0; i < currentLength; ++i)
        cout << data[i] << " ";
}

template <class T>
seqList<T> seqList<T>::operator+(const seqList<T> &q) {
    int length_of_this = (*this).length();
    seqList<T> r;
    for (int i = 0; i < length_of_this; i++)
    {
        r.insert(i, (*this).visit(i));
    }
    for (int i = 0; i < q.length(); i++)
    {
        r.insert(length_of_this+i, q.visit(i));
    }
    return r;
}

template <class T>
seqList<T> &seqList<T>::operator=(const seqList<T> &q) {
    if (this == &q) return *this;
    
    for (int i = 0; i < q.length(); i++)
    {
        (*this).insert(i, q.visit(i));
    }
    currentLength = q.length();
    return *this;
}

#endif /* seqList_hpp */
