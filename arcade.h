#pragma once
#include "solutions.h"

int centuryFromYear(int year) {
	if (!(year % 10) && year > 99)
		return year / 100;
	return year / 100 + 1;
}

bool checkPalindrome(std::string inputString) {
	if (inputString.size() == 1)
		return true;
	if (inputString.size() == 2)
		return false;
	bool check1 = false, check2 = false;
	int counter1 = 1, counter2 = 1;
	for (int i = 2; i < inputString.size(); i++) {
		if ((i - (2 * counter1) + 1 >= 0 && inputString[i] == inputString[i - (2 * counter1) + 1]) && !check2) {
			if (check1 && i - (2 * counter1) + 1 == 0 && i == inputString.size() - 1)
				return true;
			check1 = true;
			counter1++;
		}
		else {
			if (counter1 > 1)
				i--;
			check1 = false;
			counter1 = 1;
		}
		if ((i - (2 * counter2) >= 0 && inputString[i] == inputString[i - (2 * counter2)]) && !check1) {
			if (check2 && i - (2 * counter2) == 0 && i == inputString.size() - 1)
				return true;
			check2 = true;
			counter2++;
		}
		else {
			if (counter2 > 1)
				i--;
			check2 = false;
			counter2 = 1;
		}
	}
	return false;
}

int sumPairOfIndex(const std::vector<int>& inputArray, int index) {
	return inputArray[index] * inputArray[index + 1];
}

int adjacentElementsProduct(std::vector<int> inputArray) {
	int max = sumPairOfIndex(inputArray, 0);
	for (size_t i = 1; i < inputArray.size() - 1; i++) {
		int tmp = sumPairOfIndex(inputArray, i);
		if (tmp > max) {
			max = tmp;
		}
	}
	return max;
}

int shapeArea(int n) {
	int sum = 0;
	for (int i = 1; i < n; i++) {
		sum += i;
	}
	return sum * 4 + 1;
}

int makeArrayConsecutive2(std::vector<int> statues) {
	return *std::max_element(statues.begin(), statues.end()) - *std::min_element(statues.begin(), statues.end()) - statues.size() + 1;
}

bool almostIncreasingSequence(std::vector<int> sequence) {
	bool check = true;
	if (sequence[0] >= sequence[1])
		check = false;
	if (sequence.size() <= 2 && !check)
		return true;
	if (sequence[1] >= sequence[2])
		if (check)
			check = false;
		else
			return false;
	if(sequence.size() > 3)
		for (int i = 0; i < sequence.size()-2; i++) {
 			if (sequence[i+1] >= sequence[i+2]) {
				if (check) {
					check = false;
					if (sequence.size() > i + 3 && sequence[i + 1] < sequence[i + 3])
						continue;
					else if (sequence.size() <= i + 3)
						return true;
					if (sequence[i] < sequence[i + 1]) {
						std::swap(sequence[i], sequence[i + 1]);
					}
 				}
				else {
					return false;
				}
			}
			if (sequence[i + 1] >= sequence[i + 2])
				return false;
		}
	return true; 
}

int matrixElementsSum(std::vector<std::vector<int>> matrix) {
	int sum = 0;
	for (size_t i = 0; i < matrix.front().size(); i++) {
		for (size_t j = 0; j < matrix.size(); j++) {
			if (matrix[j][i] == 0)
				break;
			sum += matrix[j][i];
		}
	}
	return sum;
}

std::vector<std::string> allLongestStrings(std::vector<std::string> inputArray) {
	int max = 0;
	for (size_t i = 0; i < inputArray.size(); i++) {
		if (max < inputArray[i].size())
			max = inputArray[i].size();
	}
	std::vector<std::string> strs;
	for (size_t i = 0; i < inputArray.size(); i++) {
		if (inputArray[i].size() == max)
			strs.push_back(inputArray[i]);
	}
	return strs;
}


 
void testArcade() {
	//std::vector<std::string> strs = allLongestStrings({ "abacaba",
	// "abacab",
	// "abac",
	// "xxxxxx" });
	//std::copy(strs.begin(), strs.end(), std::ostream_iterator<std::string>(std::cout, " "));
	
	//std::cout << matrixElementsSum({
	//	{4,0,1} ,
 //{10,7,0},
 //{0,0,0},
 //{9,1,2}
	//	}) << std::endl;
	//std::cout << std::boolalpha << almostIncreasingSequence({ 3, 5, 67, 98, 3 });
	//std::cout << makeArrayConsecutive2({ 6, 2, 3, 8 });
	//std::cout << adjacentElementsProduct({ 3, 6, -2, -5, 7, 3 });
	//std::cout << checkPalindrome("hlbeeykoqqqokyeeblh") << std::endl;
}