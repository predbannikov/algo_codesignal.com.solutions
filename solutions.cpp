// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include <algorithm>
#include <vector>
#include <iostream>
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
	while (l != nullptr ) {
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
		} else
			l = l->next;
	}
	return head;
}

int main()
{

	ListNode<int>* list = new ListNode<int>(3);
	list->push_back(1);
	list->push_back(2);
	list->push_back(3);
	list->push_back(4);
	list->push_back(5);

	removeKFromList(list, 3);
	list->print();

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

