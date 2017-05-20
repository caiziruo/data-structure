//
//  BinaryTree.hpp
//  tree
//
//  Created by caiziruo on 06/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class BinaryTree
{
private:
	struct Node
	{
		Node * left, * right;
		T data;

		Node(): left(NULL), right(NULL) {}
		Node(const T &x, Node * L = NULL, Node * R = NULL):
		data(x), left(L), right(R) {}
		~Node() {}
	};

	Node * root;

	int height(Node * t) const {
		if (t == NULL) return 0;
		else {
			int lt = height(t -> left), rt = height(t -> right);
			return 1 + ((lt > rt)? lt:rt);
		}
	}

	void clear(Node * t) {
        if (t == NULL) return;
		if (t -> left != NULL) clear(t -> left);
		if (t -> right != NULL) clear(t -> right);
		delete t;
	}

	int size(Node * t) const {
		if (t == NULL) return 0;
		return 1 + size(t -> left) + size(t -> right);
	}

//	void preOrder(Node * t) const {
//		if (t != NULL) {
//			cout << t -> data << ' ';
//			preOrder(t -> left);
//			preOrder(t -> right);
//		}
//	}
    
//	void postOrder(Node * t) const {
//		if (t != NULL) {
//			postOrder(t -> left);
//			postOrder(t -> right);
//			cout << t -> data << ' ';
//		}
//	}

//	void midOrder(Node * t) const {
//		if (t != NULL) {
//			midOrder(t -> left);
//			cout << t -> data << ' ';
//			midOrder(t -> right);
//		}
//	}
	struct StNode
	{
		Node * node;
		int TimesPop;

		StNode (Node * N = NULL): node(N), TimesPop(0) {}
	};

	Node * copyTree(const Node * t) {
		if (t != NULL && t -> left != NULL && t -> right != NULL) {
            Node * tmp = new Node(t -> data, copyTree(t -> left), copyTree(t -> right));
			return tmp;
		}
		else if (t != NULL && t -> left != NULL) {
			Node * tmp = new Node(t -> data, copyTree(t -> left), NULL);
			return tmp;
		}
		else if (t != NULL && t -> right != NULL) {
			Node * tmp = new Node(t -> data, NULL, copyTree(t -> right));
			return tmp;
		}
		else if (t != NULL) {
			Node * tmp = new Node(t -> data);
			return tmp;
		}
		else return NULL;
	}

	void exchangeLeftRight(Node *t) {
		if (t == NULL) return;
		exchangeLeftRight(t -> left);
		exchangeLeftRight(t -> right);
		Node * tmp = t -> left;
		t -> left = t -> right;
		t -> right = tmp;
	}

	bool operatorEqual(const Node * a, const Node * b) const {
		if (a == NULL && b == NULL) return true;
		if (a != NULL && b != NULL && a -> data == b -> data) return operatorEqual(a -> left, b -> left) && operatorEqual(a -> right, b -> right);
		return false;
	}

public:
	BinaryTree(): root(NULL) {} //empty tree
	BinaryTree(const T &x) {root = new Node(x);} //construct a tree whose root is x
//	BinaryTree(Node * p) {root = p;} //
	BinaryTree(const BinaryTree &tree) {
		root = copyTree(tree.root);
		
	}
    
	~BinaryTree() {clear();}
    
    BinaryTree &operator=(const BinaryTree &tree) {
        if (this == &tree) return *this;
        
        this -> root = copyTree(tree.root);
        return *this;
    }

	T getRoot() const {return root -> data;}
	T getLeft() const {return root -> left -> data;}
	T getRight() const {return root -> right -> data;}

	void makeTree(const T &x, BinaryTree &lt, BinaryTree &rt) {
		clear(root); 
		root = new Node(x, lt.root, rt.root);
		lt.root = NULL;
		rt.root = NULL;
	}

//	void delLeft() {
//		BinaryTree tmp = root -> left;
//		root -> left = NULL;
//		tmp.clear();
//	}
//
//	void delRight() {
//		BinaryTree tmp = root -> right;
//		root -> right = NULL;
//		tmp.clear();
//	}

	bool isEmpty() const {
		return root == NULL;
	}

	void clear() {
		if (root != NULL) clear(root); 
		root = NULL; 
	}

	int size() const {return size(root);}

	int height() const {return height(root);}

	void preOrder() const;
//	{
//		if (root != NULL) {
//			cout << "\npre order traverse:";
//			preOrder(root);
//		}
//	}
//	
	void midOrder() const;
//	{
//		if (root != NULL) {
//			cout << "\nmid order traverse:";
//			midOrder(root);
//		}
//	}
//	
	void postOrder() const;
//	{
//		if (root != NULL) {
//			cout << "\npost order traverse:";
//			postOrder(root);
//		}
//	}

	void createTree(T flag);

	void exchangeLeftRight() {exchangeLeftRight(root);} //exchange every left son and right son of every node

	int numberOfDegreeTwo() const; // compute the number of nodes that has degree two

	void levelTraverse() const; //traverse by level

	bool operator==(const BinaryTree &tree2) const {return operatorEqual(root, tree2.root);} //overload == to judge whether two trees are the same
    
    bool completeJudge() const; //judge whether the tree is a complete binary tree

    bool mirror(BinaryTree tree2) const
    {
        tree2.exchangeLeftRight();
        return operatorEqual(root, tree2.root);
    }
};

template <class T>
void BinaryTree<T>::createTree(T flag)
{
	linkQueue<Node *> que;
	Node * tmp = NULL;
	T x, ldata, rdata;

	//create a tree, input flag means blank node
	cout << "\ninput root node:";
	cin >> x;
	root = new Node(x);
	que.enQueue(root);

	while (! que.isEmpty() ) 
	{
		tmp = que.deQueue();
		cout << "\ninput the two sons of " << tmp -> data << "(" << flag << " means blank node):";
		cin >> ldata >> rdata;
		if (ldata != flag) que.enQueue(tmp -> left = new Node(ldata));
		if (rdata != flag) que.enQueue(tmp -> right = new Node(rdata));
	}
	cout << " create completed! \n";
}

template <class T>
void BinaryTree<T>::preOrder() const {
	link_stack<Node *> s;
	Node * current = NULL;

	cout << "pre order traverse:";
	s.push(root);
	while (! s.isEmpty()) {
		current = s.pop();
		cout << current -> data;
		if (current -> right != NULL) s.push(current -> right);
		if (current -> left != NULL) s.push(current -> left);
	}
}

template <class T>
void BinaryTree<T>::midOrder() const {
	link_stack<StNode> s;
	StNode current(root);

	cout << "mid order traverse:";
	s.push(current);
	while (! s.isEmpty()) {
		current = s.pop();
		if (++current.TimesPop == 2) {
			cout << current.node -> data;
			if (current.node ->right != NULL)
				s.push(StNode(current.node -> right));
		}
		else {
			s.push(current);
			if (current.node -> left != NULL)
				s.push(StNode(current.node -> left));
		}
	}
}

template <class T>
void BinaryTree<T>::postOrder() const {
	link_stack<StNode> s;
	StNode current(root);

	cout << "post order traverse:";

	s.push(current);

	while (! s.isEmpty())
	{
		current = s.pop();
		if (++current.TimesPop == 3)
		{
			cout << current.node -> data;
			continue;
		}
		s.push(current);
		if (current.TimesPop == 1)
		{
			if (current.node -> left != NULL)
				s.push(StNode(current.node -> left));
		}
		else {
			if (current.node -> right != NULL)
				s.push(StNode(current.node -> right));
		}
	}
}

template <class T>
int BinaryTree<T>::numberOfDegreeTwo() const {
	link_stack<Node *> s;
	Node * current = NULL;
	int totalNumber = 0;

	cout << "pre order traverse:";
	s.push(root);
	while (! s.isEmpty()) {
		current = s.pop();
		if (current -> left != NULL && current -> right != NULL) {
			++totalNumber;
			s.push(current -> right);
			s.push(current -> left);
			continue;
		}
		if (current -> right != NULL) s.push(current -> right);
		if (current -> left != NULL) s.push(current -> left);
	}
	return totalNumber;
}

template <class T>
void BinaryTree<T>::levelTraverse() const {
	linkQueue<Node *> s;
	Node * current = NULL;

	cout << "traverse by level:";
	s.enQueue(root);
	while (! s.isEmpty()) {
		current = s.deQueue();
		if (current -> left != NULL) s.enQueue(current -> left);
		if (current -> right != NULL) s.enQueue(current -> right);
		cout << current -> data;
	}
}

template <class T>
bool BinaryTree<T>::completeJudge() const {
    linkQueue<Node *> s;
    Node * current = NULL;
    bool FirstNullNode = false;

    s.enQueue(root);
    while (! s.isEmpty()) {
    	current = s.deQueue();
    	if (current -> left != NULL) s.enQueue(current -> left);
		if (current -> right != NULL) s.enQueue(current -> right);

		if (FirstNullNode) {
			if (current -> left != NULL || current -> right != NULL) return false;
		}
        else
        {
            if (current -> left == NULL && current -> right != NULL) return false;
            if  ((current -> left == NULL && current -> right == NULL) || (current -> left != NULL && current -> right == NULL))
            {
                FirstNullNode = true;
                continue;
            }
        }
    }
    return true;
}



#endif /* BinaryTree_hpp */
