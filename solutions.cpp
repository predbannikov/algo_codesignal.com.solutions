// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include "arrays.h"
#include "linkedlist.h"


std::vector<std::vector<std::string>> groupingDishes(std::vector<std::vector<std::string>> dishes) {
	std::vector<std::vector<std::string>> tmp;
	std::map<std::string, std::multimap<std::string, int>> map;
	for (size_t i = 0; i < dishes.size(); i++) {
		for (size_t j = 1; j < dishes[i].size(); j++) {
			map[dishes[i][j]].insert({ dishes[i][0], 0 });
		}
		std::cout << std::endl;
	}
	for (auto it = map.begin(); it != map.end(); it++) {
		if (it->second.size() > 1) {
			tmp.push_back(std::vector<std::string>(1, it->first));
			for (auto its = it->second.begin(); its != it->second.end(); its++)
				tmp.back().push_back(its->first);
		}
	}
	return tmp;
}

int main()
{
	std::vector<std::vector<std::string>> ret = groupingDishes({
		{"Salad", "Tomato", "Cucumber", "Salad", "Sauce"} ,
			{"Pizza", "Tomato", "Sausage", "Sauce", "Dough"},
			{"Quesadilla", "Chicken", "Cheese", "Sauce"},
			{"Sandwich", "Salad", "Bread", "Tomato", "Cheese"} 
		});
	for (size_t i = 0; i < ret.size(); i++) {
		for (size_t j = 0; j < ret[i].size(); j++) {
			std::cout << ret[i][j] << " ";
		}
		std::cout << std::endl;
	}



	linkedlistImpl();
	return 0;
}

