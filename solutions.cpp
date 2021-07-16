// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>

/*Given an array a that contains only numbers in the range from 1 to a.length, find the first duplicate number for which the second occurrence has the minimal index. In other words, if there are more than 1 duplicated numbers, return the number for which the second occurrence has a smaller index than the second occurrence of the other number does. If there are no such elements, return -1.
Example
For a = [2, 1, 3, 5, 3, 2], the output should be firstDuplicate(a) = 3.

There are 2 duplicates: numbers 2 and 3. The second occurrence of 3 has a smaller index than the second occurrence of 2 does, so the answer is 3.

For a = [2, 2], the output should be firstDuplicate(a) = 2;

For a = [2, 4, 3, 5, 1], the output should be firstDuplicate(a) = -1.
*/
int firstDuplicate(std::vector<int> a) {
	std::unordered_map<int, int> map;
	for (auto x : a) {
		if (map.find(x) != map.end())
			return x;
		else
			map.insert({ x, 0 });
	}
}

/*Given a string s consisting of small English letters, find and return the first instance of a non-repeating character in it. If there is no such character, return '_'.

Example

For s = "abacabad", the output should be
firstNotRepeatingCharacter(s) = 'c'.

There are 2 non-repeating characters in the string: 'c' and 'd'. Return c since it appears in the string first.

For s = "abacabaabacaba", the output should be
firstNotRepeatingCharacter(s) = '_'.

There are no characters in this string that do not repeat.*/
char firstNotRepeatingCharacter(std::string s) {
	std::unordered_map<char, int> map;
	for (char ch : s) {
		if (map.find(ch) == map.end()) {
			map.insert({ ch, 0 });
		}
		else {
			map[ch]++;
		}
	}
	for (char ch : s) {
		if (map[ch] < 1)
			return ch;
	}
	return '_';
}

/*Note: Try to solve this task in-place (with O(1) additional memory), since this is what you'll be asked to do during an interview.

You are given an n x n 2D matrix that represents an image. Rotate the image by 90 degrees (clockwise).

Example

For

a = [[1, 2, 3],
	 [4, 5, 6],
	 [7, 8, 9]]
the output should be

rotateImage(a) =
	[[7, 4, 1],
	 [8, 5, 2],
	 [9, 6, 3]]*/
std::vector<std::vector<int>> rotateImage(std::vector<std::vector<int>> a) {
	std::vector<std::vector<int>> rotIm(a.front().size(), std::vector<int>(a.size()));
	size_t x, y;
	x = a.size() - 1;
	for (size_t i = 0; i < a.size(); i++) {
		y = 0;
		for (size_t j = 0; j < a.front().size(); j++) {
			rotIm[y][x] = a[i][j];
			y++;
		}
		x--;
	}
	return rotIm;
}

/*Sudoku is a number-placement puzzle. The objective is to fill a 9 × 9 grid with numbers in such a way that each column, each row, and each of the nine 3 × 3 sub-grids that compose the grid all contain all of the numbers from 1 to 9 one time.

Implement an algorithm that will check whether the given grid of numbers represents a valid Sudoku puzzle according to the layout rules described above. Note that the puzzle represented by grid does not have to be solvable.
Example

For
grid = [['.', '.', '.', '1', '4', '.', '.', '2', '.'],
		['.', '.', '6', '.', '.', '.', '.', '.', '.'],
		['.', '.', '.', '.', '.', '.', '.', '.', '.'],
		['.', '.', '1', '.', '.', '.', '.', '.', '.'],
		['.', '6', '7', '.', '.', '.', '.', '.', '9'],
		['.', '.', '.', '.', '.', '.', '8', '1', '.'],
		['.', '3', '.', '.', '.', '.', '.', '.', '6'],
		['.', '.', '.', '.', '.', '7', '.', '.', '.'],
		['.', '.', '.', '5', '.', '.', '.', '7', '.']]
the output should be
sudoku2(grid) = true;

For
grid = [['.', '.', '.', '.', '2', '.', '.', '9', '.'],
		['.', '.', '.', '.', '6', '.', '.', '.', '.'],
		['7', '1', '.', '.', '7', '5', '.', '.', '.'],
		['.', '7', '.', '.', '.', '.', '.', '.', '.'],
		['.', '.', '.', '.', '8', '3', '.', '.', '.'],
		['.', '.', '8', '.', '.', '7', '.', '6', '.'],
		['.', '.', '.', '.', '.', '2', '.', '.', '.'],
		['.', '1', '.', '2', '.', '.', '.', '.', '.'],
		['.', '2', '.', '.', '3', '.', '.', '.', '.']]
the output should be
sudoku2(grid) = false.
The given grid is not correct because there are two 1s in the second column. Each column, each row, and each 3 × 3 subgrid can only contain the numbers 1 through 9 one time.*/
bool sudoku2(std::vector<std::vector<char>> grid) {
	for (size_t iy = 0; iy < 3; iy++) {
		for (size_t ix = 0; ix < 3; ix++) {
			std::unordered_map<char, int> mapCell;
			for (size_t y = 0; y < 3; y++) {
				for (size_t x = 0; x < 3; x++) {
					char ch = grid[y + 3 * iy][x + 3 * ix];
					if (ch != '.') {
						if (mapCell.find(ch) == mapCell.end()) {
							mapCell.insert({ ch, 0 });
						}
						else {
							mapCell[ch]++;
							if (mapCell[ch] > 0)
								return false;
						}
					}
				}
			}
		}
	}

	for (size_t i = 0; i < 9; i++) {
		std::unordered_map<char, int> mapX;
		std::unordered_map<char, int> mapY;
		for (size_t j = 0; j < 9; j++) {
			char chX = grid[i][j];
			if (chX != '.') {
				if (mapX.find(chX) == mapX.end()) {
					mapX.insert({ chX, 0 });
				}
				else {
					mapX[chX]++;
					if (mapX[chX] > 0)
						return false;
				}
			}
		}
		for (size_t j = 0; j < 9; j++) {
			char chY = grid[j][i];
			if (chY != '.') {
				if (mapY.find(chY) == mapY.end()) {
					mapY.insert({ chY, 0 });
				}
				else {
					mapY[chY]++;
					if (mapY[chY] > 0)
						return false;
				}
			}
		}
	}
	return true;
}

bool isCryptSolution(std::vector<std::string> crypt, std::vector<std::vector<char>> solution) {
	std::unordered_map<char, char> map;
	for (auto item : solution) {
		map.insert({ item.front(), item.back() });
	}
	int diff = '0';
	int dgts[3];
	int* pDgt = dgts;
	int counterDgt = 0;
	for (auto str : crypt) {
		*(dgts + counterDgt) = 0;
		for (char ch : str) {
			*(dgts + counterDgt) *= 10;
			*(dgts + counterDgt) += map[ch] - diff;
			if (*(dgts + counterDgt) == 0 && str.size() > 1)
				return false;
		}
		counterDgt++;
	}
	int* p1 = pDgt;
	int* p2 = pDgt + 1;
	int* p3 = pDgt + 2;
	if (*p1 + *p2 == *p3) {
		return true;
	}
	return false;
}

template<typename T>
struct ListNode {
	ListNode(const T& v) : value(v), next(nullptr) {}
	void push_back(const T& v) {
		ListNode<T>* current = this;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = new ListNode(v);
	}
	void print() {
		ListNode<int>* current = this;
		while (current->next != nullptr) {
			current = current->next;
			std::cout << current->value << " ";
		}
	}
	T value;
	ListNode* next;
};



ListNode<int>* removeKFromList(ListNode<int>* l, int k) {
	while (l != nullptr) {
		if (l->value == k)
			l = l->next;
		else
			break;
		if (l == nullptr)
			return l;

	}
	ListNode<int>* head = l;

	while (l != nullptr && l->next != nullptr) {
		if (l->next->value == k) {
			l->next = l->next->next;
		}
		else
			l = l->next;
	}
	return head;
}

/*Note: Try to solve this task in O(n) time using O(1) additional space, where n is the number of elements in l, since this is what you'll be asked to do during an interview.
Given a singly linked list of integers, determine whether or not it's a palindrome.
Note: in examples below and tests preview linked lists are presented as arrays just for simplicity of visualization: in real data you will be given a head node l of the linked list
Example

For l = [0, 1, 0], the output should be
isListPalindrome(l) = true;

For l = [1, 2, 2, 3], the output should be
isListPalindrome(l) = false.

Input/Output

[execution time limit] 0.5 seconds (cpp)

[input] linkedlist.integer l

A singly linked list of integers.

Guaranteed constraints:
0 ≤ list size ≤ 5 · 105,
-109 ≤ element value ≤ 109.

[output] boolean

Return true if l is a palindrome, otherwise return false.*/
//bool isListPalindrome(ListNode<int>* l) {	// 3 2 1 2 3
//	std::vector<int> left, right;
//	size_t size = 0;
//	if (l == nullptr) {
//		return true;
//	}
//	bool checkV1 = false;
//	bool checkV2 = false;
//	std::vector<int>::iterator iLeft;
//	size_t index_r = 0;
//	while (l != nullptr) {
//		size++;
//		int cur = l->value;
//		if (!checkV1 && !checkV2) {
//			if (left.size() < 2) {
//				if (!left.empty() && left.front() == cur) {
//					checkV1 = true;
//					iLeft = left.end() - 1;
//					right.clear();
//					right.push_back(cur);
//				}
//				else
//					left.push_back(cur);
//			}
//			else {
//				if (cur != left.back() && cur != left[left.size() - 2] ) {
//					left.push_back(cur);
//				}
//				else {
//					if (cur == left.back()) {
//						checkV1 = true;
//						iLeft = left.end() - 1;
//						index_r = left.size() - 1;
//					}
//					else if (cur == left[left.size() - 2]) {
//						checkV2 = true;
//						iLeft = left.end() - 2;
//						index_r = left.size() - 2;
//					}
//					right.clear();
//					right.push_back(cur);
//				}
//			}
//		}
//		else {
//			index_r--;
//			if (iLeft != left.begin()) {
//				iLeft--;
//				if (*iLeft == cur) {
//					right.push_back(cur);
//				}
//				else {
//					std::copy(left.begin(), left.end(), std::back_inserter(right));
//					checkV1 = false;
//					checkV2 = false;
//				}
//			}
//			else {
//				std::copy(right.begin(), right.end(), std::back_inserter(left));
//				left.push_back(cur);
//				checkV1 = false;
//				checkV2 = false;
//			}
//
//		}
//
//		l = l->next;
//	}
//	if (size == 1)
//		return true;
//	if (checkV1 ) {
//		if (left.size() == 2) {
//			return true;
//		}
//		else if(0 == index_r) {
//			return true;
//		}
//	}
//	else if (checkV2 ) {
//		if (left.size() == 2) {
//			return left.front() == right.front();
//
//		}
//		else if (0 == index_r) {
//			return true;
//		}
//	}
//	return false;
//}

//bool isListPalindrome(ListNode<int>* l) {
//	if (l == nullptr)
//		return false;
//	if (l->next == nullptr)
//		return true;
//	if (l->next->next == nullptr)
//	{
//
//	}
//	else {
//		ListNode<int>* head = new ListNode(l->value);
//		ListNode<int>* prev = nullptr;
//		bool check = false;
//		while (l->next->next != nullptr) {
//			ListNode<int>* tmp = new ListNode(l->next->value);
//			tmp->next = head;
//			head = tmp;
//
//			if (check) {
//				if (prev == nullptr)
//					prev = head;
//				if (l->value != prev->value)
//					return false;
//			}
//			if (l->next->value == head->next->value) {
//				prev = head;
//				check = true;
//			}
//			if (prev != nullptr)
//				prev = prev->next;
//			l = l->next;
//		}
//	}
//
//}


bool isListPalindrome(ListNode<int>* l) {
	bool isPoly = true;
	ListNode<int>* firstLinkedList = l;
	std::stack<int>* slist = new std::stack<int>();
	while (firstLinkedList != nullptr) {
		slist->push(firstLinkedList->value);
		firstLinkedList = firstLinkedList->next;
	}
	while (l != nullptr) {
		int value = slist->top();
		slist->pop();
		if (value == l->value) {
			isPoly = true;
		}
		else {
			isPoly = false;
			break;
		}
		l = l->next;
	}
	return isPoly;
}

ListNode<int>* addTwoHugeNumbers(ListNode<int>* a, ListNode<int>* b) {
	std::vector<int> ptr_a;
	std::vector<int> ptr_b;
	int n_a = 0;
	int n_b = 0;
	while (a != nullptr || b != nullptr) {
		if (a != nullptr) {
			ptr_a.resize(n_a + 1);
			ptr_a[n_a] = a->value;
			a = a->next;
			n_a++;
		}
		if (b != nullptr) {
			ptr_b.resize(n_b + 1);
			ptr_b[n_b] = b->value;
			b = b->next;
			n_b++;
		}
	}
	ListNode<int>* list = nullptr;
	int over = 0;
	int c = 0;
	while (n_a > 0 || n_b > 0) {
		int r_a, r_b;
		r_a = r_b = 0;
		c = over;
		if (n_a > 0) {
			r_a = ptr_a[n_a - 1];
			c += r_a;
			n_a--;
		}
		if (n_b > 0) {
			r_b = ptr_b[n_b - 1];
			c += r_b;
			n_b--;
		}
		over = c / 10000;
		c -= over * 10000;
		if (list == nullptr) {
			list = new ListNode<int>(c);
		}
		else {
			ListNode<int>* tmp = new ListNode<int>(c);
			tmp->next = list;
			list = tmp;
		}
	}
	if (over > 0) {
		ListNode<int>* tmp = new ListNode<int>(over);
		tmp->next = list;
		list = tmp;
	}

	//int& a1 = a->value;
	//int& a2 = a->next->value;
	//int& a3 = a->next->next->value;
	//int& b1 = b->value;
	//int& b2 = b->next->value;
	//int& b3 = b->next->next->value;
	//int c3 = b3 + a3;
	//int c2 = b2 + a2;
	//int c1 = b1 + a1;
	//int over = c3 % 1000;
	//c2 += over;
	//over %= c2;
	//c1 += over;
	//ListNode<int>* list = new ListNode<int>(c1);
	//list->next = new ListNode<int>(c2);
	//list->next->next = new ListNode<int>(c3);
	return list;
}

ListNode<int>* mergeTwoLinkedLists(ListNode<int>* l1, ListNode<int>* l2) {
	if (l1 == nullptr) {
		l1 = l2;
		return l1;
	}
	else if (l2 == nullptr) {
		return l1;
	}
	else {
		ListNode<int>* cur = nullptr;
		ListNode<int>* head;

		if (l1->value < l2->value) {
			head = new ListNode<int>( l1->value);
			ListNode<int>* tmp = new ListNode<int>(0);
			tmp->next = l2;
			l2 = tmp;
		}
		else {
			head = new ListNode<int>( l2->value);
			ListNode<int>* tmp = new ListNode<int>(0);
			tmp->next = l1;
			l1 = tmp;
		}
		cur = head;
		while (l1->next != nullptr && l2->next != nullptr) {
			if (l1->next->value < l2->next->value) {
				cur->next = new ListNode<int>(l1->next->value);;
				l1 = l1->next;
			}
			else {
				cur->next = new ListNode<int>(l2->next->value);;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (l1->next != nullptr)
			cur->next = l1->next;
		if (l2->next != nullptr)
			cur->next = l2->next;
		return head;
	}
}
//ListNode<int>* mergeTwoLinkedLists(ListNode<int>* l1, ListNode<int>* l2) {
//	if (l1 == nullptr) {
//		l1 = l2;
//		return l1;
//	}
//	else if (l2 == nullptr) {
//		return l1;
//	}
//	else {
//		ListNode<int>* cur = nullptr;
//		ListNode<int>* list, *head;
//
//		if (l1->value < l2->value) {
//			list = new ListNode<int>( l1->value);
//		}
//		else {
//			list = new ListNode<int>(l2->value);
//		}
//		head = list;
//		while (l1->next != nullptr && l2->next != nullptr) {
//			if (l1->next->value < l2->next->value) {
//				cur = l1;
//				l1 = l1->next;
//			}
//			else {
//				cur = l2;
//				l2 = l2->next;
//			}
//			list->next = new ListNode<int>(cur->value);
//			list = list->next;
//		}
//		if (l1->next != nullptr)
//			list->next = l1;
//		if (l2->next != nullptr)
//			list->next = l2;
//		return head;
//	}
//}

int main()
{
	ListNode<int>* list = nullptr;
	ListNode<int>* list2 = nullptr;
	std::vector<int> a{ 1, 1, 2, 4 };
	std::vector<int> b{ 0, 3, 5 };
	for (int i = 0; i < a.size(); i++) {
		if (list == nullptr)
			list = new ListNode<int>(a[i]);
		else
			list->push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++) {
		if (list2 == nullptr)
			list2 = new ListNode<int>(b[i]);
		else
			list2->push_back(b[i]);
	}

	//ListNode<int>* list = new ListNode<int>(8339);
	//list->push_back(4510);
	////list->push_back(1999);
	//ListNode<int>* list2 = new ListNode<int>(2309);
	////list2->push_back(8001);
	////list->push_back(1);
	ListNode<int>* list3 = mergeTwoLinkedLists(list, list2);

	while (list3 != nullptr) {
		std::cout << list3->value << " ";
		list3 = list3->next;
	}

	//removeKFromList(list, 3);
	//list->print();

	////std::vector<std::vector<char>> solution = { {'O', '0'},
	////	{'M', '1'},
	////	{'Y', '2'},
	////	{'E', '5'},
	////	{'N', '6'},
	////	{'D', '7'},
	////	{'R', '8'},
	////	{'S', '9'} };
	////std::vector<std::string> crypt = { "SEND", "MORE", "MONEY" };
	//std::vector<std::vector<char>> solution = { {'A', '0'}, };
	//std::vector<std::string> crypt = { "A", "A", "A" };
	//std::cout << isCryptSolution(crypt, solution) << std::endl;
	////std::vector<std::vector<char>> arr{
 ////{'.','.','4'	,'.','.','.'	,'6','3','.'},
 ////{'.','.','.'	,'.','.','.'	,'.','.','.'},
 ////{'5','.','.'	,'.','.','.'	,'.','9','.'},
 ////
 ////{'.','.','.'	,'5','6','.'	,'.','.','.'},
 ////{'4','.','3'	,'.','.','.'	,'.','.','1'},
 ////{'.','.','.'	,'7','.','.'	,'.','.','.'},
 ////
 ////{'.','.','.'	,'5','.','.'	,'.','.','.'},
 ////{'.','.','.'	,'.','.','.'	,'.','.','.'},
 ////{'.','.','.'	,'.','.','.'	,'.','.','.'} 
	////};
	////std::cout << sudoku2(arr);
	////std::vector<std::vector<int>> a{ 
	////	{1, 2, 3},
	////	{4, 5, 6},
	////	{7, 8, 9 }, };
	////std::vector<std::vector<int>> b = rotateImage(a);
	////for (size_t i = 0; i < b.size(); i++) {
	////	for (size_t j = 0; j < a.front().size(); j++) {
	////		std::cout << b[i][j] << " ";
	////	}
	////	std::cout << std::endl;
	////}

	//std::cout << firstNotRepeatingCharacter("abacabad") << std::endl;
	return 0;
}

