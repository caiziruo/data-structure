//
//  main.cpp
//  searchTree
//
//  Created by caiziruo on 12/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
using namespace std;
#include "BinarySearchTree.hpp"
#include "AvlTree.hpp"
#include "RedBlackTree.hpp"
#include "AATree.hpp"
#include "SplayTree.hpp"
#include "BPlusTree.hpp"

int main(int argc, const char * argv[]) {
	int a[] = {10, 8, 6, 21, 87, 56, 4, 0, 11, 3, 22, 7, 5, 34, 1, 2, 9};
	BinarySearchTree<int> tree;

	for (int i = 0; i < 17; ++i) tree.insert(a[i]);

//	cout << tree.find(12) << endl;
//	tree.remove(2);
//	cout << "after delete 2, find 2 is " << (tree.find(2)? "true":"false") << endl;
//	cout << tree.orderliness() << endl;

	

	return 0;
}
