//
//  BPlusTree.hpp
//  searchTree
//
//  Created by caiziruo on 20/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef BPlusTree_hpp
#define BPlusTree_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class BPlusTree
{
private:
	static int M, L, MM, LL;
	struct LeafNodeSon
	{
		T data[L];
		int numberofdata;
		LeafNodeSon(T d[L] = {NULL}, int numberofd = 0): data(d), numberofdata(numberofd) {}
	};

	struct BPlusNode
	{
		BPlusNode * son[M];
		int NumberOfSons;
		T smallestofsons[M - 1];
		
		int level;
		LeafNodeSon * leafson[M];
		BPlusNode(BPlusNode * s[M] = {NULL}, int l = 0, int nosons = 0, const T smallest[M-1] = {}, LeafNodeSon * leaf[M] = {NULL}):son(s), NumberOfSons(nosons), smallestofsons(smallest), level(l), leafson(leaf) {}
	};

	BPlusNode * root;

	void makeEmpty(BPlusNode * &t);
public:
	BPlusTree(int m, int l) {
		M = m;
		L = l;
		if (M % 2 == 0) MM = M / 2;
		else MM = M / 2 + 1;
		if (L % 2 == 0) LL = L / 2;
		else LL = L / 2 + 1;
		root = NULL;
	}
	~BPlusTree() {makeEmpty(root);}
	bool find(const T &x) const;
	void insert(const T &x);
	void remove(const T &x);
	void levelTraverse() const;
};

template <class T>
void BPlusTree<T>::makeEmpty(BPlusNode * &t) {
	if (t == NULL) return;
	if (t -> level == 0) {
		int i = 0;
		while (i < M && t -> leafson[i] != NULL) delete t -> leafson[i];
	}
	else {
		int i = 0;
		while (i < M && t -> son[i] != NULL) makeEmpty(t -> son[i]);
	}
	delete t;
	t = NULL;
	return;
}

template <class T>
bool BPlusTree<T>::find(const T &x) const {
	if (root == NULL) return false;
	BPlusTree * tmp = root;
	int i;

	while (tmp -> level > 0) {
		if (x < tmp -> smallestofsons[0]) tmp = tmp -> son[0];
		else {
			for (i = 0; i < tmp -> NumberOfSons - 1 && x >= tmp -> smallestofsons[i]; ++i) {}
				tmp = tmp -> son[i];
		}
	}
	LeafNodeSon * t = NULL;
	if (x < tmp -> smallestofsons[0]) t = tmp -> leafson[0];
	else {
		for (i = 0; i < tmp -> NumberOfSons - 1 && x < tmp -> smallestofsons[i]; ++i) {}
			t = tmp  ->  leafson[i];
	}
	for (i = 0; i < t -> numberofdata && x > t -> data[i]; ++i) {}
		if (i == t -> numberofdata) return false;
	if (x == t -> data[i]) return true;
	return false;
}

template <class T>
void BPlusTree<T>::insert(const T &x) {
	if (root == NULL) {
		T smallest[M - 1] = {};
		smallest[0] = x;
		root = new BPlusNode(0, 1, smallest);
		root -> leafson[0] = new LeafNodeSon;
		root -> leafson[0] -> data[0] = x;
		root -> leafson[0] -> numberofdata = 1;
	}
	else {}
	
}

template <class T>
void BPlusTree<T>::remove(const T &x) {

}

template <class T>
void BPlusTree<T>::levelTraverse() const {
	linkQueue<BPlusNode *> que;
	que.enQueue(root);
	BPlusNode * current = NULL;

	while (!que.isEmpty()) {
		current = que.deQueue();
		if (current -> level == 0) {
			for (int i = 0; i < current -> NumberOfSons; ++i) {
				for (int j = 0; j < current -> leafson[i] -> numberofdata; ++j) {cout << current -> leafson[i] -> data[j] << " ";}
			}
	}
	else {
		for (int i = 0; i < current -> NumberOfSons; ++i) {que.enQueue(current -> son[i]);}
	}
}
return;
}


#endif /* BPlusTree_hpp */
