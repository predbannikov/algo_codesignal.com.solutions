#pragma once
#include "solutions.h"

/*In a multithreaded environment, it's possible that different processes will need to use the same resource. A wait-for graph represents the different processes as nodes in a directed graph, where an edge from node i to node j means that the node j is using a resource that node i needs to use (and cannot use until node j releases it).

We are interested in whether or not this digraph has any cycles in it. If it does, it is possible for the system to get into a state where no process can complete.

We will represent the processes by integers 0, ...., n - 1. We represent the edges using a two-dimensional list connections. If j is in the list connections{i}, then there is a directed edge from process i to process j.

Write a function that returns True if connections describes a graph with a directed cycle, or False otherwise.

Example

For connections = {{1}, {2}, {3, 4}, {4}, {0}}, the output should be
hasDeadlock(connections) = true.


This graph contains a cycle.

For connections = {{1, 2, 3}, {2, 3}, {3}, {}}, the output should be
hasDeadlock(connections) = false.


This graph doesn't contain a directed cycle (there are two paths from 0 to 3, but no paths from 3 back to 0).*/

//void dfs(std::set<int>& set, std::map<int, std::vector<int>>::iterator& it_m, std::map<int, std::vector<int>>::iterator& it_mEnd, std::vector<int>::iterator& it_v, std::vector<int>::iterator& it_vEnd) {
//	set.insert()
//}

bool checkCycle(std::map<int, std::vector<int>>& map, std::set<int> &set, int val, int key) {

	for (size_t i = 0; i < map[val].size(); i++) {
		int value = map[val][i];
		if (set.find(value) != set.end())
			return true;
		set.insert(value);
		if (checkCycle(map, set, value, key))
			return true;
		else 
			set.erase(value);
		

	}
	return false;
}

bool hasDeadlock(std::vector<std::vector<int>> connections) {
	std::map<int, std::vector<int>> map;
	for (size_t i = 0; i < connections.size(); i++)
		map[i] = connections[i];

	for (auto it_m = map.begin(); it_m != map.end(); it_m++) {
		std::set<int> set({ it_m->first });
		if (checkCycle(map, set, it_m->first, it_m->first))
			return true;
	}
	return false;
}

/*Note: Try to solve this task in O(n2) time, where n is a number of vertices, since this is what you'll be asked to do during an interview.

Sue is a network administrator who consults for companies that have massive Local Area Networks (LANs). The computers are connected together with network cables, and Sue has been brought in to evaluate the company’s network. The networks are huge, and she wants to ensure that no single network cable failure can disconnect the network. Any cable that fails that leaves the network in two or more disconnected pieces is called a single point of failure.

She labels the different network devices from 0 to n - 1. She keeps an n × n matrix connections, where connections[i][j] = 1 if there is a network cable directly connecting devices i and j, and 0 otherwise. Write a function that takes the matrix of connections, and returns the number of cables that are a single point of failure.

Example

For connections = [[0, 1], [1, 0]], the output should be
singlePointOfFailure(connections) = 1.
A failure of the cable that connects devices 0 and 1 would leave the network disconnected.



For connections = [[0, 1, 1], [1, 0, 1], [1, 1, 0]], the output should be
singlePointOfFailure(connections) = 0.
No failure of a single network cable would result in the network being disconnected.



For connections = [[0, 1, 1, 1, 0, 0], [1, 0, 1, 0, 0, 0], [1, 1, 0, 0, 0, 0], [1, 0, 0, 0, 1, 1], [0, 0, 0, 1, 0, 0], [0, 0, 0, 1, 0, 0]], the output should be
singlePointOfFailure(connections) = 3.
The three cables that are single points of failure are connected with device 3:



For connections = [[0, 1, 1, 1, 1], [1, 0, 0, 0, 0], [1, 0, 0, 0, 0], [1, 0, 0, 0, 0], [1, 0, 0, 0, 0]], the output should be
singlePointOfFailure(connections) = 4.
In this topology, every cable is a single point of failure:

*/

int singlePointOfFailure(std::vector<std::vector<int>> connections) {

	for (size_t i = 0; i < connections.size(); i++) {
		for (size_t j = 0; j < connections[i].size(); j++) {
			std::cout << connections[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}

int pow(int v, int n) {
	if (n == 1)
		return 2;
	return pow(v, n/2) * pow(v, n/2);
}

//int pow2(int v, int n) {
//
//}

void testGraphs() {
	std::cout << pow(2, 7);
	std::vector<std::vector<int>> v1 = {
		{0, 1, 1, 1, 0, 0} ,
		{1, 0, 1, 0, 0, 0},
		{1, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 0},
	};
	std::cout << singlePointOfFailure(v1);

	//std::vector<std::vector<int>> v1 = { {1,2,3} , {2,3}, {3}, {} };
	//std::cout << std::boolalpha << hasDeadlock(v1);
}