//
//  adjMatrixGraph.hpp
//  graph
//
//  Created by caiziruo on 30/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef adjMatrixGraph_hpp
#define adjMatrixGraph_hpp

#include <iostream>
#include "graph.hpp"
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"
#include "../../../chapter6/priorityqueue/priorityqueue/priorityQueue.hpp"
#include "../../../chapter11/disjointSet/disjointSet/DisjointSet.hpp"


template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfEdge> 
{
private:
	TypeOfEdge ** edge;
	TypeOfVer * ver;
	TypeOfEdge noEdge;
	
public:
	adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v) const;
	~adjMatrixGraph();

	void dfs() const;
	void bfs() const;
	void EulerCircuit(TypeOfVer start);
	void kruskal() const;
	void prim(TypeOfEdge infinity) const;
	void prim(TypeOfVer startv, TypeOfEdge infinity) const;
	void floyd() const;

private:
	void dfs(int start, bool visited[]) const;
    
    struct EulerNode
    {
        int data;
        EulerNode * next;
        EulerNode(int ver, EulerNode * n = NULL) {data = ver; next = n;}
    };
    EulerNode * EulerCircuit(int start, EulerNode * & end, int numOfDegree[]);
    TypeOfEdge ** clone() const;

	struct edge
	{
		int beg, end;
		TypeOfEdge w;
		bool operator < (const edge & rp) const {return w < rp.w;}
		bool operator > (const edge & rp) const {return w > rp.w;}
	};
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], TypeOfEdge noEdgeFlag) {
	int i, j;

	graph<TypeOfEdge>::Vers = vSize;
	graph<TypeOfEdge>::Edges = 0;
	noEdge = noEdgeFlag;

	ver = new TypeOfVer[vSize];
	for (i = 0; i < vSize; ++i) 
		ver[i] = d[i];

	edge = new TypeOfEdge * [vSize];
	for (i = 0; i < vSize; ++i) {
		edge[i] = new TypeOfEdge[vSize];
		for (j = 0; j < vSize; ++j)
			edge[i][j] = noEdge;
		edge[i][i] = 0;
	}
}

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
	delete [] ver;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		delete [] edge[i];
	delete [] edge;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w) {
	if (u < 0 || u > graph<TypeOfEdge>::Vers - 1 || v < 0 || v > graph<TypeOfEdge>::Vers - 1) return false;
	if (edge[u][v] != noEdge) return false;

	edge[u][v] = w;
	++graph<TypeOfEdge>::Edges;
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v) {
	if (u < 0 || u > graph<TypeOfEdge>::Vers - 1 || v < 0 || v > graph<TypeOfEdge>::Vers - 1) return false;
	if (edge[u][v] == noEdge) return false;

	edge[u][v] = noEdge;
	--graph<TypeOfEdge>::Edges;
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const {
	if (u < 0 || u > graph<TypeOfEdge>::Vers - 1 || v < 0 || v > graph<TypeOfEdge>::Vers - 1) return false;
	if (edge[u][v] == noEdge) return false;
	else return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs() const {
	bool visited[graph<TypeOfEdge>::Vers];

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	std::cout << "DFS:" << std::endl;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[i] == true) continue;
		dfs(i, visited);
		std::cout << std::endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const {
	std::cout << ver[start] << '\t';
	visited[start] = true;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[i] == false && edge[start][i] != noEdge) dfs(i, visited);
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::bfs() const {
	bool visited[graph<TypeOfEdge>::Vers];
	linkQueue<int> q;
	int currentNode;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	std::cout << "BFS:" << std::endl;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[i] == true) continue;
		q.enQueue(i);
		while (! q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true) continue;

			std::cout << ver[currentNode] << '\t';
			visited[currentNode] = true;

			for (int j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
				if (visited[j] == false && edge[currentNode][j] != noEdge) q.enQueue(j);
			}
		}
		std::cout << std::endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start) {
	EulerNode * beg, * end, * p, * q, * tb, * te;
	int numOfDegree[graph<TypeOfEdge>::Vers];
	TypeOfEdge ** tmp;

	if (graph<TypeOfEdge>::Edges == 0) {std::cout << "No Euler circuit." << std::endl; return;}
	int i, j;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		numOfDegree[i] = 0;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {if (edge[i][j] != noEdge && i != j) numOfDegree[i]++;}
		if (numOfDegree[i] == 0 || numOfDegree[i] % 2 == 1) {std::cout << "No Euler circuit." << std::endl; return;}
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (ver[i] == start) break;
	if (i == graph<TypeOfEdge>::Vers) {std::cout << "Starting vertex does not exist." << std::endl; return;}

	tmp = clone();

	beg = EulerCircuit(i, end, numOfDegree);
	while (true) {
		p = beg;
		while (p -> next != NULL) {
			if (numOfDegree[p -> next -> data] > 0) break;
			else p = p -> next;
		}
		if (p -> next == NULL) break;
		q = p -> next;
		tb = EulerCircuit(q -> data, te, numOfDegree);
		te -> next = q -> next;
		p -> next = tb;
		delete q;
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {delete [] edge[i];}
	delete [] edge;
	edge = tmp;

	std::cout << "Euler circuit:" << std::endl;
	while (beg != NULL) {
		std::cout << ver[beg -> data] << '\t';
		p = beg;
		beg = beg -> next;
		delete p;
	}
	std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
TypeOfEdge ** adjMatrixGraph<TypeOfVer, TypeOfEdge>::clone() const {
	TypeOfEdge ** tmp = new TypeOfEdge * [graph<TypeOfEdge>::Vers];

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		tmp[i] = new TypeOfEdge[graph<TypeOfEdge>::Vers];
		for (int j = 0; j < graph<TypeOfEdge>::Vers; ++j) 
			tmp[i][j] = edge[i][j];
	}
	return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
typename adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerNode * adjMatrixGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode * & end, int numOfDegree[]) {
	EulerNode * beg;
	int nextNode;

	beg = end = new EulerNode(start);

	int i;
	while (numOfDegree[start] > 0) {
		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) 
			if (edge[start][i] != noEdge && start != i) break;
		nextNode = i;

		adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(start, nextNode);
		adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(nextNode, start);
		numOfDegree[start]--;
		numOfDegree[nextNode]--;

		start = nextNode;
		end -> next = new EulerNode(start);
		end = end -> next;
	}

	return beg;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::kruskal() const {
	int edgesAccepted = 0, u, v;

	struct edge e;
	DisjointSet ds(graph<TypeOfEdge>::Vers);
	priorityQueue<struct edge> pq;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (int j = i + 1; j < graph<TypeOfEdge>::Vers; ++j) {
			if (edge[i][j] != noEdge) {
				e.beg = i;
				e.end = j;
				e.w = edge[i][j];
				pq.enQueue(e);
			}
		}
	}

	while (edgesAccepted < graph<TypeOfEdge>::Vers - 1) {
		e = pq.deQueue();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		if (u != v) {
			edgesAccepted++;
			ds.Union(u, v);
			std::cout << '(' << ver[e.beg] << ',' << ver[e.end] << ")\t";
		}
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge infinity) const {
	bool * flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge * lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * startNode = new int[graph<TypeOfEdge>::Vers];

	TypeOfEdge min;
	int start, i, j;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[i] = false;
		lowCost[i] = infinity;
	}

	start = 0;
	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[start] = true;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			if (i != j && edge[start][j] != infinity && ! flag[j] && lowCost[j] > edge[start][j]) {
				lowCost[j] = edge[start][j];
				startNode[j] = start;
			}
		}
		min = infinity;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j)
			if (lowCost[j] < min) {min = lowCost[j]; start = j;}
		std::cout << '(' << ver[startNode[start]] << ',' << ver[start] << ")\t";
		lowCost[start] = infinity;
	}
	delete [] flag;
	delete [] startNode;
	delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfVer startv, TypeOfEdge infinity) const {
	bool * flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge * lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * startNode = new int[graph<TypeOfEdge>::Vers];

	TypeOfEdge min;
	int start, i, j;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[i] = false;
		lowCost[i] = infinity;
	}

	int startInt;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (ver[i] == startv) {startInt = i; break; }
	}
	start = startInt;
	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[start] = true;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			if (i != j && edge[start][j] != infinity && ! flag[j] && lowCost[j] > edge[start][j]) {
				lowCost[j] = edge[start][j];
				startNode[j] = start;
			}
		}
		min = infinity;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j)
			if (lowCost[j] < min) {min = lowCost[j]; start = j;}
		std::cout << '(' << ver[startNode[start]] << ',' << ver[start] << ")\t";
		lowCost[start] = infinity;
	}
	delete [] flag;
	delete [] startNode;
	delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::floyd() const {
	TypeOfEdge ** d = new TypeOfEdge * [graph<TypeOfEdge>::Vers];
	int ** prev = new int * [graph<TypeOfEdge>::Vers];
	int i, j, k;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {		//initialization
		d[i] = new TypeOfEdge[graph<TypeOfEdge>::Vers];
		prev[i] = new int[graph<TypeOfEdge>::Vers];
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			d[i][j] = edge[i][j];
			prev[i][j] = (edge[i][j] != noEdge)? i: -1;
		}
	}

	for (k = 0; k < graph<TypeOfEdge>::Vers; ++k) {
		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
			for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
				if (d[i][k] + d[k][j] < d[i][j]) {d[i][j] = d[i][k] + d[k][j]; prev[i][j] = prev[k][j]; }
			}
		}
	}

	std::cout << "Shortest path length:" << std::endl;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			std::cout << d[i][j] << '\t';
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Shortest path:" << std::endl;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			std::cout << ver[prev[i][j]] << '\t';
		}
		std::cout << std::endl;
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		delete [] d[i];
	}
	delete [] d;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		delete [] prev[i];
	}
	delete [] prev;
}

#endif /* adjMatrixGraph_hpp */
