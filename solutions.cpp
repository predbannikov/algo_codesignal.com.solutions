// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include "arrays.h"
#include "linkedlist.h"
#include "arcade.h"

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

bool areFollowingPatterns(std::vector<std::string> strings, std::vector<std::string> patterns) {
	bool check = true;
	std::unordered_map<std::string, std::string> mapStr, mapPat;
	std::string lastStr = strings[0];
	std::string lastPat = patterns[0];
	mapStr[lastStr] = lastPat;
	mapPat[lastPat] = lastStr;

	for (size_t i = 1; i < strings.size(); i++) {
		bool state1 = lastStr == strings[i];
		bool state2 = lastPat == patterns[i];
		bool state3 = true;
		if (mapStr.find(strings[i]) != mapStr.end())
			state3 = mapStr.find(strings[i])->second == patterns[i];
		bool state4 = true;
		if (mapPat.find(patterns[i]) != mapPat.end())
			state4 = mapPat.find(patterns[i])->second == strings[i];

		if (state1 != state2)
			check = false;
		if (state3 != state4)
			check = false;
		lastStr = strings[i];
		lastPat = patterns[i];
		mapStr[lastStr] = lastPat;
		mapPat[lastPat] = lastStr;
	}
	//bool state3 = true;
	//if (mapStr.find(lastStr) != mapStr.end())
	//	state3 = mapStr.find(lastStr)->second == lastPat;
	//bool state4 = true;
	//if (mapPat.find(lastPat) != mapPat.end())
	//	state4 = mapPat.find(lastPat)->second == lastStr;
	//if (state3 != state4)
	//	check = false;

	return check;
}


int main()
{
	std::cout << areFollowingPatterns({
	"cat",
 "dog",
 "dog"
		},
		{
"a",
 "b",
 "b"
		}) << std::endl;


	//std::vector<std::vector<std::string>> ret = groupingDishes({
	//	{"Salad", "Tomato", "Cucumber", "Salad", "Sauce"} ,
	//		{"Pizza", "Tomato", "Sausage", "Sauce", "Dough"},
	//		{"Quesadilla", "Chicken", "Cheese", "Sauce"},
	//		{"Sandwich", "Salad", "Bread", "Tomato", "Cheese"} 
	//	});
	//for (size_t i = 0; i < ret.size(); i++) {
	//	for (size_t j = 0; j < ret[i].size(); j++) {
	//		std::cout << ret[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//testArcade();
	//linkedlistImpl();
	return 0;
}

