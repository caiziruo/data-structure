//
//  main.cpp
//  list
//
//  Created by caiziruo on 23/02/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
#include "seqList.hpp"
#include "duLinkList.hpp"
#include "linkList.hpp"
#include "circular_linked_list.hpp"
#include "dual_circular_linked_list.hpp"

int main(int argc, const char * argv[]) {
    duLinkList<int> list1, list2, list3;
    
    list1.insert(0, 1);
    list1.insert(0, 3);
    list1.traverse();
    list2.insert(0, 3);
    list2.insert(0, 4);
    list2.insert(0, 5);
    list2.traverse();
    list3 = list1 + list2 + list2 + list1;
    list3.traverse();
    
    
    return 0;
}
