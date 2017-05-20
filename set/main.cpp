//
//  main.cpp
//  set
//
//  Created by caiziruo on 12/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

template <class T>
int seqSearch(vector<T> &data, const T &x) {
    data[0] = x;
    int i;
    for (i = data.size() + 1; x != data[i]; --i);
    return i;
}

template <class T>
int binarySearch(const vector<T> &data, const T &x) {
    int low = 1, high = data.size() + 1, mid;
    while (low <= high) {
    	mid = (low + high) / 2;
    	if (x == data[mid]) return mid;
    	if (x < data[mid]) high = mid - 1;
    	else low = mid + 1;
    }
    return 0;
}

template <class T>
int binarySearch(const T * a, const T &x, int min, int max) {
	if (min < max) {
        if (max - min == 1) {
            if (a[min] == x) return min;
            if (a[max] == x) return max;
            return -1;
        }
		int tmp = min + (max - min) / 2;
		if (x < a[tmp]) return binarySearch(a, x, min, tmp);
		else if (x == a[tmp]) return tmp;
		else return binarySearch(a, x, tmp, max);
	}
	else if (a[min] == x) {
		return min;
	}
	else return -1;
}


int main(int argc, const char * argv[]) {
//	vector<int> v;
    int a[] = {1, 2, 3, 4, 5, 8, 11, 14, 16, 20, 25};
//	for (int i = 0; i < 11; ++i) v.push_back(a[i]);
    cout << binarySearch(a, 5, 0, 10);

//	cout << binarySearch(v, 11);
    return 0;
}
