//
//  openHashTable.hpp
//  hashTable
//
//  Created by caiziruo on 25/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef openHashTable_hpp
#define openHashTable_hpp

#include <iostream>
#include "hashTable.hpp"

template <class T>
class openHashTable:public hashTable<T> {
private:
    struct node{
        T data;
        struct node * next;
        
        node (const T &d, node * n = NULL) {data = d; next = n;}
        node () {next = NULL;}
    };

    node * * array; //array of pointers
    int size;
    
public:
    openHashTable(int length = 101, int (* f) (const T &x) = hashTable<T>::defaultKey);
    ~openHashTable();
    bool find(const T &x) const;
    bool insert(const T &x);
    bool remove(const T &x);
};

template <class T>
openHashTable<T>::openHashTable(int length, int (* f) (const T &x)) {
	size = length;
	array = new node * [size];
	hashTable<T>::key = f;
	for (int i = 0; i < size; ++i) array[i] = new node;
}

template <class T>
openHashTable<T>::~openHashTable() {
	node * p, * q;
	for (int i = 0; i < size; ++i) {
		p = array[i];
		do {q = p -> next; delete p; p = q;} while (p != NULL);
	}

	delete [] array;
}

template <class T>
bool openHashTable<T>::insert(const T &x) {
	int pos;
	node * p;
	pos = key(x) % size;
	p = array[pos] -> next;
	while (p != NULL && ! (p -> data == x)) p = p -> next;
	if (p == NULL) {
		p = new node(x);
		p -> next = array[pos] -> next;
		array[pos] -> next = p;
		return true;
	}
	return false;
}

template <class T>
bool openHashTable<T>::remove(const T &x) {
	int pos;
	node * p, * q;

	pos = key(x) % size;
	p = array[pos];
	while (p -> next != NULL && !(p -> next -> data == x) ) p = p -> next;
	if (p -> next == NULL) return false;
	else {
		q = p -> next;
		p -> next = q -> next;
		delete q;
		return true;
	}
}

template <class T>
bool openHashTable<T>::find(const T &x) const {
	int pos;
	node * p;

	pos = key(x) % size;
	p = array[pos];
	while (p -> next != NULL && !(p -> next -> data == x)) p = p -> next;
	if (p -> next != NULL) return true;
	else return false;
}


#endif /* openHashTable_hpp */
