//
//  completeBinaryTree.hpp
//  tree
//
//  Created by caiziruo on 09/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef completeBinaryTree_hpp
#define completeBinaryTree_hpp

#include <iostream>
using namespace std;

template <class T>
class completeBinaryTree {
private:
    T * Node;
    int size;
    
public:
    completeBinaryTree(int length) {Node = new T[length + 1]; size = length;}
    ~completeBinaryTree() {delete [] Node;}
    
    void preOrderTraverse() const;
    void midOrderTraverse() const;
    void postOrderTraverse() const;
    void createTree();

};

template <class T>
void completeBinaryTree<T>::createTree() {
	cout << "\ninput root node:";
	cin >> Node[1];
	int i = 2;

	while (i < size + 1) {
		if (i % 2 == 0) {
			cout << "\ninput the left son of the node " << Node[i / 2] << ":";
			cin >> Node[i];
			++i;
		}
		else {
			cout << "\ninput the right son of the node " << Node[i / 2] << ":";
			cin >> Node[i];
			++i;
		}
	}
	cout << "create completed!";
}

template<class T>
void completeBinaryTree<T>::preOrderTraverse() const {
	bool traversedNode[size + 1];
    for (int i = 1; i < size + 1; ++i) {
        traversedNode[i] = false;
    }
    
	int i = 1;
	cout << Node[i] << " ";
	traversedNode[i] = true;

	while (i < size + 1 && i > 0) {
		if (i * 2 > size) {
			if (i % 2 == 0) {
				if (i > size - 1) {
					i /= 2;
					continue;
				}
				++i;
				cout << Node[i] << " ";
				traversedNode[i] = true;
				continue;
			}
			if (i % 2 == 1) {
				i /= 2;
				continue;
			}
		}
		if (i * 2 <= size) {
			if (traversedNode[2 * i] == false) {
				i *= 2;
				cout << Node[i] << " ";
				traversedNode[i] = true;
				continue;
			}
            else if (i < (size + 1)/2 && traversedNode[2 * i + 1] == false) {
                i = 2 * i + 1;
                cout << Node[i] << " ";
                traversedNode[i] = true;
                continue;
            }
			else {
				i /= 2;
				continue;
			}
		}
	}
}

template <class T>
void completeBinaryTree<T>::midOrderTraverse() const {
	bool traversedNode[size + 1];
	for (int i = 1; i < size + 1; ++i) {
		traversedNode[i] = false;
	}

	int i = 1;

	while (i < size + 1 && i > 0) {
		if (i * 2 > size) {
			if (i % 2 == 0) {
				cout << Node[i] << " ";
				traversedNode[i] = true;
				i /= 2;
				continue;
			}
			if (i % 2 == 1) {
				cout << Node[i] << " ";
				traversedNode[i] = true;
				i /= 2;
				continue;
			}
		}
		if (i * 2 <= size) {
			if (traversedNode[2 * i] == false) {
				i *= 2;				
				continue;
			}
            else if (traversedNode[i] == false) {
            	cout << Node[i] << " ";
            	traversedNode[i] = true;
            	continue;
            }
            else if (i < (size + 1)/2 && traversedNode[2 * i + 1] == false) {
                i = 2 * i + 1;
                continue;
            }
			else {
				i /= 2;
				continue;
			}
		}
	}
}

template <class T>
void completeBinaryTree<T>::postOrderTraverse() const {
	bool traversedNode[size + 1];
	for (int i = 1; i < size + 1; ++i) {
		traversedNode[i] = false;
	}

	int i = 1;

	while (i < size + 1 && i > 0) {
		if (i * 2 > size) {
			if (i % 2 == 0) {
				cout << Node[i] << " ";
				traversedNode[i] = true;
				i /= 2;
				continue;
			}
			if (i % 2 == 1) {
				cout << Node[i] << " ";
				traversedNode[i] = true;
				i /= 2;
				continue;
			}
		}
		if (i * 2 <= size) {
			if (traversedNode[2 * i] == false) {
				i *= 2;				
				continue;
			}
			else if (i < (size + 1) / 2 && traversedNode[2 * i + 1] == false) {
				i = 2 * i + 1;
				continue;
			}
            else if (traversedNode[i] == false) {
            	cout << Node[i] << " ";
            	traversedNode[i] = true;
            	continue;
            }
			else {
				i /= 2;
				continue;
			}
		}
	}
}

#endif /* completeBinaryTree_hpp */
