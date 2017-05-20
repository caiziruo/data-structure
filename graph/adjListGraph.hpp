//
//  adjListGraph.hpp
//  graph
//
//  Created by caiziruo on 30/03/2017.
//  Copyright © 2017 caiziruo. All rights reserved.
//

#ifndef adjListGraph_hpp
#define adjListGraph_hpp

#include <iostream>
#include "../../../chapter4/queue/queue/linkQueue.h"
#include "../../../chapter3/stack/stack/link_stack.h"
#include "../../../chapter6/priorityqueue/priorityqueue/priorityQueue.hpp"
#include "../../../chapter11/disjointSet/disjointSet/DisjointSet.hpp"
#include "graph.hpp"

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public graph<TypeOfEdge>
{
private:
	struct edgeNode
	{
		int end;
		TypeOfEdge weight;
		edgeNode * next;

		edgeNode(int e, TypeOfEdge w, edgeNode * n = NULL) {end = e; weight = w; next = n;}
	};

	struct verNode
	{
		TypeOfVer ver;
		edgeNode * head;

		verNode(edgeNode * h = NULL) {head = h;}
	};

	verNode * verList;

public:
	adjListGraph(int vSize, const TypeOfVer d[]);
	~adjListGraph();
	bool insert(int u, int v, TypeOfEdge w);
	bool remove(int u, int v);
	bool exist(int u, int v) const;

	void dfs() const;
	void bfs() const;

	void EulerCircuit(TypeOfVer start);
	void topSort() const;
	// void strongConnectedComponent();
	bool haveCircle() const;
	void find(TypeOfVer start, int length) const;	//find simple path of given length
	bool pathBetween(TypeOfVer start, TypeOfVer end) const;
	void EulerWalk();
	void dfs(TypeOfVer start) const;
	void bfs(TypeOfVer start) const;
	void kruskal() const;
	void prim(TypeOfEdge noEdge) const;
	void prim(TypeOfVer start, TypeOfEdge noEdge) const;
	void unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const;
	void dijkstra(TypeOfVer start, TypeOfEdge noEdge) const;
	void negativeWeightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const;
	void noCircle(TypeOfVer start, TypeOfEdge infinity) const;
	void dijkstra_shortest(TypeOfVer start, TypeOfEdge infinity) const;
	void dijkstra_priority(TypeOfVer start, TypeOfEdge infinity) const;

private:
	void dfs(int start, bool visited[]) const;

	verNode * clone() const;
	struct EulerNode {
		int data;
		EulerNode * next;
		EulerNode(int ver, EulerNode * n = NULL) {data = ver; next = n;}
	};
	EulerNode * EulerCircuit(int start, EulerNode * & end);

	struct edge
	{
		int beg, end;
		TypeOfEdge w;
		bool operator < (const edge & rp) const {return w < rp.w;}
		bool operator > (const edge & rp) const {return w > rp.w;}
	};

	void printPath(int start, int end, int prev[]) const;
	int * topSortInt() const;

};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[]) {
	graph<TypeOfEdge>::Vers = vSize;
	graph<TypeOfEdge>::Edges = 0;

	verList = new verNode[vSize];
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
	int i;
	edgeNode * p;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p -> next;
			delete p;
		}
	}

	delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::insert(int u, int v, TypeOfEdge w) {
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++graph<TypeOfEdge>::Edges;
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::remove(int u, int v) {
	edgeNode * p = verList[u].head, * q;

	if (p == NULL) return false;

	if (p -> end == v) {
		verList[u].head = p -> next;
		delete p;
		--graph<TypeOfEdge>::Edges;
		return true;
	}
	while (p -> next != NULL && p -> next -> end != v) p = p -> next;
	if (p -> next == NULL) return false;
	q = p -> next;
	p -> next = q -> next;
	delete q;
	--graph<TypeOfEdge>::Edges;
	return true;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(int u, int v) const {
	edgeNode * p = verList[u].head;

	while (p != NULL && p -> end != v) p = p -> next;
	if (p == NULL) return false;
	else return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const {
	bool * visited = new bool[graph<TypeOfEdge>::Vers];
	int i;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	std::cout << "DFS:" << std::endl;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[i] == true) continue;
		dfs(i, visited);
		std::cout << std::endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(TypeOfVer start) const
{
	bool * visited = new bool[graph<TypeOfEdge>::Vers];

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	int startInt;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == start) {startInt = i; break; }

	std::cout << "DFS:" << std::endl;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[ (startInt + i) % graph<TypeOfEdge>::Vers ] == true) continue;
		dfs( (startInt + i) % graph<TypeOfEdge>::Vers, visited);
		std::cout << std::endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const {
	edgeNode * p = verList[start].head;

	std::cout << verList[start].ver << '\t';
	visited[start] = true;

	while (p != NULL) {
		if (visited[p -> end] == false) dfs(p -> end, visited);
		p = p -> next;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const {
	bool visited[graph<TypeOfEdge>::Vers];
	int currentNode;
	linkQueue<int> q;
	edgeNode * p;
	int i;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	std::cout << "BFS:" << std::endl;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[i] == true)
			continue;
		q.enQueue(i);
		while (! q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true) continue;

			std::cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;

			p = verList[currentNode].head;
			while (p != NULL) {
				if (visited[p -> end] == false) q.enQueue(p -> end);
				p = p -> next;
			}
		}
		std::cout << std::endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start) const {
	bool visited[graph<TypeOfEdge>::Vers];
	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	int startInt;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == start) {startInt = i; break; }

	int currentNode;
	linkQueue<int> q;
	edgeNode * p;

	std::cout << "BFS:" << std::endl;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (visited[(i + startInt) % graph<TypeOfEdge>::Vers] == true) continue;
		q.enQueue((i + startInt) % graph<TypeOfEdge>::Vers);
		while (! q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true) continue;

			std::cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;

			p = verList[currentNode].head;
			while (p != NULL) {
				if (visited[p -> end] == false) q.enQueue(p -> end);
				p = p -> next;
			}
		}
		std::cout << std::endl;
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start) {
	int numOfDegree;
	edgeNode * r;

	if (graph<TypeOfEdge>::Edges == 0) {std::cout << "No Euler circuit." << std::endl; return;}
	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		numOfDegree = 0;
		r = verList[i].head;
		while (r != 0) {++numOfDegree; r = r -> next;}
		if (numOfDegree == 0 || numOfDegree % 2 == 1) {std::cout << "No Euler circuit." << std::endl; return;}
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == start) break;
	if (i == graph<TypeOfEdge>::Vers) {std::cout << "Starting vertex does not exist." << std::endl; return;}

	verNode * tmp;
	tmp = clone();

	EulerNode * beg, * end, * p, * q, * tb, * te;
	beg = EulerCircuit(i, end);

	while (true) {
		p = beg;
		while (p -> next != NULL) {
			if (verList[p -> next -> data].head != NULL) break;
			else p = p -> next;
		}
		if (p -> next == NULL) break;
		q = p -> next;
		tb = EulerCircuit(q -> data, te);
		te -> next = q -> next;
		p -> next = tb;
		delete q;
	}

	delete [] verList;
	verList = tmp;

	std::cout << "Euler circuit:" << std::endl;
	while (beg != NULL) {
		std::cout << verList[beg -> data].ver << '\t';
		p = beg;
		beg = beg -> next;
		delete p;
	}
	std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode * adjListGraph<TypeOfVer, TypeOfEdge>::clone() const {
	verNode * tmp = new verNode[graph<TypeOfEdge>::Vers];
	edgeNode * p;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		tmp[i].ver = verList[i].ver;
		p = verList[i].head;
		while (p != NULL) {
			tmp[i].head = new edgeNode(p -> end, p -> weight, tmp[i].head);
			p = p -> next;
		}
	}
	return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::EulerNode * adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode * & end) {
	EulerNode * beg;
	int nextNode;

	beg = end = new EulerNode(start);
	while (verList[start].head != NULL) {
		nextNode = verList[start].head -> end;
		adjListGraph<TypeOfVer, TypeOfEdge>::remove(start, nextNode);
		adjListGraph<TypeOfVer, TypeOfEdge>::remove(nextNode, start);
		start = nextNode;
		end -> next = new EulerNode(start);
		end = end -> next;
	}
	return beg;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const {
	linkQueue<int> q;
	edgeNode * p;
	int current;
	int inDegree[graph<TypeOfEdge>::Vers];

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		inDegree[i] = 0;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[i].head; p != NULL; p = p -> next)
			++inDegree[p -> end];
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (inDegree[i] == 0) q.enQueue(i);

	std::cout << "Topological sort:" << std::endl;
	while (! q.isEmpty()) {
		current = q.deQueue();
		std::cout << verList[current].ver << '\t';
		for (p = verList[current].head; p != NULL; p = p -> next)
			if (--inDegree[p -> end] == 0) q.enQueue(p -> end);
	}
	std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
int * adjListGraph<TypeOfVer, TypeOfEdge>::topSortInt() const {
	linkQueue<int> q;
	edgeNode * p;
	int current;
	int inDegree[graph<TypeOfEdge>::Vers];
	int * topsortint = new int[graph<TypeOfEdge>::Vers];

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		inDegree[i] = 0;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[i].head; p != NULL; p = p -> next)
			++inDegree[p -> end];
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (inDegree[i] == 0) q.enQueue(i);

	i = 0;
	while (! q.isEmpty()) {
		current = q.deQueue();
		topsortint[i++] = current;
		for (p = verList[current].head; p != NULL; p = p -> next)
			if (--inDegree[p -> end] == 0) q.enQueue(p -> end);
	}
	return topsortint;
}

// template <class TypeOfVer, class TypeOfEdge>
// void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const { //Without queue
// 	edgeNode * p;
// 	int current;
// 	int * inDegree = new int[graph<TypeOfEdge>::Vers];

// 	int i;
// 	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
// 		inDegree[i] = 0;
// 	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
// 		for (p = verList[i].head; p != NULL; p = p -> next)
// 			++inDegree[p -> end];
// 	}

// 	std::cout << "Topological sort:" << std::endl;
// 	for (int j = 0; j < graph<TypeOfEdge>::Vers; ) {
// 		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
// 			if (inDegree[i] == 0) {
// 				--inDegree[i];
// 				std::cout << verList[i].ver << '\t';
// 				for (p = verList[i].head; p != NULL; p = p -> next)
// 					--inDegree[p -> end];
// 				++j;
// 			}
// 		}
// 	}
// }

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::haveCircle() const {
	int inDegree[graph<TypeOfEdge>::Vers];
	bool isRemoved[graph<TypeOfEdge>::Vers];
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		isRemoved[i] = false;
	int numOfRemoved = 0;
	edgeNode * p;

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		inDegree[i] = 0;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[i].head; p != NULL; p = p -> next)
			++inDegree[p -> end];
	}

	while (true) {
		if (numOfRemoved == graph<TypeOfEdge>::Vers) return false;

		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
			if (inDegree[i] == 0 && isRemoved[i] == false) break;
		if (i == graph<TypeOfEdge>::Vers) {return true;}

		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
			if (inDegree[i] == 0 && isRemoved[i] == false) {	//remove i
				isRemoved[i] = true;
				numOfRemoved++;
				for (p = verList[i].head; p != NULL; p = p -> next)
					if (isRemoved[p -> end] == false) inDegree[p -> end]--;
			}
		}
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::find(TypeOfVer start, int length) const {
	link_stack<edgeNode *> edgeNodeStack;
	bool isInStack[graph<TypeOfEdge>::Vers];
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		isInStack[i] = false;

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == start) break;

	int lengthOfStack = 1;
	edgeNodeStack.push(verList[i].head);
	isInStack[i] = true;

	while (! edgeNodeStack.isEmpty()) {
		if (lengthOfStack == length) {
			if (edgeNodeStack.top() != NULL) {
				link_stack<edgeNode *> tmpStack;
				for (i = 0; i < length; ++i) 
					tmpStack.push(edgeNodeStack.pop());
				for (i = 0; i < length; ++i) {
					edgeNode * tmp = tmpStack.pop();
					std::cout << verList[tmp -> end].ver << '\t';
					edgeNodeStack.push(tmp);
				}
				std::cout << std::endl;
				edgeNode * tmp = edgeNodeStack.pop();
				isInStack[tmp -> end] = false;
				for (tmp = tmp -> next; tmp != NULL; tmp = tmp -> next) 
					if (isInStack[tmp -> end] == false) {edgeNodeStack.push(tmp); isInStack[tmp -> end] = true; break; }
				if (tmp == NULL) edgeNodeStack.push(NULL);
			}
			else {
				edgeNodeStack.pop();
				lengthOfStack--;
				if (edgeNodeStack.isEmpty()) break;
				edgeNode * tmp = edgeNodeStack.pop();
				isInStack[tmp -> end] = false;
				for (tmp = tmp -> next; tmp != NULL; tmp = tmp -> next)
					if (isInStack[tmp -> end] == false) {edgeNodeStack.push(tmp); isInStack[tmp -> end] = true; break; }
				if (tmp == NULL) edgeNodeStack.push(NULL);
			}
		}
		else {
			if (edgeNodeStack.top() == NULL) {
				edgeNodeStack.pop();
				lengthOfStack--;
				if (edgeNodeStack.isEmpty()) break;
				edgeNode * tmp = edgeNodeStack.pop();
				isInStack[tmp -> end] = false;
				for (tmp = tmp -> next; tmp != NULL; tmp = tmp -> next)
					if (isInStack[tmp -> end] == false) {edgeNodeStack.push(tmp); isInStack[tmp -> end] = true; break; }
				if (tmp == NULL) edgeNodeStack.push(NULL);
			}
			else {
				lengthOfStack++;
				edgeNode * tmp = verList[edgeNodeStack.top() -> end].head;
				for (; tmp != NULL; tmp = tmp -> next) 
					if (isInStack[tmp -> end] == false) {edgeNodeStack.push(tmp); isInStack[tmp -> end] = true; break;}
				if (tmp == NULL) edgeNodeStack.push(NULL);
			}
		}
	}
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::pathBetween(TypeOfVer start, TypeOfVer end) const {
	bool visited[graph<TypeOfEdge>::Vers];
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		visited[i] = false;

	int startInt, endInt;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == start) {startInt = i; break;}
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		if (verList[i].ver == end) {endInt = i; break;}

	int currentNode;
	linkQueue<int> q;
	edgeNode * p;

	q.enQueue(startInt);
	while (! q.isEmpty()) {
		currentNode = q.deQueue();
		if (visited[currentNode] == true) continue;

		visited[currentNode] = true;

		p = verList[currentNode].head;
		while (p != NULL) {
			if (p -> end == endInt) return true;
			if (visited[p -> end] == false) q.enQueue(p -> end);
			p = p -> next;
		}
	}

	return false;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerWalk() {
	int numOfDegree[graph<TypeOfEdge>::Vers], numberOfOdd = 0;
	edgeNode * r;

	if (graph<TypeOfEdge>::Edges == 0) {std::cout << "No Euler walk." << std::endl; return;}

	int i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		numOfDegree[i] = 0;
		r = verList[i].head;
		while (r != NULL) {++numOfDegree[i]; r = r -> next;}
		if (numOfDegree[i] % 2 == 1) numberOfOdd++;
		if (numOfDegree[i] == 0 ) {std::cout << "No Euler walk." << std::endl; return;}
	}
	if (numberOfOdd != 0 && numberOfOdd != 2) {std::cout << "No Euler walk." << std::endl; return;}

	int startInt = 0;
	if (numberOfOdd == 2) {
		for (i = 0; i < graph<TypeOfEdge>::Vers; ++i)
			if (numOfDegree[i] % 2 == 1) {startInt = i; break;}
	}

	verNode * tmp;
	tmp = clone();

	EulerNode * beg, * end, * p, * q, * tb, * te;
	beg = EulerCircuit(startInt, end);

	while (true) {
		p = beg;
		while (p -> next != NULL) {
			if (verList[p -> next -> data].head != NULL) break;
			else p = p -> next;
		}
		if (p -> next == NULL) break;
		q = p -> next;
		tb = EulerCircuit(q -> data, te);
		te -> next = q -> next;
		p -> next = tb;
		delete q;
	}

	delete [] verList;
	verList = tmp;

	std::cout << "Euler walk:" << std::endl;
	while (beg != NULL) {
		std::cout << verList[beg -> data].ver << '\t';
		p = beg;
		beg = beg -> next;
		delete p;
	}
	std::cout << std::endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const {
	int edgesAccepted = 0, u, v;
	edgeNode * p;
	edge e;
	DisjointSet ds(graph<TypeOfEdge>::Vers);
	priorityQueue<edge> pq;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[i].head; p != NULL; p = p -> next) {
			if (i < p -> end) {
				e.beg = i;
				e.end = p -> end;
				e.w = p -> weight;
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
			std::cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
		}
	}
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const {
	bool * flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge * lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * startNode = new int[graph<TypeOfEdge>::Vers];

	edgeNode * p;
	TypeOfEdge min;
	int start, i, j;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[i] = false;
		lowCost[i] = noEdge;
	}

	start = 0;
	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[start].head; p != NULL; p = p -> next) {
			if (! flag[p -> end] && lowCost[p -> end] > p -> weight) {
				lowCost[p -> end] = p -> weight;
				startNode[p -> end] = start;
			}
		}
		flag[start] = true;
		min = noEdge;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j)
			if (lowCost[j] < min) {min = lowCost[j]; start = j;}
		std::cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
		lowCost[start] = noEdge;
	}
	delete [] flag;
	delete [] startNode;
	delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfVer startver, TypeOfEdge noEdge) const {
	bool * flag = new bool[graph<TypeOfEdge>::Vers];
	TypeOfEdge * lowCost = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * startNode = new int[graph<TypeOfEdge>::Vers];

	edgeNode * p;
	TypeOfEdge min;
	int start, i, j;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		flag[i] = false;
		lowCost[i] = noEdge;
	}

	int startInt;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (verList[i].ver == startver) {startInt = i; break;}
	}
	start = startInt;
	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		for (p = verList[start].head; p != NULL; p = p -> next) {
			if (! flag[p -> end] && lowCost[p -> end] > p -> weight) {
				lowCost[p -> end] = p -> weight;
				startNode[p -> end] = start;
			}
		}
		flag[start] = true;
		min = noEdge;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j)
			if (lowCost[j] < min) {min = lowCost[j]; start = j;}
		std::cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
		lowCost[start] = noEdge;
	}
	delete [] flag;
	delete [] startNode;
	delete [] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const {
	linkQueue<int> q;
	TypeOfEdge * distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * prev = new int[graph<TypeOfEdge>::Vers];
	int u, startInt;
	edgeNode * p;

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i)
		distance[i] = noEdge;

	for (startInt = 0; startInt < graph<TypeOfEdge>::Vers; ++startInt) {
		if (verList[startInt].ver == start) break;
	}
	if (startInt == graph<TypeOfEdge>::Vers)
	{
		std::cout << "Starting vertex does not exist" << std::endl;
		delete [] distance;
		delete [] prev;
		return;
	}

	distance[startInt] = 0;
	prev[startInt] = startInt;
	q.enQueue(startInt);

	while (! q.isEmpty()) {
		u = q.deQueue();
		for (p = verList[u].head; p != NULL; p = p -> next)
		{
			if (distance[p -> end] == noEdge)
			{
				distance[p -> end] = distance[u] + 1;
				prev[p -> end] = u;
				q.enQueue(p -> end);
			}
		}
	}

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		std::cout << "The path from " << start << " to " << verList[i].ver << " is:" << std::endl;
		printPath(startInt, i, prev);
		std::cout << std::endl;
	}
	delete [] distance;
	delete [] prev;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(int start, int end, int prev[]) const {
	if (start == end) {std::cout << verList[start].ver; return;}

	printPath(start, prev[end], prev);
	std::cout << " - " << verList[end].ver;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(TypeOfVer start, TypeOfEdge noEdge) const {
	TypeOfEdge * distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * prev = new int[graph<TypeOfEdge>::Vers];
	bool * known = new bool[graph<TypeOfEdge>::Vers];

	int u, startInt, i, j;
	edgeNode * p;
	TypeOfEdge min;

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {		//initialize
		known[i] = false;
		distance[i] = noEdge;
	}

	for (startInt = 0; startInt < graph<TypeOfEdge>::Vers; ++startInt) {		//find the starting vertex startInt
		if (verList[startInt].ver == start) break;
	}

	if (startInt == graph<TypeOfEdge>::Vers) {
		std::cout << "Starting vertex does not exits." << std::endl; 
		delete [] distance;
		delete [] prev;
		delete [] known;
		return; 
	}

	distance[startInt] = 0;
	prev[startInt] = startInt;

	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		min = noEdge;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			if (! known[j] && distance[j] < min) {min = distance[j]; u = j;}
		}
		known[u] = true;

		for (p = verList[u].head; p != NULL; p = p -> next) {
			if (! known[p -> end] && distance[p -> end] > min + p -> weight) {distance[p -> end] = min + p -> weight; prev[p -> end] = u; }
		}
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		std::cout << "The path from " << start << " to " << verList[i].ver << " is:" << std::endl;
		printPath(startInt, i, prev);
		std::cout << "\tLength is:" << distance[i] << std::endl;
	}

	delete [] known;
	delete [] prev;
	delete [] distance;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::negativeWeightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const {
	linkQueue<int> que;

	int startInt;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (verList[i].ver == start) {startInt = i; break; }
	}

	edgeNode * p;
	int currentNode;

	int * distance = new int[graph<TypeOfEdge>::Vers];
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		distance[i] = noEdge;
	}

	distance[startInt] = 0;
	que.enQueue(startInt);
	while (! que.isEmpty()) {
		currentNode = que.deQueue();
		for (p = verList[currentNode].head; p != NULL; p = p -> next) {
			if (distance[currentNode] + p -> weight < distance[p -> end]) {
				distance[p -> end] = distance[currentNode] + p -> weight;
				que.enQueue(p -> end);
			}
		}
	}

	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		std::cout << "The length from " << start << " to " << verList[i].ver << " is " << distance[i] << std::endl;
	}

	delete [] distance;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::noCircle(TypeOfVer start, TypeOfEdge infinity) const {
	int * topSequence = topSortInt();
	linkQueue<int> que;
	for (int i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		que.enQueue(topSequence[i]);
	}
	delete [] topSequence;
	
	int startInt = 0, i;
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {		//find the start int;
		if (verList[i].ver == start) {startInt = i; break;}
	}

	if (i == graph<TypeOfEdge>::Vers) {std::cout << "Starting vertex does not exist." << std::endl; return; }

	TypeOfEdge * distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];	//the distance of every path
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		distance[i] = infinity;
	}
	int * prev = new int[graph<TypeOfEdge>::Vers];		//the previous vertex of every end vertex of the path
	bool * known = new bool[graph<TypeOfEdge>::Vers];	//the vertex has been visited or not
	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		known[i] = false;
	}

	while (que.getHead() != startInt) que.deQueue();
	distance[startInt] = 0;
	prev[startInt] = startInt;

	int currentNode;
	edgeNode * p;
	while (! que.isEmpty()) {
		currentNode = que.deQueue();
		if (distance[currentNode] == infinity) prev[currentNode] = currentNode;
		else known[currentNode] = true;
		for (p = verList[currentNode].head; p != NULL; p = p -> next) {
			if (distance[currentNode] + p -> weight < distance[p -> end]) {
				distance[p -> end] = distance[currentNode] + p -> weight;
				prev[p -> end] = currentNode;
			}
		}
	}
	// for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
	// 	if (known[i] == true) {
	// 		std::cout << verList[i].ver << '\t' << distance[i] << '\t' << verList[prev[i]].ver << std::endl;
	// 	}
	// }

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		if (known[i] == true) {
			std::cout << "The path from " << start << " to " << verList[i].ver << " is:" << std::endl;
			printPath(startInt, i, prev);
			std::cout << "\tLength is:" << distance[i] << std::endl;
		}
	}

	delete [] distance;
	delete [] prev;
	delete [] known;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra_shortest(TypeOfVer start, TypeOfEdge infinity) const {
	int u, startInt, i, j;

	for (startInt = 0; startInt < graph<TypeOfEdge>::Vers; ++startInt) {		//find the starting vertex startInt
		if (verList[startInt].ver == start) break;
	}

	if (startInt == graph<TypeOfEdge>::Vers) {std::cout << "Starting vertex does not exits." << std::endl; return; }

	TypeOfEdge * distance = new TypeOfEdge[graph<TypeOfEdge>::Vers];
	int * prev = new int[graph<TypeOfEdge>::Vers];
	bool * known = new bool[graph<TypeOfEdge>::Vers];
	int * lengthOfPath = new int[graph<TypeOfEdge>::Vers];

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {		//initialize
		known[i] = false;
		distance[i] = infinity;
		lengthOfPath[i] = 2147483647;
	}

	distance[startInt] = 0;
	prev[startInt] = startInt;
	lengthOfPath[startInt] = 0;

	edgeNode * p;
	TypeOfEdge min;
	for (i = 1; i < graph<TypeOfEdge>::Vers; ++i) {
		min = infinity;
		for (j = 0; j < graph<TypeOfEdge>::Vers; ++j) {
			if (known[j] == false && distance[j] < min) {min = distance[j]; u = j;}
		}
		known[u] = true;

		for (p = verList[u].head; p != NULL; p = p -> next) {
			if (known[p -> end] == false ) {
				if (distance[p -> end] > min + p -> weight) {
					distance[p -> end] = min + p -> weight;
					prev[p -> end] = u;
					lengthOfPath[p -> end] = lengthOfPath[u] + 1;
				}
				if (distance[p -> end] == min + p -> weight && lengthOfPath[p -> end] > lengthOfPath[u] + 1) {
					lengthOfPath[p -> end] = lengthOfPath[u] + 1;
					prev[p -> end] = u;
				}
			}
		}
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		std::cout << "The path from " << start << " to " << verList[i].ver << " is:" << std::endl;
		printPath(startInt, i, prev);
		std::cout << "\tLength is:" << distance[i] << std::endl;
	}

	delete [] known;
	delete [] prev;
	delete [] distance;
	delete [] lengthOfPath;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra_priority(TypeOfVer start, TypeOfEdge infinity) const {
	int startInt, i;

	for (startInt = 0; startInt < graph<TypeOfEdge>::Vers; ++startInt) {		//find the starting vertex startInt
		if (verList[startInt].ver == start) break;
	}

	if (startInt == graph<TypeOfEdge>::Vers) {std::cout << "Starting vertex does not exits." << std::endl; return; }

	struct dijkstra_vertex
	{
		int data;
		TypeOfEdge distance;
		bool operator < (const dijkstra_vertex & t) const {return distance > t.distance;}
		bool operator > (const dijkstra_vertex & t) const {return distance < t.distance;}
	};

	dijkstra_vertex * V = new dijkstra_vertex[graph<TypeOfEdge>::Vers];
	int * prev = new int[graph<TypeOfEdge>::Vers];
	bool * known = new bool[graph<TypeOfEdge>::Vers];
	int * lengthOfPath = new int[graph<TypeOfEdge>::Vers];

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {		//initialize
		known[i] = false;
		V[i].data = i;
		V[i].distance = infinity;
		lengthOfPath[i] = 2147483647;
	}

	V[startInt].distance = 0;
	prev[startInt] = startInt;
	lengthOfPath[startInt] = 0;

	edgeNode * p;
	int u;
	priorityQueue<dijkstra_vertex> que;
	dijkstra_vertex currentNode;
	i = 0;
	que.enQueue(V[startInt]);
	while (i != graph<TypeOfEdge>::Vers && ! que.isEmpty()) {
		if (i == 0) {u = startInt;}
		else {
			currentNode = que.deQueue();
			u = currentNode.data;
			if (known[currentNode.data] == true) continue;
		}
		known[u] = true;
		i++;

		for (p = verList[u].head; p != NULL; p = p -> next) {
			if (known[p -> end] == false ) {
				if (V[p -> end].distance > V[u].distance + p -> weight) {
					V[p -> end].distance = V[u].distance + p -> weight;
					prev[p -> end] = u;
					lengthOfPath[p -> end] = lengthOfPath[u] + 1;
					que.enQueue(V[p -> end]);
				}
				if (V[p -> end].distance == V[u].distance + p -> weight && lengthOfPath[p -> end] > lengthOfPath[u] + 1) {
					lengthOfPath[p -> end] = lengthOfPath[u] + 1;
					prev[p -> end] = u;
				}
			}
		}
	}

	for (i = 0; i < graph<TypeOfEdge>::Vers; ++i) {
		std::cout << "The path from " << start << " to " << verList[i].ver << " is";
		if (V[i].distance == infinity) {
			std::cout << " not existent." << std::endl;
		}
		else {
			std::cout << ":" << std::endl;
			printPath(startInt, i, prev);
			std::cout << "\tLength is:" << V[i].distance << std::endl;
		}
	}

	delete [] known;
	delete [] prev;
	delete [] lengthOfPath;
	delete [] V;
}


#endif /* adjListGraph_hpp */
