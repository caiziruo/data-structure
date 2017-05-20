//
//  SonBrotherLinkTree.hpp
//  tree
//
//  Created by caiziruo on 10/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef SonBrotherLinkTree_hpp
#define SonBrotherLinkTree_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class SonBrotherLinkTree
{
private:
	struct Node
	{
		Node * left, * right;
		T data;

		Node(): left(NULL), right(NULL) {}
		Node(const T &x, Node * L = NULL, Node * R = NULL): data(x), left(L), right(R) {}
		~Node() {}
	};

	Node * root;

	void clear(Node * t) {
		if (t == NULL) return;
		if (t -> left != NULL) clear(t -> left);
		if (t -> right != NULL) clear(t -> right);
		delete t;
	}

	void preOrder(Node * t) const {
		if (t != NULL) {
			cout << t -> data << " ";
			Node * tmp = t -> left;
			while (tmp != NULL) {
				preOrder(tmp);
				tmp = tmp -> right;
			}
		}
	}
	void postOrder(Node * t) const {
		if (t != NULL) {
			Node * tmp = t -> left;
			while (tmp != NULL) {
				postOrder(tmp);
				tmp = tmp -> right;
			}
			cout << t -> data << " ";
		}
	}

	int height(Node * t) const {
		if (t != NULL) {
			Node * tmp = t -> left;
			int tmpheight = 0;
			while (tmp != NULL) {
				tmpheight = ((tmpheight < height(tmp))? height(tmp):tmpheight);
				tmp = tmp -> right;
			}
			return tmpheight + 1;
		}
		else return 0;
	}

	int size(Node * t) const {
		if (t != NULL) {
			return 1 + size(t -> left) + size(t -> right);
		}
		else return 0;
	}
public:
	SonBrotherLinkTree(): root(NULL) {}

	~SonBrotherLinkTree() {clear();}

	void clear() {
		if (root != NULL) clear(root); 
		root = NULL;
	}

	void preOrder() const {
		if (root != NULL) {
			cout << "\npre order traverse:";
			preOrder(root);
		}
	}
	void postOrder() const {
		if (root != NULL) {
			cout << "\npost order traverse:";
			postOrder(root);
		}
	}
	void levelTraverse() const;

	void createTree(T flag);

	int height() const {return height(root);}

	int size() const {return size(root);}
};

template <class T>
void SonBrotherLinkTree<T>::createTree(T flag) {
	linkQueue<Node *> que;
	Node * tmp, * sontmp;
	T x;

	cout << "\ninput root node:";
	cin >> x;
	root = new Node(x);
	que.enQueue(root);

	while (! que.isEmpty()) {
		tmp = que.deQueue();
		cout << "\ninput the sons of " << tmp -> data << "(input " << flag << " to terminate)";
		cin >> x;
		if (x != flag) {
			que.enQueue(tmp -> left = new Node(x));
			sontmp = tmp -> left;
			cin >> x;
			while (x != flag) {
				que.enQueue(sontmp -> right = new Node(x));
				sontmp = sontmp -> right;
				cin >> x;
			}
		}
	}
	cout << "create completed! \n";
}

template <class T>
void SonBrotherLinkTree<T>::levelTraverse() const {
	linkQueue<Node *> s;
	Node * current;

	cout << "traverse by lever:";
	s.enQueue(root);
	while (! s.isEmpty()) {
		current = s.deQueue();
		cout << current -> data << " ";
		current = current -> left;
		while (current != NULL) {
			s.enQueue(current);
			current = current -> right;
		}
	}
}


#endif /* SonBrotherLinkTree_hpp */
