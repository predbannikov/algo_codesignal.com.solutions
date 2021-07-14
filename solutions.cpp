﻿// solutions.cpp : Defines the entry point for the application.
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
			map.insert( { x, 0 });
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
			map.insert({ ch, 0});
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


int main()
{
	std::cout << firstNotRepeatingCharacter("abacabad") << std::endl;
	return 0;
}