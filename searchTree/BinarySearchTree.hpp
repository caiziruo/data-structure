//
//  BinarySearchTree.hpp
//  searchTree
//
//  Created by caiziruo on 12/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"


template <class T>
class BinarySearchTree {
private:
	struct BinaryNode{
		T data;
		BinaryNode * left;
		BinaryNode * right;

		BinaryNode(const T & thedata, BinaryNode * lt = NULL, BinaryNode * rt = NULL):data(thedata), left(lt), right(rt) {}
	};

	BinaryNode * root;

	void insert(const T &x, BinaryNode * &t);
	void remove(const T &x, BinaryNode * &t);
	bool find(const T &x, BinaryNode * t) const;
	void makeEmpty(BinaryNode * &t) {
		if (t == NULL) return;
		if (t -> left != NULL) makeEmpty(t -> left);
		if (t -> right != NULL) makeEmpty(t -> right);
		delete t;
		t = NULL;
	}
	bool orderliness(BinaryNode * t) const;
	void deleteInOpenInterval(const T &min, const T &max, BinaryNode * &t);

	void midOrder(int &j, int i, BinaryNode * t, T &x) const;

public:
	BinarySearchTree() {root = NULL;}
	~BinarySearchTree() {makeEmpty(root);}
	bool find(const T &x) const;
	bool isEmpty() const {return root == NULL;}
	void insert(const T &x);
	void remove(const T &x);
	void levelTraverse() const;
	bool orderliness() const {return orderliness(root);}
	void deleteAllSmallerThan(const T &x);
	void deleteAllLargerThan(const T &x);
	void deleteInOpenInterval(const T &min, const T &max);
	int depthOf(const T &x) const;
	T maximum() const;
	T minimum() const;
	T biggest(int i) const;
	T dequemin();
	T dequemax();
};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//template <class T>
	//bool BinarySearchTree<T>::find(const T &x) const {return find(x, root);}

template <class T>
bool BinarySearchTree<T>::find(const T &x) const {
	if (root == NULL) return false;
	BinaryNode * tmp = root;
	while (tmp != NULL && tmp -> data !=x) {
		if (tmp -> data < x) tmp = tmp -> right;
		else tmp = tmp -> left;
	}
	if (tmp == NULL) return false;
	return true;
}

template <class T>
bool BinarySearchTree<T>::find(const T &x, BinaryNode * t) const {
	if (t == NULL) return false;
	else if (x < t -> data) return find(x, t -> left);
	else if (t -> data < x) return find(x, t -> right);
	else return true;
}

	//	template <class T>
	//	void BinarySearchTree<T>::insert(const T &x) {
	//		insert(x,root);
	//	}

template <class T>
void BinarySearchTree<T>::insert(const T &x) {
	if (root == NULL) {root = new BinaryNode(x); return;}
	if (root -> data == x) return;
	BinaryNode * tmp = root;
	while (tmp -> data != x) {
		if (tmp -> data < x) {
			if (tmp -> right == NULL) break;
			else tmp = tmp -> right;
		}
		else if (tmp -> data > x) {
			if (tmp -> left == NULL) break;
			else tmp = tmp  -> left;
		}
		else return;
	}
	if (tmp -> data > x) {tmp -> left = new BinaryNode(x); return;}
	else {tmp -> right = new BinaryNode(x); return;}
}

template <class T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode * &t) {
	if (t == NULL) t = new BinaryNode(x, NULL, NULL);
	else if (x < t -> data) insert(x, t -> left);
	else if (t -> data < x) insert(x, t -> right);
}

	//	template <class T>
	//	void BinarySearchTree<T>::remove(const T &x)
	//	{
	//		remove(x, root);
	//	}

template <class T>
void BinarySearchTree<T>::remove(const T &x) {
	if (root == NULL) return;
	BinaryNode * tmp = root, * parent = root;
	while (tmp != NULL && tmp -> data != x) {
		parent = tmp;
		if (tmp -> data < x) tmp = tmp -> right;
		else tmp = tmp -> left;
	}
	if (tmp == NULL) return;

	if (tmp -> left == NULL && tmp -> right == NULL) {
		if (parent -> left == tmp) parent -> left = NULL;
		else parent -> right = NULL;
		delete tmp;
		return;
	}
	else if (tmp -> left == NULL && tmp -> right != NULL) {
		if (parent -> left == tmp) parent -> left = tmp -> right;
		else parent -> right = tmp -> right;
		delete tmp;
		return;
	}
	else if (tmp -> left != NULL && tmp -> right == NULL) {
		if (parent -> left == tmp) parent -> left = tmp -> left;
		else parent -> right = tmp -> left;
		delete tmp;
		return;
	}
	else {
		BinaryNode * t = tmp -> right;
		if (t -> left != NULL) {
			parent = t; 
			t = t -> left;
			while (t -> left != NULL) {
				parent = t;
				t = t -> left;
			}
			tmp -> data = t -> data;
			parent -> left = t -> right;
			delete t;
			return;
		}
		tmp -> data = t -> data;
		tmp -> right = t -> right;
		delete t;
		return;
	}
}

template <class T>
void BinarySearchTree<T>::remove(const T &x, BinaryNode * &t)
{
	if (t == NULL) return;
	if (x < t -> data) remove(x, t -> left);
	else if (t -> data < x) remove(x, t -> right);
	else if (t -> left != NULL && t -> right != NULL) {
		BinaryNode * tmp = t -> right;
		while (tmp -> left != NULL) tmp = tmp -> left;
		t -> data = tmp -> data;
		remove(t -> data, t -> right);
	}
	else {
		BinaryNode * oldNode = t;
		t = (t -> left != NULL)? t -> left : t -> right;
		delete oldNode;
	}
}

template <class T>
bool BinarySearchTree<T>::orderliness(BinaryNode * t) const {
	if (t == NULL) return true;  
	if (!orderliness(t -> left) || !orderliness(t -> right)) return false; 
	if (t -> left == NULL) {
		if (t -> right == NULL) return true;
		else return t -> right -> data > t -> data;
	}
	else {
		if (t -> right == NULL) return t -> left -> data < t -> data;
		else return (t -> left -> data < t -> data) && (t -> right -> data > t -> data);
	}
}

template <class T>
void BinarySearchTree<T>::deleteAllSmallerThan(const T &x) {
	if (root == NULL) return;
	else if (x == root -> data) {makeEmpty(root -> left); return;}

	BinaryNode * t, * parent = root;
	if (root -> data < x) {
		while (parent -> right != NULL && parent -> right -> data < x) {parent = parent -> right;}
		t = parent -> right;
		parent -> right = NULL;
		makeEmpty(root);
		root = t;
		if (root == NULL) return;
	}
	parent = root;
	while (parent -> left != NULL) {
		if (parent -> left -> data < x) {
			t = parent -> left;
			parent -> left = t -> right;
			t -> right = NULL;
			makeEmpty(t);
		}
		else {parent = parent -> left;}
	}
	return;
}

template <class T>
void BinarySearchTree<T>::levelTraverse() const {
	if (root == NULL) {cout << "No elements." << endl; return;}
	linkQueue<BinaryNode *> que;
	que.enQueue(root);
	BinaryNode * current = NULL;

	while (!que.isEmpty()) {
		current = que.deQueue();
		cout << current -> data << " ";
		if (current -> left != NULL) que.enQueue(current -> left);
		if (current -> right != NULL) que.enQueue(current -> right);
	}
	return;
}

template <class T>
void BinarySearchTree<T>::deleteAllLargerThan(const T &x) {
	if (root == NULL) return;
	else if (x == root -> data) {makeEmpty(root -> right); return;}

	BinaryNode * t, * parent = root;
	if (x < root -> data) {
		while (parent -> left != NULL && parent -> left -> data > x) {parent = parent -> left;}
		t = parent -> left;
		parent -> left = NULL;
		makeEmpty(root);
		root = t;
		if (root == NULL) return;
	}
	parent = root;
	while (parent -> right != NULL) {
		if (x < parent -> right -> data) {
			t = parent -> right;
			parent -> right = t -> left;
			t -> left = NULL;
			makeEmpty(t);
		}
		else {parent = parent -> right;}
	}
	return;
}

template <class T>
void BinarySearchTree<T>::deleteInOpenInterval(const T &min, const T &max) {
	deleteInOpenInterval(min, max, root);
	return;
}

template <class T>
void BinarySearchTree<T>::deleteInOpenInterval(const T &min, const T &max, BinaryNode * &t) {
	if (t == NULL) return;
	while (t -> data > min && t -> data < max) {remove(t -> data, t);}
	deleteInOpenInterval(min, max, t -> left);
	deleteInOpenInterval(min, max, t -> right);
}

template <class T>
int BinarySearchTree<T>::depthOf(const T &x) const {
	int depth = 0;
	if (root == NULL) return -1;
	BinaryNode * tmp = root;
	while (tmp != NULL && tmp -> data !=x) {
		if (tmp -> data < x) tmp = tmp -> right;
		else tmp = tmp -> left;
		++depth;
	}
	if (tmp == NULL) return -1;
	return depth;
}

template <class T>
T BinarySearchTree<T>::maximum() const {
	BinaryNode * tmp = root;
	while (tmp -> right != NULL) {tmp = tmp -> right;}
	return tmp -> data;
}

template <class T>
T BinarySearchTree<T>::minimum() const {
	BinaryNode * tmp = root;
	while (tmp -> left != NULL) {tmp = tmp -> left;}
	return tmp -> data;
}

template <class T>
T BinarySearchTree<T>::biggest(int i) const {
	int j = 0;
	T x;
	midOrder(j, i, root, x);
	return x;
}

template <class T>
void BinarySearchTree<T>::midOrder(int &j, int i, BinaryNode * t, T &x) const {
	if (t != NULL && i != j) {
		midOrder(j, i, t -> right, x);
		if (j != i) {
			x = t -> data;
			++j;
		}
		if (j != i) {
			midOrder(j, i, t -> left, x);
		}
	}
	return;
}

template <class T>
T BinarySearchTree<T>::dequemin() {
	T x;
	if (root -> left == NULL) {
		x = root -> data;
		remove(x, root);
		return x;
	}

	BinaryNode * tmp = root;
	while (tmp -> left -> left != NULL) tmp = tmp -> left;
	x = tmp -> left -> data;
	remove(x, tmp -> left);
	return x;
}

template <class T>
T BinarySearchTree<T>::dequemax() {
	T x;
	if (root -> right == NULL) {
		x = root -> data;
		remove(x, root);
		return x;
	}

	BinaryNode * tmp = root;
	while (tmp -> right -> right != NULL) tmp = tmp -> right;
	x = tmp -> right -> data;
	remove(x, tmp -> right);
	return x;
}

#endif /* BinarySearchTree_hpp */