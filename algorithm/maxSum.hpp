//
//  maxSum.hpp
//  algorithm
//
//  Created by caiziruo on 06/04/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef maxSum_hpp
#define maxSum_hpp

#include <iostream>

int maxSum(int a[], int left, int right)
{
	int maxLeft, maxRight, center;
	int leftSum = 0, rightSum = 0;
	int maxLeftTmp = 0, maxRightTmp = 0;

	if (left == right) return a[left] > 0? a[left]:0;
	center = (left + right) / 2;

	maxLeft = maxSum(a, left, center);
	maxRight = maxSum(a, center + 1, right);

	int i;
	for (i = center; i >= left; --i)
	{
		leftSum += a[i];
		if (leftSum > maxLeftTmp) maxLeftTmp = leftSum;
	}

	for (i = center + 1; i <= right; ++i) {
		rightSum += a[i];
		if (rightSum > maxRightTmp) maxRightTmp = rightSum;
	}

	int max = maxLeft;
	if (max < maxRight) max = maxRight;
	if (max < maxLeftTmp + maxRightTmp) max = maxLeftTmp + maxRightTmp;

	return max;
}
#endif /* maxSum_hpp */
