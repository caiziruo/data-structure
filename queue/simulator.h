//
//  simulator.h
//  queue
//
//  Created by caiziruo on 06/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef simulator_h
#define simulator_h

#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include "linkQueue.h"

class simulator {
    double arrivalLow;
    double arrivalHigh;
    double serviceTimeLow;
    double serviceTimeHigh;
    int customNum;
    
public:
    simulator();
    
    double avgWaitTime() const;
};

simulator::simulator() {
    cout << "Please input the arrival time interval:";
    cin >> arrivalLow >> arrivalHigh;
    
    cout << "Please input the service time interval:";
    cin >> serviceTimeLow >> serviceTimeHigh;
    
    cout << "Please input the custom number:";
    cin >> customNum;
    
    srand(double(time(NULL)));
}

double simulator::avgWaitTime() const{
    double currentTime = 0;
    double totalWaitTime = 0;
    double eventTime;
    linkQueue<double> customerQueue;
    int i;
    
    for (i = 0; i < customNum; ++i) {
        currentTime += arrivalLow + (arrivalHigh - arrivalLow) * rand() / RAND_MAX;
        customerQueue.enQueue(currentTime);
    }
    
    currentTime = 0;
    while (! customerQueue.isEmpty()) {
        eventTime = customerQueue.deQueue();
        if (eventTime < currentTime)
            totalWaitTime += currentTime - eventTime;
        else currentTime = eventTime;
        currentTime += serviceTimeLow + (serviceTimeHigh - serviceTimeLow) * rand() / RAND_MAX;
    }
    return totalWaitTime / customNum;
}


#endif /* simulator_h */
