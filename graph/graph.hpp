//
//  graph.hpp
//  graph
//
//  Created by caiziruo on 30/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>

template <class T> //T: type of edge
class graph {
protected:
    int Vers, Edges;
    
public:
    virtual bool insert(int u, int v, T w) = 0;
    virtual bool remove(int u, int v) = 0;
    virtual bool exist(int u, int v) const = 0;
    virtual int numOfVer() const {return Vers;}
    virtual int numOfEdge() const {return Edges;}
};



#endif /* graph_hpp */
