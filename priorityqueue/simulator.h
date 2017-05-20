//
//  simulator.h
//  priorityqueue
//
//  Created by caiziruo on 11/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef simulator_h
#define simulator_h

#include <iostream>
using namespace std;
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"
#include "priorityQueue.hpp"
#include <ctime>

class simulator{
    int noOfServer;
    double arrivalLow;
    double arrivalHigh;
    double serviceTimeLow;
    double serviceTimeHigh;
    int customNum;
    
    struct eventT
    {
        double time;
        int type;//0:arrive, 1:leave
        bool operator<(const eventT &e) const {return time < e.time;}
        bool operator>(const eventT &e) const {return time > e.time;}
    };
    
public:
    simulator();
    double avgWaitTime();
};

simulator::simulator() {
    cout << "Please input the number of server:";
    cin >> noOfServer;
    
    cout << "Please input the low and high arrival time interval:";
    cin >> arrivalLow >> arrivalHigh;
    
    cout << "Please input the low and high service time interval:";
    cin >> serviceTimeLow >> serviceTimeHigh;
    
    cout << "Please input the number of custom:";
    cin >> customNum;
    
    srand(double(time(NULL)));
}

double simulator::avgWaitTime() {
    int serverBusy = 0;   //the busy server number
    double currentTime;
    double totalWaitTime = 0;
    linkQueue<eventT> waitQueue;
    priorityQueue<eventT> eventQueue;
    
    eventT currentEvent;
    
    //initialize the arrival time
    int i;
    currentEvent.time = 0; 
    currentEvent.type = 0;
    for (i = 0; i < customNum; ++i) {
        currentEvent.time += arrivalLow + (arrivalHigh - arrivalLow + 1) * rand() / RAND_MAX;
        eventQueue.enQueue(currentEvent);
    }
    
    //simulate
    while (! eventQueue.isEmpty()) {
        currentEvent = eventQueue.deQueue();
        currentTime = currentEvent.time;
        switch(currentEvent.type) {
            case 0:
                if (serverBusy != noOfServer) {
                    ++serverBusy;
                    currentEvent.time += serviceTimeLow + (serviceTimeHigh - serviceTimeLow) * rand() / RAND_MAX;
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                }
                else waitQueue.enQueue(currentEvent);
                break;
            case 1:
                if (! waitQueue.isEmpty()) {
                    currentEvent = waitQueue.deQueue();
                    totalWaitTime += currentTime - currentEvent.time;
                    currentEvent.time = currentTime + serviceTimeLow + (serviceTimeHigh - serviceTimeLow) * rand() / RAND_MAX;
                    currentEvent.type = 1;
                    eventQueue.enQueue(currentEvent);
                }
                else --serverBusy;
        }
    }
    return totalWaitTime / customNum;
}


#endif /* simulator_h */
