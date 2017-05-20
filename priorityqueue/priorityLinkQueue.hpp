//
//  priorityLinkQueue.hpp
//  priorityqueue
//
//  Created by caiziruo on 11/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef priorityLinkQueue_hpp
#define priorityLinkQueue_hpp

#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"
#include <iostream>
using namespace std;

template <class T>
class priorityLinkQueue {
private:
	struct Node {
		T data;
		Node * left, * right, * parent;
		Node(const T &x, Node * pare = NULL, Node * L = NULL, Node * R = NULL): data(x), parent(pare), left(L), right(R) {}
		~Node() {}
	};
	Node * root;

    Node * findHoleParent() const;
    Node * findLastNode() const;
    void clear(Node * t) {
        if (t != NULL) {
            clear(t -> left);
            clear(t -> right);
            delete t;
        }
        
    }
	
public:
	priorityLinkQueue() {root = NULL;}
    ~priorityLinkQueue() {clear(root);}
	
    bool isEmpty() const {return root == NULL;}
    void enQueue(const T &x);
    T deQueue();
    T getHead() const {return root -> data;}
    void levelTraverse() const;
};

template <class T>
void priorityLinkQueue<T>::enQueue(const T &x) {
	if (root == NULL) {
		root = new Node(x);
		return;
	}

    Node * holeparent = findHoleParent();
    Node * hole;

    if (holeparent -> left == NULL) {
    	holeparent -> left = new Node(x, holeparent);
    	hole = holeparent -> left;	
    } 
    else {
    	holeparent -> right = new Node(x, holeparent);
    	hole = holeparent -> right;
    }
    while (x < holeparent -> data) {	
    	hole -> data = holeparent -> data;
    	hole = holeparent;
    	if (hole != root) holeparent = holeparent -> parent;
    	else {root -> data = x; return;}
    }
    hole -> data = x; 
    return;
}

template <class T>
T priorityLinkQueue<T>::deQueue() {
	Node * tmp = findLastNode();
	root -> data = tmp -> data;
	delete tmp;
	tmp = root;
	T x = root -> data;

	while (tmp -> left != NULL) {
		if (tmp -> right != NULL && tmp -> left -> data > tmp -> right -> data && x > tmp -> right -> data) {
			tmp -> data = tmp -> right -> data;
			tmp = tmp -> right;
		}
		else if (x > tmp -> left -> data) {
			tmp -> data = tmp -> left -> data;
			tmp -> left;
		}
		else {
			tmp -> data = x;
			return;
		}
	}
}

template <class T>
typename priorityLinkQueue<T>::Node * priorityLinkQueue<T>::findLastNode() const {
	linkQueue<Node *> que;
	que.enQueue(root);
	Node * current;

	while (! que.isEmpty()) {
		current = que.deQueue();
		if (current -> left != NULL) que.enQueue(current -> left);
		if (current -> right != NULL) que.enQueue(current -> right);
	}
	return current;

}

template <class T>
typename priorityLinkQueue<T>::Node * priorityLinkQueue<T>::findHoleParent() const {
	linkQueue<Node *> que;
	que.enQueue(root);
	Node * current;

	while (! que.isEmpty()) {
		current = que.deQueue();
		if (current -> left == NULL) return current;
		else que.enQueue(current -> left);
		if (current -> right == NULL) return current;
		else que.enQueue(current -> right);
	}
    return NULL;
}

template <class T>
void priorityLinkQueue<T>::levelTraverse() const {
	linkQueue<Node *> que;
	que.enQueue(root);
	Node * current;

	while (! que.isEmpty()) {
		current = que.deQueue();
		cout << current -> data << " ";
		if (current -> left != NULL) que.enQueue(current -> left);
		if (current -> right != NULL) que.enQueue(current -> right);
	}
}


#endif /* priorityLinkQueue_hpp */
