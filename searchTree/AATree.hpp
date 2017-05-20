//
//  AATree.hpp
//  searchTree
//
//  Created by caiziruo on 18/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef AATree_hpp
#define AATree_hpp

#include <iostream>
using namespace std;

template <class T>
class AATree
{
private:
	struct AANode
	{
		T data;
		AANode * left;
		AANode * right;
		int level;

		AANode(const T & thedata, AANode * lt, AANode * rt, int lv = 1): data(thedata), left(lt), right(rt), level(lv) {}
	};
public:
	AATree(AANode * t = NULL) {root = t;}
	~AATree() {makeEmpty(root);}
	bool find(const T &x) const {return find(x, root);}
	void insert(const T &x) {insert(x, root);}
	void remove(const T &x) {remove(x, root);}

private:
	AANode * root;

	void insert(const T &x, AANode * &t);
	void remove(const T &x, AANode * &t);
	bool find(const T &x, AANode * t) const;
	void makeEmpty(AANode * &t);
	void LL(AANode * &t);
	void RR(AANode * &t);
};

template <class T>
bool AATree<T>::find(const T &x, AANode * t) const {
	if (t == NULL) return false;
	else if (x < t -> data) return find(x, t -> left);
	else if (t -> data < x) return find(x, t -> right);
	else return true;
}

template <class T>
void AATree<T>::makeEmpty(AANode * &t) {
	if (t != NULL) {
		makeEmpty(t -> left);
		makeEmpty(t -> right);
		delete t;
	}
	t = NULL;
}

template <class T>
void AATree<T>::LL(AANode * &t) {
	if (t -> left != NULL && t -> left -> level == t -> level) {
		AANode * t1 = t -> left;
		t -> left = t1 -> right;
		t1 -> right = t;
		t = t1;
	}
}

template <class T>
void AATree<T>::RR(AANode * &t) {
	if (t -> right != NULL && t -> right -> right != NULL && t -> right -> right -> level == t -> level) {
		AANode * t1 = t -> right;
		t -> right = t1 -> left;
		t1 -> left = t;
		t = t1;
		t -> level++;
	}
}

template <class T>
void AATree<T>::insert(const T &x, AANode * &t) {
	if (t == NULL) t = new AANode(x, NULL, NULL);
	else if (x < t -> data) insert(x, t -> left);
	else if (t -> data < x) insert(x, t -> right);
	else return;

	LL(t);
	RR(t);
    return;
}

template <class T>
void AATree<T>::remove(const T &x, AANode * &t) {
	if (t == NULL) return;
	if (x < t -> data) remove(x, t -> left);
	else if (t -> data < x) remove(x, t -> right);
	else if (t -> left != NULL && t -> right != NULL) {
		AANode * tmp = t -> right;
		while (tmp -> left != NULL) tmp = tmp -> left;
		t -> data = tmp -> data;
		remove(t -> data, t -> right);
	}
	else {
		AANode * oldNode = t;
		t = (t -> left != NULL)? t -> left : t -> right;
		delete oldNode;
        return;
	}
    
	if (t -> left == NULL || t -> right == NULL) t -> level = 1;
	else t -> level = min(t -> left -> level, t -> right -> level) + 1;
	if (t -> right != NULL && t -> right -> level > t -> level) t -> right -> level = t -> level;
	LL(t);
	if (t -> right != NULL) LL(t -> right);
	if (t -> right != NULL && t -> right -> right != NULL) LL(t -> right -> right);
	RR(t);
	if (t -> right != NULL) RR(t -> right);
}

#endif /* AATree_hpp */
