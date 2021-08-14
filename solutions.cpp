// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include "arrays.h"
#include "linkedlist.h"
#include "hashtables.h"
#include "trees.h"
#include "arcade.h"



int kthLargestElement(std::vector<int> nums, int k) {
	for (int i = 0; i < nums.size(); i++) {
		for (int j = 0; j < nums.size()-1; j++) {
			if (nums[j] > nums[j+1]) {
				nums[j] += nums[j+1];
				nums[j+1] = nums[j] - nums[j+1];
				nums[j] -= nums[j+1];
			}
		}
	}
	return nums[nums.size()-k];
}


int main()
{
	std::cout << kthLargestElement({ 7, 6, 5, 4, 3, 2, 1 }, 2);

	//testTrees();
	//hashtables();
	//testArcade();
	//linkedlistImpl();
	return 0;
}

