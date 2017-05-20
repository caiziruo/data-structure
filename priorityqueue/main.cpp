//
//  main.cpp
//  priorityqueue
//
//  Created by caiziruo on 11/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
using namespace std;
#include "priorityQueue.hpp"
#include "simulator.h"
#include "priorityLinkQueue.hpp"
#include "BernoulliQueue.hpp"

int main(int argc, const char * argv[]) {
    
//  simulator sim;
//  cout << sim.avgWaitTime() << endl;
    
    priorityQueue<int> pri;
    cout << "input the size of queue:";
    int size;
    cin >> size;
    for (int i = 0; i < size; ++i) {
        int j;
        cout << "please input the " << i + 1 << "-th element:";
        cin >> j;
        pri.enQueue(j); 
    }
    pri.levelTraverse();
    cout << endl;
//  pri.changeType();
//  pri.levelTraverse();
    while (true) {
        int i, j;
        cin >> i >> j;
        if (i == -1) return 0;
        pri.decreaseKey(i, j);
        pri.levelTraverse();
        cout << endl;
    }
    

//  priorityLinkQueue<int> pri2;
//  cout << "input the size of queue:";
//  int size;
//  cin >> size;
//  for (int i = 0; i < size; ++i) {
//      int j;
//      cout << "please input the " << i + 1 << "-th element:";
//      cin >> j;
//      pri2.enQueue(j);
//  }
//  pri2.levelTraverse();
    
//  BernoulliQueue<int> que;
//  cout << "Input the size of queue:";
//  int size;
//  cin >> size;
//  for (int i = 0; i < size; ++i) {
//      int j;
//      cout << "please input the " << i + 1 << "-th element:";
//      cin >> j;
//      que.enQueue(j);
//  }
//  cout << "level traverse:";
//  que.levelTraverse();
//  cout << endl;
//  
//  for (int i = 0; i < size; ++i) {cout << que.deQueue() << " ";}

    return 0;
}
