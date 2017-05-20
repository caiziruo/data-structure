//
//  hfTree.hpp
//  tree
//
//  Created by caiziruo on 08/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef hfTree_hpp
#define hfTree_hpp

#include <iostream>
using namespace std;

template <class T>
class hfTree {
private:
	struct Node
	{
		T data;
		int weight, parent, left, right;
	};

	Node * elem;
	int length;

public:
	hfTree(const T * x, const int * w, int size);
	~hfTree() {delete [] elem;}

	struct hfCode
	{
		T data;
		string code;
	};
	
	void getCode(hfCode result[]);
};

template <class T>
hfTree<T>::hfTree(const T *v, const int * w, int size) {
	const int MAX_INT = 32767;
	int min1, min2;
	int x, y;

	length = 2 * size;
	elem = new Node[length];

	for (int i = size; i < length; ++i) {
		elem[i].weight = w[i - size];
		elem[i].data = v[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}

	for (int i = size - 1; i > 0; --i) {
		min1 = min2 = MAX_INT;
		x = y = 0;
		for (int j = i + 1; j < length; ++j)
			if (elem[j].parent == 0) {
				if (elem[j].weight < min1) {
					min2 = min1;
					min1 = elem[j].weight;
					x = y;
					y = j;
				}
				else if (elem[j].weight < min2) {
					min2 = elem[j].weight;
					x = j;
				}
			}
			elem[i].weight = min1 + min2;
			elem[i].left = x;
			elem[i].right = y;//x >= y ????
			elem[i].parent = 0;
			elem[x].parent = i;
			elem[y].parent = i;
	}
}

template <class T>
void hfTree<T>::getCode(hfCode result[]) {
	int size = length / 2;
	int p, s;
	for (int i = size; i < length; ++i) {
		result[i - size].data = elem[i].data;
		result[i - size].code = "";
		p = elem[i].parent;
		s = i;
		while (p) {
			if (elem[p].left == s)
				result[i - size].code = '0' + result[i - size].code;
			else result[i - size].code = '1' + result[i - size].code;
			s = p;
			p = elem[p].parent;
		}
	}
}



#endif /* hfTree_hpp */
