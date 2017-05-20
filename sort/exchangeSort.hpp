//
//  exchangeSort.hpp
//  sort
//
//  Created by caiziruo on 28/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef exchangeSort_hpp
#define exchangeSort_hpp

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"


template <class T>
void bubbleSort(T a[], int size) {
    int i, j;
    T tmp;
    bool flag;
    
    for (i = 1; i < size; ++i) {
        flag = false;
        for (j = 0; j < size - i; ++j) {
            if (a[j + 1] < a[j]) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                flag = true;
            }
        }
        if (! flag) break;
    }
}


template <class T>
int divide(T a[], int low, int high) {
    T k = a[low];
    do {
        while (low < high && a[high] >= k) --high;
        if (low < high) {a[low] = a[high]; ++low;}
        while (low < high && a[low] <= k) ++low;
        if (low < high) {a[high] = a[low]; --high;}
    } while (low != high);
    a[low] = k;
    return low;
}

//    template <class T>
//    void quickSort(T a[], int low, int high) {
//        int mid;
//        if (low >= high) return;
//        mid = divide(a, low, high);
//        quickSort(a, low, mid - 1);
//        quickSort(a, mid + 1, high);
//    }

template <class T>
void quickSort(T a[], int low, int high) {
    link_stack<int> sta;
    int tmplow, tmphigh;
    
    sta.push(low);
    sta.push(high);
    while (! sta.isEmpty()) {
        tmphigh = sta.pop();
        tmplow = sta.pop();
        if (tmplow >= tmphigh) continue;
        int mid;
        mid = divide(a, tmplow, tmphigh);
        sta.push(mid + 1);
        sta.push(tmphigh);
        sta.push(tmplow);
        sta.push(mid - 1);
    }
}

template <class T>
void quickSort(T a[], int size) {
    quickSort(a, 0, size - 1);
}

template <class T>
int deleteRepeated(T a[], int size) {
    quickSort(a, size);
    T tmp[size];
    for (int i = 0; i < size; ++i)
        tmp[i] = a[i];
    
    int finalSize = 0;
    for (int i = 1; i < size; ++i) {
        if (tmp[i] > a[finalSize]) {
            a[++finalSize] = tmp[i];
        }
    }
    return finalSize + 1;
}

void negativeToFront(int a[], int size) {
    int tmp, previousNegative = -1;
    for (int i = 0; i < size; ++i) {
        if (a[i] < 0) {
            tmp = a[++previousNegative];
            a[previousNegative] = a[i];
            a[i] = tmp;
        }
    }
}



#endif /* exchangeSort_hpp */
