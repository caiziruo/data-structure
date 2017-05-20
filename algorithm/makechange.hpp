//
//  makechange.hpp
//  algorithm
//
//  Created by caiziruo on 06/04/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef makechange_hpp
#define makechange_hpp
#include <iostream>

void makechange(int coins[], int differentCoins, int maxChange, int coinUsed[]) {
	coinUsed[0] = 0;
	for (int cents = 1; cents <= maxChange; cents++) {
		int minCoins = cents;
		for (int j = 1; j < differentCoins; j++) {
			if (coins[j] > cents) continue;
			if (coinUsed[cents - coins[j]] + 1 < minCoins) minCoins = coinUsed[cents - coins[j]] + 1;
		}
		coinUsed[cents] = minCoins;
	}
}

#endif /* makechange_hpp */
