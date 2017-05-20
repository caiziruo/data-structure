//
//  main.cpp
//  graph
//
//  Created by caiziruo on 30/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"
#include "adjListGraph.hpp"
#include "adjMatrixGraph.hpp"

int main(int argc, const char * argv[]) {
	int d1[] = {1, 2, 3, 4, 5, 6, 7};
	adjListGraph<int, int> graph1(7, d1);
	graph1.insert(4, 5, 1);
	graph1.insert(4, 6, 1);
	graph1.insert(6, 5, 1);
	graph1.insert(5, 1, 1);
	graph1.insert(6, 3, 1);
	graph1.insert(1, 2, 1);
	graph1.insert(3, 0, 1);
	graph1.insert(1, 3, 1);
	graph1.insert(3, 2, 1);
	// graph1.insert(2, 0, 1);
	// graph1.insert(0, 1, 1);
	// std::cout << graph1.haveCircle();
	// graph1.find(5, 3);
	// std::cout << graph1.pathBetween(5, 1);
	// graph1.dfs(5);
	// graph1.bfs(5);
	// graph1.noCircle(3, 999);
	// graph1.dijkstra_shortest(5, 999);
	graph1.dijkstra_priority(2, 999);

	int d2[] = {1, 2, 3, 4, 5, 6};
	adjMatrixGraph<int, int> graph2(6, d2, 999);
	graph2.insert(0, 1, 1);
	graph2.insert(1, 0, 1);
	graph2.insert(0, 5, 1);
	graph2.insert(5, 0, 1);
	graph2.insert(1, 2, 1);
	graph2.insert(2, 1, 1);
	graph2.insert(1, 4, 1);
	graph2.insert(4, 1, 1);
	graph2.insert(1, 5, 1);
	graph2.insert(5, 1, 1);
	graph2.insert(2, 3, 1);
	graph2.insert(3, 2, 1);
	graph2.insert(2, 4, 1);
	graph2.insert(4, 2, 1);
	graph2.insert(2, 5, 1);
	graph2.insert(5, 2, 1);
	graph2.insert(3, 4, 1);
	graph2.insert(4, 3, 1);
	graph2.insert(4, 5, 1);
	graph2.insert(5, 4, 1);
	// graph2.EulerCircuit(1);
	// graph2.kruskal();
	// graph2.prim(4, 999);
	// graph2.floyd();

	// int d3[] = {1, 2, 3, 4, 5, 6};
	// adjListGraph<int, int> graph3(6, d3);
	// graph3.insert(0, 1, 1);
	// graph3.insert(1, 0, 1);
	// graph3.insert(0, 5, 1);
	// graph3.insert(5, 0, 1);
	// graph3.insert(1, 2, 1);
	// graph3.insert(2, 1, 1);
	// graph3.insert(1, 4, 1);
	// graph3.insert(4, 1, 1);
	// graph3.insert(1, 5, 1);
	// graph3.insert(5, 1, 1);
	// graph3.insert(2, 3, 1);
	// graph3.insert(3, 2, 1);
	// graph3.insert(2, 4, 1);
	// graph3.insert(4, 2, 1);
	// graph3.insert(2, 5, 1);
	// graph3.insert(5, 2, 1);
	// graph3.insert(3, 4, 1);
	// graph3.insert(4, 3, 1);
	// graph3.insert(4, 5, 1);
	// graph3.insert(5, 4, 1);
	// // graph3.insert(3, 1, 1);
	// // graph3.insert(1, 3, 1);
	// // graph3.EulerWalk();
	// // graph3.kruskal();
	// // graph3.prim(4, 999);
	// // graph3.unweightedShortDistance(4, 999);
	// // graph3.dijkstra(1, 999);
	// // graph3.negativeWeightedShortDistance(1, 999);
	
	return 0;
}
