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

void sm(std::vector<int>& c, std::vector<int>& q, std::unordered_set<int>& s, int ix, int sum) {
	if (ix == c.size()) {
		s.insert(sum);
		return;
	}
	else {
		for (int i = 0; i <= q[i]; i++) {
			sm(c, q, s, i + 1, sum + c[ix] * i);
		}
	}
}

void test(std::unordered_set<int>& set, std::vector<int>& a) {
	if (a.empty()) {
		return;
	}
	std::vector<int> tmp(a.size() - 1);
	if (tmp.empty())
		return;
	if (tmp.size() == 1)
		return;
	for (size_t i = 0; i < a.size(); i++) {
		int index_tmp = 0;
		for (size_t j = 0; j < a.size(); j++)
			if (j != i) {
				tmp[index_tmp++] = a[j];
			}
		int sum = 0;
		for (int i = 0; i < tmp.size(); i++) {
			sum += tmp[i];
		}

		std::copy(tmp.begin(), tmp.end(), std::ostream_iterator<int>(std::cout << std::endl, " "));
		set.insert(sum);
		test(set, tmp);
	}
}

void ttt() {
	uint8_t x = 0b01011000;
	x = x & (x + 1);

	std::bitset<8> b(x);
	std::cout << "yes x=" << b << std::endl;

}

bool NextSet(std::vector<int>& a, int n)
{
	int k = a.size();
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

void genSochWithRepeat(std::vector<int>& c, std::unordered_set<int>& set, std::vector<int>& a, int m) {

	if (m < 1)
		return;

	size_t k = fact(a.size()) / (fact(a.size() - m) * fact(m));
	std::vector<std::vector<int>> res(k, std::vector<int>(m, 0));
	for (size_t i = 0; i < res.front().size(); i++)
		res.front()[i] = i;

	for (size_t i = 0; i < k; i++) {
		if (!NextSet(res[i], res[i].size() - 1)) {

			std::copy(res[i].begin(), res[i].end(), std::ostream_iterator<int>(std::cout << std::endl, "\t"));
		}
		if (i + 1 < k)
			res[i + 1] = res[i];
	}
	for (size_t i = 0; i < res.size(); i++) {
		int sum = 0;
		for (size_t j = 0; j < res[i].size(); j++) {
			sum += c[res[i][j]];
		}
		set.insert(sum);
	}
	genSochWithRepeat(c, set, a, m - 1);
}


int possibleSums(std::vector<int> coins, std::vector<int> quantity) {
	//ttt();
	std::multiset<int> mset;
	std::unordered_set<int> set;
	std::vector<int> vSet;
	std::vector<int> cSet;
	int sum = 0;
	for (size_t i = 0; i < coins.size(); i++) {
		for (size_t j = 0; j < quantity[i]; j++) {
			//sum += coins[i];
			cSet.push_back(coins[i]);
		}
	}
	for (size_t i = 0; i < cSet.size(); i++)
		vSet.push_back(i);


	int n = vSet.size();
	int m = n - 1;
	size_t k = fact(n) / (fact(n - m) * fact(m));

	genSochWithRepeat(cSet, set, vSet, vSet.size() - 1);

	return set.size();

	//set.insert(sum);
	//bt(coins, quantity, set, 0, 0);
	//std::vector<int> tt{ 1, 2, 3, 4 };
	//std::vector<int>b = coins2;

	//for (int i = 0; i < fact(vSet.size()); i++)
	//{
	//	std::next_permutation(vSet.begin(), vSet.end());
	//}

	//test(set, vSet);
	return set.size();

	//test(coins2, coins2.size());
	//while (true) {
	//	std::vector<int> a;
	//	std::copy(coins2);
	//}
	//int size = fact(coins2.size()) ;
	//for (int i = 0; i < size; i++) {
	//	std::copy(coins2.begin(), coins2.end(), std::ostream_iterator<int>(std::cout << std::endl, "\t"));
	//	if (i == 12) {
	//	}
	//	if (algoNarajanj(coins2)) {
	//		std::reverse(coins2.begin(), coins2.end());
	//		coins2.pop_back();
	//	}
	//}

	//do {
	//	//for (int i = 0; i < n; ++i) {
	//	//	if (v[i]) {
	//	//		std::cout << (i + 1) << " ";
	//	//	}
	//	//}
	//	std::copy(coins2.begin(), coins2.end(), std::ostream_iterator<int>(std::cout << std::endl, " "));
	//} while (std::next_permutation(coins2.begin(), coins2.end()));
	//const int test[] = { 1,2,3,4 };
	////PermutationWithRepetition(test, 4, 4);

	////std::multiset<int>::iterator it = mset.begin();




	//std::unordered_set<int>* setResults = new std::unordered_set<int>;
	//setResults->merge(*possibleSumsSup(mset));
	//std::cout << std::endl;
	return 0;
}

struct BtNode {
	BtNode(int value_, BtNode* left_ = nullptr, BtNode* right_ = nullptr) : value(value_), l(left_), r(right_) {}
	int value;
	BtNode* l, * r;
};

void add_node(int value, BtNode*& tree) {
	if (tree == nullptr)
		tree = new BtNode(value);

	else if (value < tree->value)
		if (tree->l != nullptr)
			add_node(value, tree->l);
		else
			tree->l = new BtNode(value);
	else if (value >= tree->value)
		if (tree->r != nullptr)
			add_node(value, tree->r);
		else
			tree->r = new BtNode(value);

}

void show(BtNode*& tree) {
	if (tree != nullptr) {
		show(tree->l);
		std::cout << tree->value << std::endl;

		show(tree->r);
	}
	else {
		//std::cout << "endl ";
	}
}

int main()
{
	//BtNode* tree = nullptr;
	//add_node(3, tree);
	//for (int i = 0; i < 5; i++) {
	//	add_node(i, tree);
	//}
	//show(tree);
	std::cout << possibleSums({ 10, 50, 100, 500 }, { 5, 3, 2, 2 });


	std::vector<int> a{ 1, 2, 3, 4 };

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

