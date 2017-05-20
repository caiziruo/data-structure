//
//  main.cpp
//  queue
//
//  Created by caiziruo on 05/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
using namespace std;
#include "simulator.h"
#include "circularLinkQueue.hpp"

int main(int argc, const char * argv[]) {
	
    simulator sim;
    cout << "average waiting time:" << sim.avgWaitTime() << endl;
        
    
    return 0;
}
