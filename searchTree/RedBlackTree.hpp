//
//  RedBlackTree.hpp
//  searchTree
//
//  Created by caiziruo on 18/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"


template <class T>
class RedBlackTree {
private:
	struct RedBlackNode {
		T data;
		RedBlackNode * left;
		RedBlackNode * right;
		int colour; //0-red, 1-black

		RedBlackNode(const T &element, RedBlackNode *lt, RedBlackNode * rt, int h = 0):data(element), left(lt), right(rt), colour(h) {}
	};

	RedBlackNode * root;
public:
	RedBlackTree(RedBlackNode * t = NULL) {root = t;}
	~RedBlackTree() {makeEmpty(root);}
	bool find(const T &x) const;
	void insert(const T &x);
	void remove(const T &x);

private:
	void makeEmpty(RedBlackNode * &t);
	void LL(RedBlackNode * &t);
	void LR(RedBlackNode * &t);
	void RL(RedBlackNode * &t);
	void RR(RedBlackNode * &t);
	void reLink(RedBlackNode * oldp, RedBlackNode * newp, link_stack<RedBlackNode *> &path);
	void insertReBalance(RedBlackNode * t, link_stack<RedBlackNode *> &path);
	void removeReBalance(RedBlackNode * t, link_stack<RedBlackNode *> &path);

};

template <class T>
void RedBlackTree<T>::reLink(RedBlackNode * oldp, RedBlackNode * newp, link_stack<RedBlackNode *> &path) {
	if (path.isEmpty()) root = newp;
	else {
		RedBlackNode * grandParent = path.pop();
		if (grandParent -> left == oldp) grandParent -> left = newp;
		else grandParent -> right = newp;
		path.push(grandParent);
	}
}

template <class T>
bool RedBlackTree<T>::find(const T &x) const {
	RedBlackNode * t = root;

	while (t != NULL && t -> data != x)
		if (t -> data > x) t = t -> left; else t = t -> right;

	if (t == NULL) return false; else return true;
}

template <class T>
void RedBlackTree<T>::makeEmpty(RedBlackNode * &t) {
	if (t != NULL) {
		makeEmpty(t -> left);
		makeEmpty(t -> right);
		delete t;
	}
	t = NULL;
}

template <class T>
void RedBlackTree<T>::LL(RedBlackNode * &t) {
	RedBlackNode * t1 = t -> left;
	t -> left = t1 -> right;
	t1 -> right = t;
	t = t1;
}

template <class T>
void RedBlackTree<T>::RR(RedBlackNode * &t) {
	RedBlackNode * t1 = t -> right;
	t -> right = t1 -> left;
	t1 -> left = t;
	t = t1;
}

template <class T>
void RedBlackTree<T>::LR(RedBlackNode * &t) {
	RR(t -> left);
	LL(t);
}

template <class T>
void RedBlackTree<T>::RL(RedBlackNode * &t) {
	LL(t -> right);
	RR(t);
}

template <class T>
void RedBlackTree<T>::insert(const T &x) {
	link_stack<RedBlackNode *> path;
	RedBlackNode * t, * parent;

	if (root == NULL) {
		root = new RedBlackNode(x, NULL, NULL, 1);
		return;
	}

	t = root;
	while (t != NULL && t -> data != x) {
		path.push(t);
		if (t -> data < x) t = t -> right; else t = t -> left;
	}
	if (t != NULL) return; //find the existed node

	t = new RedBlackNode(x, NULL, NULL);
	parent = path.pop();
	if (x < parent -> data) parent -> left = t; else parent -> right = t;

	if (parent -> colour == 1) return;

	path.push(parent);
	insertReBalance(t, path);
}

template <class T>
void RedBlackTree<T>::insertReBalance(RedBlackNode * t, link_stack<RedBlackNode *> &path) {
	RedBlackNode * parent, * grandParent, * uncle, * rootOfSubTree;

	parent = path.pop();
	while (parent -> colour == 0) {
		if (parent == root) {parent -> colour = 1; return;}

		grandParent = rootOfSubTree = path.pop();
		if (grandParent -> data > parent -> data) uncle = grandParent -> right;
		else uncle = grandParent -> left;

		if (uncle == NULL || uncle -> colour == 1) {
			if (grandParent -> left == parent) {
				if (t == parent -> left) {	//LLb
					parent -> colour = 1;
					grandParent -> colour = 0;
					LL(grandParent);
				}
				else {	//LRb
					grandParent -> colour = 0;
					t -> colour = 1;
					LR(grandParent);
				}
			}
			else if (t == parent -> right) { //RRb
				parent -> colour = 1;
				grandParent -> colour = 0;
				RR(grandParent);
			}
			else {	//RLb
				grandParent -> colour = 0;
				t -> colour = 1;
				RL(grandParent);
			}
			reLink(rootOfSubTree, grandParent, path);
			return;
		}
		else { //uncle = 0
			grandParent -> colour = 0;
			parent -> colour = 1;
			uncle -> colour = 1;
			if (root == grandParent) {root -> colour = 1; return;}
			t = grandParent;
			parent = path.pop();
		}
	}
	return;
}

template <class T>
void RedBlackTree<T>::remove(const T &x) {
	link_stack<RedBlackNode *> path;
	RedBlackNode * t = root, * old, * parent = NULL;

	while (t != NULL && t -> data != x) {
		path.push(t);
		if (t -> data > x) t = t -> left; else t = t -> right;
	}
	if (t == NULL) return;

	if (t -> left != NULL && t -> right != NULL) {
		path.push(t);
		old = t;
		t = t -> right;
		while (t -> left != NULL) {path.push(t); t = t -> left;}
		old -> data = t -> data;
	}

	if (t == root) {
		root = (t -> left? t -> left : t -> right);
		if (root != NULL) root -> colour = 1;
		return;
	}

    parent = path.pop();
	old = t;
	t = (t -> left? t -> left : t -> right);
	if (parent -> left == old) parent -> left = t; else parent -> right = t;

	if (old -> colour == 0) {delete old; return;}
	delete old;

	if (t != NULL) {t -> colour = 1; return;}

	path.push(parent);
	removeReBalance(t, path); //t == NULL, t's sibling != NULL
}

template <class T>
void RedBlackTree<T>::removeReBalance(RedBlackNode * t, link_stack<RedBlackNode *> &path) {
	RedBlackNode * parent, * sibling = NULL, * rootOfSubTree;

	parent = rootOfSubTree = path.pop();
	while (parent != NULL) {
		if (parent -> left == t) sibling = parent -> right;
		else sibling = parent -> left;
		if (sibling -> colour == 0) {
			sibling -> colour = 1;
			parent -> colour = 0;
			if (parent -> left == t) RR(parent); else LL(parent);
			reLink(rootOfSubTree, parent, path);
			path.push(parent);
			parent = rootOfSubTree;
		}
		else {
			if ((sibling -> left == NULL || sibling -> left -> colour == 1) && (sibling -> right == NULL || sibling -> right -> colour == 1)) {		//L0 or R0
				sibling -> colour = 0;
				if (parent -> colour == 0) {parent -> colour = 1; return;}
				else {
					t = parent;
					if (t == root) return;
					else parent = rootOfSubTree = path.pop();
				}
			}
			else break;
		}
	}

	if (parent -> left == t) {
		if (sibling -> left != NULL && sibling -> left -> colour == 0) {	//R1L or R2
			sibling -> left -> colour = parent -> colour;
			parent -> colour = 1;
			RL(parent);
			reLink(rootOfSubTree, parent, path);
		}
		else {	//R1R
			sibling -> colour = parent -> colour;
			sibling -> right -> colour = 1;
			parent -> colour = 1;
			RR(parent);
			reLink(rootOfSubTree, parent, path);
		}
	}
	else {
		if (sibling -> right != NULL && sibling -> right -> colour == 0) {	//L1R or L2
			sibling -> right -> colour = parent -> colour;
			parent -> colour = 1;
			LR(parent);
			reLink(rootOfSubTree, parent, path);
		}
		else {		//L1L
			sibling -> colour = parent -> colour;
			sibling -> left -> colour = 1;
			parent -> colour = 1;
			LL(parent);
			reLink(rootOfSubTree, parent, path);
		}
	}
}


#endif /* RedBlackTree_hpp */
