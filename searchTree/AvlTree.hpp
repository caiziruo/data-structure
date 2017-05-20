//
//  AvlTree.hpp
//  searchTree
//
//  Created by caiziruo on 17/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef AvlTree_hpp
#define AvlTree_hpp

#include <iostream>

template <class T>
class AvlTree {
private:
	struct AvlNode {
		T data;
		AvlNode * left;
		AvlNode * right;
		int height;
		AvlNode(const T &element, AvlNode * lt, AvlNode * rt, int h = 0): data(element), left(lt), right(rt), height(h) {}
	};

	AvlNode * root;

	void insert(const T &x, AvlNode * &t);
	bool remove(const T &x, AvlNode * &t);
	void makeEmpty(AvlNode * t);
	int height(AvlNode * t) const {return t == NULL? -1:t -> height;}
	void LL(AvlNode * &t);
	void LR(AvlNode * &t);
	void RL(AvlNode * &t);
	void RR(AvlNode * &t);
	int max(int a, int b) {return(a > b)? a : b;}

public:
	AvlTree() {root = NULL;}
	~AvlTree() {makeEmpty(root);}
	bool find(const T &x) const;
	void insert(const T &x) {insert(x, root);}
	void remove(const T &x) {remove(x, root);}
};

template <class T>
bool AvlTree<T>::find(const T &x) const {
	AvlNode * t = root;

	while (t != NULL && t -> data != x)
		if (t -> data > x) t = t -> left; else t = t -> right;
	if (t == NULL) return false; else return true;
}

template <class T>
void AvlTree<T>::insert(const T &x, AvlNode * &t) {
	if (t == NULL) t = new AvlNode(x, NULL, NULL);
	else if (x < t -> data) {
		insert(x, t -> left);
		if (height(t -> left) - height(t -> right) == 2)
			{if (x < t -> left -> data) LL(t); else LR(t);}
	}
	else if (t -> data < x) {
		insert(x, t -> right);
		if (height(t -> right) - height(t -> left) == 2)
			{if (t -> right -> data < x) RR(t); else RL(t);}
	}
	t -> height = max(height(t -> left), height(t -> right)) + 1;
}

template <class T>
void AvlTree<T>::LL(AvlNode * &t) {
	AvlNode * t1 = t -> left;
	t -> left = t1 -> right;
	t1 -> right = t;
	t -> height = max(height(t -> left), height(t -> right)) + 1;
	t1 -> height = max(height(t1->left), height(t)) + 1;
	t = t1;
}

template <class T>
void AvlTree<T>::RR(AvlNode * &t) {
	AvlNode * t1 = t -> right;
	t -> right = t1 -> left;
	t1 -> left = t;
	t -> height = max(height(t -> left), height(t -> right)) + 1;
	t1 -> height = max(height(t1 -> right), height(t)) + 1;
	t = t1;
}

template <class T>
void AvlTree<T>::LR(AvlNode * &t) {
	RR(t -> left);
	LL(t);
}

template <class T>
void AvlTree<T>::RL(AvlNode * &t) {
	LL(t -> right);
	RR(t);
}

template <class T>
bool AvlTree<T>::remove(const T &x, AvlNode * &t) {
	bool stop = false;
	int subTree; //1 means the deletion occurs on the left tree, 2 means right tree

	if (t == NULL) return true;
	if (x < t -> data) {stop = remove(x, t -> left); subTree = 1;}
	else if (t -> data < x) {stop = remove(x, t -> right); subTree = 2;}
	else if (t -> left != NULL && t -> right != NULL) {
		AvlNode * tmp = t -> right;
		while (tmp -> left != NULL) tmp = tmp -> left;
		t -> data = tmp -> data;
		stop = remove(t -> data, t -> right);
		subTree = 2;
	}
	else {
		AvlNode * oldNode = t;
		t = (t -> left != NULL)? t -> left : t -> right;
		delete oldNode;
		return false;
	}

	if (stop) return true;
	int bf;
	switch(subTree) {
		case 1:
		bf = height(t -> left) - height(t -> right);
		if (bf == 0) return false;
		if (bf == -1) return true;
		if (bf == -2) {
			int bfr = height(t -> right -> left) - height(t -> right -> right);
			switch (bfr) {
				case 0: RR(t); return true;
				case -1: RR(t); return false;
				default: RL(t); return false;
			}
		}
		break;
		case 2:
		bf = height(t -> left) - height(t -> right);
		if (bf == 0) return false;
		if (bf == 1) return true;
		if (bf == 2) {
			int bfl = height(t -> left -> left) - height(t -> left -> right);
			switch (bfl) {
				case 0: LL(t); return true;
				case 1: LL(t); return false;
				default: LR(t); return false;
			}
		}
	}
	return false;
}

template <class T>
void AvlTree<T>::makeEmpty(AvlNode * t) {
	if (t == NULL) return;
	if (t -> left != NULL) makeEmpty(t -> left);
	if (t -> right != NULL) makeEmpty(t -> right);
	delete t;
}

#endif /* AvlTree_hpp */
