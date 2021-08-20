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


void testGraphs() {


	std::vector<std::vector<int>> v1 = { {1,2,3} , {2,3}, {3}, {} };
	std::cout << std::boolalpha << hasDeadlock(v1);

}