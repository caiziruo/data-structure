//
//  hashTable.hpp
//  hashTable
//
//  Created by caiziruo on 25/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef hashTable_hpp
#define hashTable_hpp

#include <iostream>

template <class T>
class hashTable {
protected:
    int (* key) (const T &x);	//T x -> int
    static int defaultKey(const int &k) {return k;}
    
public:
    virtual bool find(const T &x) const = 0;
    virtual bool insert(const T &x) = 0;
    virtual bool remove(const T &x) = 0;
};

#endif /* hashTable_hpp */
