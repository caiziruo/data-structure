//
//  insertSort.hpp
//  sort
//
//  Created by caiziruo on 27/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef insertSort_hpp
#define insertSort_hpp

#include <iostream>

template <class T>
void simpleInsertSort(T a[], int size) {
    int k;
    T tmp;
    
    for (int j = 1; j < size; ++j) {
        tmp = a[j];
        for (k = j - 1; tmp < a[k] && k >= 0; --k)
            a[k + 1] = a[k];
        a[k + 1] = tmp;
    }
}

template <class T>
void shellSort(T a[], int size) {
    int step, i, j;
    T tmp;
    
    for (step = size / 2; step > 0; step /= 2) {
        for (i = step; i < size; ++i) {
            tmp = a[i];
            for (j = i - step; j >= 0 && a[j] > tmp; j -= step)
                a[j + step] = a[j];
            a[j + step] = tmp;
        }
    }
}


#endif /* insertSort_hpp */
