//
//  priorityQueue.hpp
//  priorityqueue
//
//  Created by caiziruo on 11/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef priorityQueue_hpp
#define priorityQueue_hpp

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"

template <class T>
class priorityQueue
{
private:
	int currentSize;
	T * array;
	int maxSize;
    int typeOfHeap; //0 means minheap, 1 means maxheap

    void doubleSpace();
	void buildHeap(); //transfer a complete binary tree to a heap
	void percolateDown(int hole);

public:
	priorityQueue(int capacity = 100) {
		//cout << "please input the type of the priority queue:(0 means min, 1 means max)";
		//cin >> typeOfHeap;
        typeOfHeap = 0;
		array = new T[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const T data[], int size);
	~priorityQueue() {delete [] array;}

	bool isEmpty() const {return currentSize == 0;}
	void enQueue(const T &x);
	T deQueue();
	T getHead() const {return array[1];}
	void levelTraverse() const;
	void changeType() {typeOfHeap = 1 - typeOfHeap; buildHeap();}
	int findMin(const T &x) const;
	void decreaseKey(int i, const T value);
};

template <class T>
void priorityQueue<T>::enQueue(const T &x) {
	if (currentSize == maxSize - 1) doubleSpace();

	int hole = ++currentSize;
	if (typeOfHeap == 0) {
		for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
	}
	else {
		for (; hole > 1 && x > array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
	}
	array[hole] = x;
}

template <class T>
T priorityQueue<T>::deQueue() {
	T Item;
	Item = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return Item;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole) {
	int child;
	T tmp = array[hole];

	if (typeOfHeap == 0) {
		for (; hole * 2 <= currentSize; hole = child) {
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child]) child++;
			if (array[child] < tmp) array[hole] = array[child];
			else break;
		}
	}
	else {
		for (; hole * 2 <= currentSize; hole = child) {
			child = hole * 2;
			if (child != currentSize && array[child + 1] > array[child]) child++;
			if (array[child] > tmp) array[hole] = array[child];
			else break;
		}
	}
	array[hole] = tmp;
}

template <class T>
void priorityQueue<T>::buildHeap() {
	for (int i = currentSize / 2; i > 0; i--) percolateDown(i);
}

template <class T>
priorityQueue<T>::priorityQueue(const T * items, int size):maxSize(size + 10), currentSize(size) {
	cout << "please input the type of the priority queue:(0 means min, 1 means max)";
	cin >> typeOfHeap;
	array = new T[maxSize];
	for (int i = 0; i < size; ++i) array[i + 1] = items[i];
		buildHeap();
}

template <class T>
void priorityQueue<T>::doubleSpace() {
	T * tmp = array;
	maxSize *= 2;
	array = new T[maxSize];

	for (int i = 0; i <= currentSize; ++i) array[i] = tmp[i];

		delete [] tmp;
}

template <class T>
void priorityQueue<T>::levelTraverse() const {
	for (int i = 1; i < currentSize + 1; ++i) {
		cout << array[i] << " ";
	}
}

template <class T>
int priorityQueue<T>::findMin(const T &x) const {
	if (array[1] > x) return 1;

	struct node {
		int index;
		T data;
		node(int i, T d): index(i), data(d) {}
		~node() {}
	};
	node * current, * newnode;
	newnode = new node(1, array[1]);

	linkQueue<node *> que1, que2;
	que1.enQueue(newnode);

	while (! que1.isEmpty()) {
		current = que1.deQueue();
		if (current -> index * 2 < currentSize + 1 && array[current -> index * 2] <= x) que1.enQueue(newnode = new node(current -> index * 2, array[current -> index * 2] ));
		else if (current -> index * 2 < currentSize + 1) que2.enQueue(newnode = new node(current -> index * 2, array[current -> index * 2] ));
		if (current -> index * 2 < currentSize &&  array[current -> index * 2 + 1] <= x) que1.enQueue(newnode  = new node(current -> index * 2 + 1, array[current -> index * 2 + 1]));
		else if (current -> index * 2 < currentSize) que2.enQueue(newnode  = new node(current -> index * 2 + 1, array[current -> index * 2 + 1]));
	}

	if (que2.isEmpty()) return 0;
	current = que2.deQueue();
	int minindex = current -> index;
	T mindata = current -> data;
	while (! que2.isEmpty()) {
		current = que2.deQueue();
		if (current -> data < mindata) {
			mindata = current -> data;
			minindex = current -> index;
		}

	}
	return minindex;
}

template <class T>
void priorityQueue<T>::decreaseKey(int i, const T value) {
	array[i] -= value;

	T tmpvalue = array[i];
	while (i > 1 && tmpvalue < array[i / 2]) {array[i] = array[i / 2]; i /= 2;}
	array[i] = tmpvalue;
}

#endif /* priorityQueue_hpp */
