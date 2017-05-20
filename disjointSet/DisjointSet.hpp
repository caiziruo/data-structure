//
//  DisjointSet.hpp
//  disjointSet
//
//  Created by caiziruo on 28/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef DisjointSet_hpp
#define DisjointSet_hpp

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"


class DisjointSet
{
private:
	int size;
	int * parent;

public:
	DisjointSet(int s);
	~DisjointSet() {delete [] parent;}
	void Union(int root1, int root2);
	int Find(int x);
	
};

DisjointSet::DisjointSet(int n) {
	size = n;
	parent = new int[size];
	for (int i = 0; i < size; ++i) 
		parent[i] = -1;
}

//	int DisjointSet::Find(int x) {
//		if (parent[x] < 0) return x;
//		return parent[x] = Find(parent[x]);
//	}

int DisjointSet::Find(int x) {
	link_stack<int> sta;
	int tmp = x, y;

	while (parent[tmp] >= 0) {sta.push(tmp); tmp = parent[tmp];}
	while (! sta.isEmpty()) {y = sta.pop(); parent[y] = tmp;}

	return tmp;
}

void DisjointSet::Union(int root1, int root2) {
	if (root1 == root2) return;
	if (parent[root1] > parent[root2]) {
		parent[root2] += parent[root1];
		parent[root1] = root2;
	}
	else {
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}

void createSquarePuzzle(int size) {
	int num1, num2;
	DisjointSet ds(size * size);

	srand(int(time(0)));

	while (ds.Find(0) != ds.Find(size * size - 1)) {
		while (true) {
			num1 = rand() * size * size / RAND_MAX;
			num2 = num1 - size;
			if (num2 >= 0) {
				if (ds.Find(num1) != ds.Find(num2)) break;
			}
			num2 = num1 - 1;
			if (num1 % size != 0) {
				if (ds.Find(num1) != ds.Find(num2)) break;
			}
			num2 = num1 + size;
			if (num2 < size * size) {
				if (ds.Find(num1) != ds.Find(num2)) break;
			}
			num2 = num1 + 1;
			if (num2 % size != 0) {
				if (ds.Find(num1) != ds.Find(num2)) break;
			}
		}
		ds.Union(ds.Find(num1), ds.Find(num2));
		std::cout << '<' << num1 << ',' << num2 << ">,";
	}
}

void createRectanglePuzzle(int a, int b) {
	int num1, num2;
	DisjointSet ds(a * b);

	srand(int(time(0)));

	while (ds.Find(0) != ds.Find(a * b - 1)) {
		while (true) {
			num1 = rand() * a * b / RAND_MAX;
			num2 = num1 - a;
			if (num2 >= 0) if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 - 1;
			if (num1 % a != 0) if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 + a;
			if (num2 < a * b) if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 + 1;
			if (num2 % a != 0) if (ds.Find(num1) != ds.Find(num2)) break;
		}
		ds.Union(ds.Find(num1), ds.Find(num2));
		std::cout << '<' << num1 << "," << num2 << ">,";
	}
}



#endif /* DisjointSet_hpp */
