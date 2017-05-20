//
//  SplayTree.hpp
//  searchTree
//
//  Created by caiziruo on 19/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef SplayTree_hpp
#define SplayTree_hpp

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class SplayTree
{
private:
	struct Node{
		T data;
		Node * left;
		Node * right;

		Node(const T & thedata, Node * lt = NULL, Node * rt = NULL):data(thedata), left(lt), right(rt) {}
	};
	Node * root;

	void makeEmpty(Node * &t) {
		if (t == NULL) return;
		if (t -> left != NULL) makeEmpty(t -> left);
		if (t -> right != NULL) makeEmpty(t -> right);
		delete t;
		t = NULL;
	}

public:
	SplayTree() {root = NULL;}
	~SplayTree() {makeEmpty(root);}
	bool find(const T &x) ;
	void insert(const T &x);
	void remove(const T &x);
	void levelTraverse() const;
};

template <class T>
bool SplayTree<T>::find(const T &x) {
	if (root == NULL) return false;
	Node * tmp = root;
	while (tmp != NULL && tmp -> data != x) {
		if (tmp -> data > x) tmp = tmp -> left;
		else tmp = tmp -> right;
	}
	if (tmp == NULL) return false;

	//x has been found, now let's splay!!!
	if (tmp == root) return true;
    tmp = root;
	link_stack<Node *> sta;
	while (tmp != NULL && tmp -> data != x) {
		if (tmp -> data > x) {sta.push(tmp); tmp = tmp -> left;}
		else {sta.push(tmp); tmp = tmp -> right;}
	}

	Node * parent = NULL, * grandparent = NULL;
	while (! sta.isEmpty() ) {
		parent = sta.pop();
		if (sta.isEmpty()) {
			if (parent -> left == tmp) {parent -> left = tmp -> right; tmp -> right = parent;}
			else {parent -> right = tmp -> left; tmp -> left = parent;}
			root = tmp;
			break;
		}
		else {
			grandparent = sta.pop();
			if (grandparent -> left -> left == tmp) {
				grandparent -> left = parent -> right;
				parent -> right = grandparent;
				parent -> left = tmp -> right;
				tmp -> right = parent;
			}
			else if (grandparent -> right -> right == tmp) {
				grandparent -> right = parent -> left;
				parent -> left = grandparent;
				parent -> right = tmp -> left;
				tmp -> left = parent;
			}
			else if (grandparent -> left -> right == tmp) {
				grandparent -> left = tmp -> right;
				parent -> right = tmp -> left;
				tmp -> right = grandparent;
				tmp -> left = parent;
			}
			else if (grandparent -> right -> left == tmp) {
				grandparent -> right = tmp -> left;
				parent -> left = tmp -> right;
				tmp -> left = grandparent;
				tmp -> right = parent;
			}

			if (root == grandparent) {root = tmp;}
			else {
				Node * grandgrandparent = sta.pop();
				if (grandgrandparent -> left == grandparent) grandgrandparent -> left = tmp;
				else grandgrandparent -> right = tmp;
				sta.push(grandgrandparent);
			}
		}
	}
	return true;
}

template <class T>
void SplayTree<T>::insert(const T &x) {
	if (root == NULL) {root = new Node(x); return;}
	if (root -> data == x) return;
	Node * tmp = root;
	while (tmp -> data != x) {
		if (tmp -> data < x) {
			if (tmp -> right == NULL) break;
			else tmp = tmp -> right;
		}
		else if (tmp -> data > x) {
			if (tmp -> left == NULL) break;
			else tmp = tmp -> left;
		}
		else return;
	}
	if (tmp -> data > x) {tmp -> left = new Node(x); return;}
	else {tmp -> right = new Node(x); return;}
}

template <class T>
void SplayTree<T>::remove(const T &x) {
	if (root == NULL) return;
	Node * tmp = root, * parent = root;
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
		Node * t = tmp -> right;
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
void SplayTree<T>::levelTraverse() const {
	linkQueue<Node *> que;
	que.enQueue(root);
	Node * current = NULL;

	while (! que.isEmpty()) {
		current = que.deQueue();
		cout << current -> data << " ";
		if (current -> left != NULL) que.enQueue(current -> left);
		if (current -> right != NULL) que.enQueue(current -> right);
	}
	return;
}


#endif /* SplayTree_hpp */
