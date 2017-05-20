//
//  selectSort.hpp
//  sort
//
//  Created by caiziruo on 27/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef selectSort_hpp
#define selectSort_hpp

#include <iostream>

template <class T>
void simpleSelectSort(T a[], int size)
{
    int i, j, k;
    T tmp;
    
    for (i = 0; i < size - 1; ++i) {
        k = i;
        for (j = i + 1; j < size; ++j)
            if (a[j] < a[k]) k = j;
        tmp = a[i];
        a[i] = a[k];
        a[k] = tmp;
    }
}

template <class T>
void percolateDown(T a[], int hole, int size, int typeOfHeap) {     //typeOfHeap = 0, smallest heap; 1, largest heap
    int child;
    T tmp = a[hole];
    
    if (typeOfHeap == 0) {
        for (; hole * 2 + 1 < size; hole = child) {
            child = hole * 2 + 1;
            if (child < size - 1 && a[child + 1] < a[child]) child++;
            if (a[child] < tmp) a[hole] = a[child];
            else break;
        }
    }
    else {
        for (; hole * 2 + 1 < size; hole = child) {
            child = hole * 2 + 1;
            if (child < size - 1 && a[child + 1] > a[child]) child++;
            if (a[child] > tmp) a[hole] = a[child];
            else break;
        }
    }
    a[hole] = tmp;
}

template <class T>
void heapSort(T a[], int size) {
    int i;
    T tmp;
    
    for (i = size / 2 - 1; i >= 0; i--)
        percolateDown(a, i, size, 1);
    
    for (i = size - 1; i > 0; --i) {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        percolateDown(a, 0, i, 1);
    }
}


#endif /* selectSort_hpp */
