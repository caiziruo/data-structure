//
//  main.cpp
//  sort
//
//  Created by caiziruo on 25/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
#include "insertSort.hpp"
#include "selectSort.hpp"
#include "exchangeSort.hpp"
#include "mergeSort.hpp"


int main(int argc, const char * argv[]) {
	int a[9] = {5, -2, 1, -1, -6, 7, -3, 9, 4};
//	quickSort(a, 9);

//	std::cout << deleteRepeated(a, 9) << "\n\n";
    negativeToFront(a, 9);
	for (int i = 0; i < 9; ++i) {
		std::cout << a[i] << std::endl;
	}
	return 0;
}
