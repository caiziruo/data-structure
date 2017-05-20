//
//  main.cpp
//  hashTable
//
//  Created by caiziruo on 20/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
#include "closeHashTable.hpp"

int main(int argc, const char * argv[]) {
    closeHashTable<int> table(3, 3);

	table.insert(1);
	table.insert(7);
	table.insert(21);
	table.insert(25);

	table.traverse();

    return 0;
}
