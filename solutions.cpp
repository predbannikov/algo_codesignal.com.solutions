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
	return check;
}

bool containsCloseNums(std::vector<int> nums, int k) {
	if (nums.empty() || k == 0)
		return false;

	std::unordered_map<int, int> map;
	for (size_t i = 0; i < nums.size() && i <= k; i++) {
		if (map.find(nums[i]) != map.end())
			return true;
		else
			map[nums[i]];
	}
	for (size_t i = 0; i < nums.size(); i++) {

		int cur = nums[i];
		map.erase(cur);


		if (map.find(cur) != map.end())
			return true;
		if (i + k + 1 < nums.size())
			if (map.find(nums[i + k + 1]) != map.end())
				return true;
			else
				map[nums[i + k + 1]];
	}
	return false;
}

/*You have a collection of coins, and you know the values of the coins and the quantity of each type of coin in it. You want to know how many distinct sums you can make from non-empty groupings of these coins.

Example

For coins = [10, 50, 100] and quantity = [1, 2, 1], the output should be
possibleSums(coins, quantity) = 9.

Here are all the possible sums:

50 = 50;
10 + 50 = 60;
50 + 100 = 150;
10 + 50 + 100 = 160;
50 + 50 = 100;
10 + 50 + 50 = 110;
50 + 50 + 100 = 200;
10 + 50 + 50 + 100 = 210;
10 = 10;
100 = 100;
10 + 100 = 110.
As you can see, there are 9 distinct sums that can be created from non-empty groupings of your coins.*/
std::unordered_set<int>* possibleSumsSup(std::multiset<int> mset) {
	std::unordered_set<int>* setResults = new std::unordered_set<int>;
	for (auto it = mset.begin(); it != mset.end(); it++) {
		std::multiset<int> mset_tmp(mset);
		auto itTodel = mset_tmp.find(*it);
		mset_tmp.erase(itTodel);
		if (!mset_tmp.empty())
			setResults->merge(*possibleSumsSup(mset_tmp));
	}
	return setResults;
}
// pIn - входной массив
// N - размер входного массива
// K - количество элементов в размещении

void PermutationWithRepetition(const char* pIn, int N, int K)
{
	char* pOut = new char[K + 1]; // строка из K символов плюс 1 символ для терминального 0
	pOut[K] = 0;                  // помещаем 0 в конец строки
	K--;
	int* stack = new int[K * 2],  // стек псевдорекурсии, глубина рекурсии K - 1
		* pTop = stack,            // вершина стека
		k = 0,                    // переменные цикла
		n = 0,
		j = 0;
	for (;;)                      // цикл псевдорекурсии
	{
		while (n < N)
		{
			pOut[k] = pIn[n++];
			if (k == K)
				printf("%02d. %s\n", ++j, pOut);
			else
			{
				if (n < N)
				{
					*pTop++ = k;          // сохраняем k и n в стеке
					*pTop++ = n;
				}
				k++;                    // псевдорекурсивный вызов
				n = 0;
			}
		}
		if (pTop == stack)          // стек пуст, конец цикла
			break;

		n = *(--pTop);              // выталкиваем k и n из стека
		k = *(--pTop);
	}
	delete[] pOut;
	delete[] stack;
}

void algoNarajanj(std::vector<int>& v) {
	std::vector<int>::iterator it = v.end();
	std::vector<int>::iterator i = v.end();
	while (true) {
		i--;
		if (it == v.end() && i != v.end()-1 && *i < *(i + 1)) {
			it = i;
			i = v.end()-1;
		}
		if (it != v.end() && *it < *i) {
			std::swap(*it, *i);
			it++;
			std::reverse(it, v.end());
			return;
		}
		if (i == v.begin())
			return;
	}
	return;
}

int fact(int n) {
	if (n < 1)
		return 1;
	else
		return fact(n - 1) * n;
}
int possibleSums(std::vector<int> coins, std::vector<int> quantity) {
	std::multiset<int> mset;
	for (size_t i = 0; i < coins.size(); i++) {
		for (size_t j = 0; j < quantity[i]; j++) {
			mset.insert(coins[i]);
		}
	}
	for (int i = 0; i < fact(coins.size()); i++) {
		std::copy(coins.begin(), coins.end(), std::ostream_iterator<int>(std::cout << std::endl, "\t"));
		algoNarajanj(coins);

	}
	std::vector<int> coins2{ 10, 50, 50, 100 };

	do {
		//for (int i = 0; i < n; ++i) {
		//	if (v[i]) {
		//		std::cout << (i + 1) << " ";
		//	}
		//}
		std::copy(coins2.begin(), coins2.end(), std::ostream_iterator<int>(std::cout << std::endl, " "));
	} while (std::next_permutation(coins2.begin(), coins2.end()));

	PermutationWithRepetition("abcd", 4, 4);

	std::multiset<int>::iterator it = mset.begin();




	std::unordered_set<int>* setResults = new std::unordered_set<int>;
	setResults->merge(*possibleSumsSup(mset));
	std::cout << std::endl;
	return 0;
}


int main()
{
	//std::cout << possibleSums({ 10, 50, 100 }, { 1, 2, 1 });


	//std::cout << containsCloseNums({ 99, 99 }, 2);
	//	std::cout << areFollowingPatterns({
	//	"cat",
	// "dog",
	// "dog"
	//		},
	//		{
	//"a",
	// "b",
	// "b"
	//		}) << std::endl;


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

		testArcade();
		//linkedlistImpl();
	return 0;
}

