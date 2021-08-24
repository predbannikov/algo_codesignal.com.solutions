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

bool checkCycle(std::map<int, std::vector<int>>& map, std::set<int>& set, int val, int key) {

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

size_t pow(size_t base, int exponent) {
	int n = exponent;
	int stackLvl = 1;
	bool check = true;
	while (stackLvl) {
		n = n / 2;
		if (check && n > 1)
			stackLvl++;
		else {
			if (check) {
				check = false;
			}
			base *= base;
			stackLvl--;
		}
	}
	return base;
}

size_t pow2(int base, int exponent) {
	size_t res = base;
	while (exponent > 1) {
		res *= base;
		exponent--;
	}
	return res;
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

void traversalGraph(std::set<int>& visit, std::vector<std::pair<int, int>>& e) {

}

void checkConnection(std::vector<std::vector<int>>& graph, std::set<int>& visit, int v) {
	for (size_t i = 0; i < graph[v].size(); i++) {
		if (graph[v][i]) {
			if (visit.find(i) == visit.end()) {
				visit.insert(i);
				checkConnection(graph, visit, i);
			}
		}
	}
}

int singlePointOfFailure(std::vector<std::vector<int>> connections) {
	size_t max = 0;
	for (size_t i = 0; i < connections.size(); i++) {
		for (size_t j = i; j < connections[i].size(); j++) {
			if (connections[i][j] == 1) {
				connections[i][j] = 0;
				connections[j][i] = 0;
				std::set<int> set;
				std::cout << i << " " << j << std::endl;
				if (i == 0 && j == 3)
					std::cout << "stop";
				checkConnection(connections, set, 0);
				std::cout << set.size() << std::endl;
				if (connections.size() != set.size())
					max++;
				connections[i][j] = 1;
				connections[j][i] = 1;

			}
		}
	}


	std::cout << "max=" << max << std::endl;
	return 0;
}

/*You are the head zookeeper at a large zoo. You've been contacted by schools in the area that want to bring in classes so that students can feed the animals. The animals can only be fed once a day, so no two classes can come on the same day if they want to feed the same animals.

You have a list classes, such that classes[i] is a list of animals that the ith class wants to feed. Classes i and j cannot come on the same day if an animal in classes[i] also appears in classes[j] (for i ≠ j). Your job is to determine the minimum number of days you would need to have all the classes come to feed the animals if they can all come within 5 days. If it isn't possible for all the classes to come within 5 days, return -1 instead.

Example

For classes = [["Tiger", "Lima", "Frog"], ["Tiger", "Zebra","Lion"], ["Tiger", "Rabbit"], ["Emu", "Zebra", "Rabbit"]], the output should be
feedingTime(classes) = 3.
Classes 0, 1, and 2 all want to feed the Tiger, so they have to come on different days. Class 3 cannot come on the same day as class 1 (because of the Zebra) or class 2 (because of the Rabbit), but they can come on the same day as class 0. Therefore it only takes 3 days for all the classes to visit the zoo.

For classes = [["Tiger", "Lima", "Frog"], ["Tiger", "Zebra", "Lion"], ["Tiger", "Rabbit"], ["Lima", "Zebra", "Rabbit"]], the output should be
feedingTime(classes) = 4.
Each class has to come on a separate day, because every pair of classes has at least one animal in common.

For classes = [["Lion", "Emu"], ["Giraffe", "Peacock"], ["Lima"], ["Tiger", "Cheetah", "Slugs"], ["Snakes", "Sealion"]], the output should be
feedingTime(classes) = 1.
No classes have animals in common, so they can all come on the same day.*/
int feedingTime(std::vector<std::vector<std::string>> classes) {

}

void testGraphs() {



	const int size = 100000;
	std::cout << sizeof size << std::endl;
	int val = 2;
	int N = 22;
	std::cout << val << "^" << N << " count tests=" << size << std::endl;
	long mark = 0;
	long dmark = 0;
	std::vector<long> vec(size);
	size_t res = 0;
	std::cout << "pow=";
	for (size_t i = 0; i < size; i++) {
		mark = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		res = pow(val, N);
		dmark = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - mark;
		vec[i] = dmark;
	}
	int avr = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << " dTimeAvr=" << avr << " microsec" << std::endl;
	std::cout << "pow2=";
	for (size_t i = 0; i < size; i++) {
		mark = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		res = pow2(val, N);
		dmark = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - mark;
		vec[i] = dmark;
	}
	avr = std::accumulate(vec.begin(), vec.end(), 0);
	std::cout << " dTimeAvr=" << avr << " microsec" << std::endl;



	//std::vector<std::vector<int>> v1 = {
	//	{0, 1, 1, 1, 0, 0} ,
	//	{1, 0, 1, 0, 0, 0},
	//	{1, 1, 0, 0, 0, 0},
	//	{1, 0, 0, 0, 1, 1},
	//	{0, 0, 0, 1, 0, 0},
	//	{0, 0, 0, 1, 0, 0},
	//};

	std::vector<std::vector<int>> v1 = {
		{0, 1},
		{1, 0}
	};

	std::cout << singlePointOfFailure(v1);

	//std::vector<std::vector<int>> v1 = { {1,2,3} , {2,3}, {3}, {} };
	//std::cout << std::boolalpha << hasDeadlock(v1);
}