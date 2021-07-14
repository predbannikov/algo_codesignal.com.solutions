// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>

int firstDuplicate(std::vector<int> a) {
	std::unordered_map<int, int> map;
	for (auto x : a) {
		if (map.find(x) != map.end())
			return x;
		else 
			map.insert( { x, 0 });
	}
}

int main()
{

	return 0;
}
