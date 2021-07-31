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

void bt(std::vector <int>& c, std::vector <int>& q, std::unordered_set <int>& sums, int idx, int sum) {
	static int lvl = 0;
	lvl++;
	//std::cout << "in lvl(" << lvl  << ")" << std::endl;
	if (idx == c.size()) {			// Если дошли максимального количества, то на этом уровне стека 
		if (sum) sums.insert(sum);		// добавляем в сет сумму и выходим из рекурсии
		std::cout << "lvl=" << lvl << " sum=" << sum << std::endl;
		lvl--;
		//std::cout << "out lvl(" << lvl << ")" << std::endl;
		return;
	}
	for (int i = 0; i <= q[idx]; ++i) {					// Запускаем некоторое количество раз функцию на этом уровне стека, i - определяет сколько раз в наборе будет встречаться элемент
		std::cout << c[idx] * i << "\t" << "lvl=" << lvl << " bt(c,q,s," << idx << "+1" << "," << sum << "+c[" << idx << "]*" << i << ")" << std::endl;
		bt(c, q, sums, idx + 1, sum + c[idx] * i);		// С каждым новым запуском прибавляем idx + 1 ( что в один момент даст размер массива монет)
	}
	lvl--;
	//std::cout << "out lvl(" << lvl << std::endl;
}

int possibleSumsNotMyImpl(std::vector<int> coins, std::vector<int> quantity) {
	std::unordered_set <int> sums;
	bt(coins, quantity, sums, 0, 0);
	return sums.size();
}

// pIn - входной массив
// N - размер входного массива
// K - количество элементов в размещении

void PermutationWithRepetition(const int* pIn, int N, int K)
{
	//std::unordered_set<std::unordered_set<int>> set;
	int* pOut = new int[K + 1]; // строка из K символов плюс 1 символ для терминального 0
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
			if (k == K) {
				printf("%02d. ", ++j);
				std::unordered_set<int> tmp_set;
				for (int i = 0; i < N; i++) {
					printf("%d ", *(pOut + i));
					tmp_set.insert(*(pOut + i));
				}
				//set.insert(tmp_set);
				printf("\n");
			}
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

bool algoNarajanj(std::vector<int>& v) {
	std::vector<int>::iterator it = v.end();
	std::vector<int>::iterator i = v.end();
	while (true) {
		i--;
		if (it == v.end() && i != v.end() - 1 && *i < *(i + 1)) {
			it = i;
			i = v.end() - 1;
		}
		if (it != v.end() && *it < *i) {
			std::swap(*it, *i);
			it++;
			std::reverse(it, v.end());
			return false;
		}
		if (i == v.begin())
			return true;
	}
	return false;
}

uint64_t fact(uint64_t n) {
	if (n < 1)
		return 1;
	else
		return fact(n - 1) * n;
}

bool NextSet(std::vector<int>& a, int n, int m)
{
	int k = m;
	for (int i = k - 1; i >= 0; --i)
		if (a[i] < n - k + i + 1)
		{
			++a[i];
			for (int j = i + 1; j < k; ++j)
				a[j] = a[j - 1] + 1;
			return true;
		}
	return false;
}

void genSochWithRepeat(std::vector<int>& c, std::unordered_set<int>& set, int n, int m) {
	if (m < 1)
		return;
	std::vector<int> r(m);
	for (int i = 0; i < m; i++)
		r[i] = i;
	int sum = 0;
	for (size_t i = 0; i < r.size(); i++) {
		sum += c[r[i]];
	}
	set.insert(sum);
	while (NextSet(r, n, m)) {
		sum = 0;
		for (size_t i = 0; i < r.size(); i++) {
			sum += c[r[i]];
		}
		set.insert(sum);
	}
	genSochWithRepeat(c, set, n, m - 1);
}


int possibleSums(std::vector<int> coins, std::vector<int> quantity) {
	std::unordered_set<int> set;
	int sum = 0;
	set.insert(0);
	std::unordered_set<int> curSums(set);
	for (size_t i = 0; i < coins.size(); i++) {
		for (auto& cursum : set)
			for (size_t j = 1; j < quantity[i] + 1; j++)
				curSums.insert(cursum + coins[i] * j);
		set.merge(curSums);
		curSums.clear();
	}
	return set.size() - 1;
}

bool checkPairAndInsert(std::vector<std::unordered_set<int>>& vSet, std::vector<int>& pair) {
	for (auto& item : vSet) {
		if (item.find(pair[0]) != item.end()) {
			item.insert(pair[1]);
			pair[0] = 0;
			pair[1] = 0;
			return true;
		}
		else if (item.find(pair[1]) != item.end()) {
			item.insert(pair[0]);
			pair[0] = 0;
			pair[1] = 0;
			return true;
		}
	}
	return false;
}

void dfs(std::unordered_map<int, std::unordered_set<int>>& map, std::unordered_set<int>& set, std::unordered_set<int>& visited, int cur) {
	//std::cout << "stop";
	for (auto& item : map[cur]) {
		if (visited.find(item) == visited.end()) {
			visited.insert(item);
			set.insert(item);
			dfs(map, set, visited, item);
		}
	}
}

std::string swapLexOrder(std::string str, std::vector<std::vector<int>> pairs) {
	if (pairs.empty())
		return str;
	std::vector<std::unordered_set<int>> vSet;
	std::unordered_map<int, std::unordered_set<int>> map;

	for (size_t i = 0; i < pairs.size(); i++) {
		map[pairs[i][0]].insert(pairs[i][1]);
		map[pairs[i][1]].insert(pairs[i][0]);

	}
	std::unordered_set<int> set;
	std::unordered_set<int> visited;
	for (auto& item : map) {
		if (visited.find(item.first) == visited.end()) {
			//visited.insert(item.first);
			//set.insert(item.first);
			dfs(map, set, visited, item.first);
		}
		if (!set.empty())
			vSet.push_back(set);
		set.clear();
		//std::cout << "stop";
	}

	//for (size_t j = 0; j < pairs.size(); j++) {
	//	for (size_t i = 0; i < pairs.size(); i++) {
	//		if (!pairs[i][0] && !pairs[i][1]) {
	//			continue;
	//		}
	//		else {
	//			vSet.push_back(std::unordered_set<int>({ pairs[i][0] , pairs[i][1] }));
	//			break;
	//		}
	//	}
	//	for (size_t i = 0; i < pairs.size(); i++) {
	//		if (!checkPairAndInsert(vSet, pairs[i])) {
	//			vSet.push_back(std::unordered_set<int>({ pairs[i][0] , pairs[i][1] }));
	//		}
	//	}
	//}
	std::vector<std::vector<int> > prepPairs(vSet.size());
	for (size_t i = 0; i < vSet.size(); i++) {
		for (auto& item : vSet[i]) {
			prepPairs[i].push_back(item);
		}
	}
	std::vector<std::string> prepStrings(prepPairs.size());
	for (size_t i = 0; i < prepPairs.size(); i++) {
		for (size_t j = 0; j < prepPairs[i].size(); j++) {
			prepStrings[i] += str[prepPairs[i][j] - 1];
		}
	}

	for (size_t i = 0; i < prepStrings.size(); i++) {
		for (size_t j = 0; j < prepStrings[i].size(); j++) {
			for (size_t n = 0; n < prepStrings[i].size() - 1; n++) {
				if (prepStrings[i][n] < prepStrings[i][n + 1])
					std::swap(prepStrings[i][n], prepStrings[i][n + 1]);
			}
		}
	}

	for (size_t i = 0; i < prepPairs.size(); i++) {
		for (size_t j = 0; j < prepPairs[i].size(); j++) {
			for (size_t n = 0; n < prepPairs[i].size() - 1; n++) {
				if (prepPairs[i][n] > prepPairs[i][n + 1])
					std::swap(prepPairs[i][n], prepPairs[i][n + 1]);
			}
		}
	}

	for (size_t i = 0; i < prepPairs.size(); i++) {
		for (size_t j = 0; j < prepPairs[i].size(); j++) {
			str[prepPairs[i][j] - 1] = prepStrings[i][j];
		}
	}

	return str;
}

extern std::string longString;
extern std::vector<std::vector<int>> longPairs;

int main()
{
	std::cout << swapLexOrder(longString, longPairs);
	// 
	// );
	std::cout << std::endl << swapLexOrder("acxrabdz", {
		{1, 3},
		{6,8},
		{3, 8},
		{2,7},
		});
	std::cout << std::endl << swapLexOrder("fixmfbhyutghwbyezkveyameoamqoi", {
		{8,5} ,
 {10,8},
 {4,18},
 {20,12},
 {5,2},
 {17,2},
 {13,25},
 {29,12},
 {22,2},
 {17,11}
		});

	//std::cout << possibleSumsMy({ 10, 50, 100, 500 }, { 5, 3, 2, 2 });
	//std::cout << possibleSums({ 1, 2 }, { 50000, 2 });



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

	//testArcade();
	//linkedlistImpl();
	return 0;
}

