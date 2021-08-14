// solutions.cpp : Defines the entry point for the application.
//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "solutions.h"
#include "arrays.h"
#include "linkedlist.h"
#include "hashtables.h"
#include "arcade.h"
#include "json.hpp"



using namespace rapidjson;

using json = nlohmann::json;



template<typename T>
struct Tree {
	Tree(const T& v = 0) : value(v), left(nullptr), right(nullptr) {}
	T value;
	Tree* left;
	Tree* right;
};

void heightTree(Tree<int>* tree, int lvl, int& max) {
	if (max < lvl)
		max = lvl;
	if (tree->left != nullptr) {
		heightTree(tree->left, lvl + 1, max);
	}
	if (tree->right != nullptr) {
		heightTree(tree->right, lvl + 1, max);
	}
	return;
}

#define WIDTH 150
#define HALF_WIDTH (WIDTH/2)

void traversalTree(std::vector<std::string>& v, Tree<int>* tree, int lvl, int i1, int maxLvl = 0) {

	if (maxLvl != 0 && lvl >= maxLvl) {
		return;
	}
	std::string val = std::to_string(tree->value);
	int valSize = val.length();
	int curPos = i1;
	if (i1 - (valSize / 2) >= 0)
		curPos = i1 - valSize / 2;
	for (size_t i = curPos, j = 0; i < curPos + val.size(); i++, j++)
		v[lvl * 2][i] = val[j];
	int diff;
	if (tree->left != nullptr) {
		diff = HALF_WIDTH / pow(2, lvl);
		v[(lvl * 2) + 1][curPos + (valSize / 2) - diff / 2] = '/';
		traversalTree(v, tree->left, lvl + 1, i1 - diff, maxLvl);

	}
	if (tree->right != nullptr) {
		diff = HALF_WIDTH / pow(2, lvl);
		v[(lvl * 2) + 1][curPos + (valSize / 2) + diff / 2] = '\\';
		traversalTree(v, tree->right, lvl + 1, i1 + diff, maxLvl);
	}
	return;
}

void printTree(Tree<int>* tree, int maxLvl = 0) {
	if (tree == nullptr) {
		std::cout << std::string(HALF_WIDTH, ' ') << "nill" << std::endl;
		return;
	}
	int height = maxLvl;
	if (height == 0)
		heightTree(tree, 0, height);
	std::vector<std::string> pic((height + 1) * 2 + 1, std::string(WIDTH, ' '));
	traversalTree(pic, tree, 1, HALF_WIDTH, maxLvl);
	for (size_t i = 0; i < pic.size(); i++) {
		std::cout << pic[i] << std::endl;
	}
}

std::string* loadStringJson(const std::string path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "could not open file " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string* ret = new std::string(std::istream_iterator<char>(file), std::istream_iterator<char>());
	file.close();
	return ret;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void parseJSONtoTwoVectors(std::string& str, std::vector<int>& one, std::vector<int>& two, int& idx, int& lastIdx) {
	int sign = 0;
	while (idx < str.size()) {
		char ch = str[idx];
		switch (ch)
		{
		case '{':
			switch (sign)
			{
			case 1:
				std::stoi(str.substr(lastIdx + 1, idx - lastIdx - 1));
				break;
			case 2:
				idx++;
				parseJSONtoTwoVectors(str, one, two, idx, lastIdx);
				break;
			case 3:
				idx++;
				parseJSONtoTwoVectors(str, one, two, idx, lastIdx);
				break;
			case 4:
				break;
			default:
				break;
			}
			sign = 0;
			lastIdx = idx;
			break;
		case '}':
			switch (sign)
			{
			case 1: {
				one.push_back(std::stoi(str.substr(lastIdx + 1, idx - (lastIdx + 1))));
				break;
			}
			}
			lastIdx = idx;
			return;
		case '[':
			lastIdx = idx;
			break;
		case ']':
			switch (sign)
			{
			case 1:
				one.push_back(std::stoi(str.substr(lastIdx + 1, idx - (lastIdx + 1))));
				break;
			case 2:
				two.push_back(std::stoi(str.substr(lastIdx + 1, idx - (lastIdx + 1))));
				break;
			};
			sign = 0;
			lastIdx = idx;
			break;
		case ':':
			if (str.substr(idx - 8, 7) == "inorder")
				sign = 1;
			else if (idx - 9 >= 0 && str.substr(idx - 9, 8) == "preorder")
				sign = 2;
			else if (str.substr(idx - 6, 5) == "input")
				sign = 3;
			else if (str.substr(idx - 7, 6) == "output") {
				std::cout << "this is the data of " << str.substr(idx - 7, 6) << " need make new Tree" << std::endl;
				return;
			}
			lastIdx = idx;
			break;
		case ',':
			switch (sign)
			{
			case 1:
				one.push_back(std::stoi(str.substr(lastIdx + 1, idx - (lastIdx + 1))));
				break;
			case 2:
				two.push_back(std::stoi(str.substr(lastIdx + 1, idx - (lastIdx + 1))));
				break;
			};
			lastIdx = idx;
			break;
		}
		idx++;
	}
}

void loadTooVectors(std::vector<int>& one, std::vector<int>& two, std::string path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "could not open file " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	std::string* ret = new std::string(std::istream_iterator<char>(file), std::istream_iterator<char>());
	int idx = 0, lastIdx = 0;
	parseJSONtoTwoVectors(*ret, one, two, idx, lastIdx);
	file.close();

}

void parseJSONtoTree(std::string& str, int& idx, Tree<int>*& tree, size_t& lastIndex) {
	int sign = 0;
	tree = new Tree<int>;
	while (idx < str.size()) {
		char ch = str[idx];
		switch (ch)
		{
		case '{':
			switch (sign)
			{
			case 1:
				tree->value = std::stoi(str.substr(lastIndex + 1, idx - lastIndex - 1));
				break;
			case 2:
				idx++;
				parseJSONtoTree(str, idx, tree->left, lastIndex);
				break;
			case 3:
				idx++;
				parseJSONtoTree(str, idx, tree->right, lastIndex);
				break;
			case 4:
				break;
			default:
				break;
			}
			sign = 0;
			lastIndex = idx;
			break;
		case '}':
			switch (sign)
			{
			case 1: {
				tree->value = std::stoi(str.substr(lastIndex + 1, idx - (lastIndex + 1)));
				break;
			}
			case 2:
				tree->left = nullptr;
				break;
			case 3:
				tree->right = nullptr;
				break;
			default:
				break;
			}
			lastIndex = idx;
			return;
		case ':':
			if (str.substr(idx - 6, 5) == "value")
				sign = 1;
			else if (str.substr(idx - 5, 4) == "left") {
				sign = 2;
			}

			else if (str.substr(idx - 6, 5) == "right") {
				sign = 3;
			}
			else if (str.substr(idx - 5, 4) == "null")
				sign = 4;
			lastIndex = idx;
			break;
		case ',':
			switch (sign)
			{
			case 1: {
				std::string tmp = str.substr(lastIndex + 1, idx - (lastIndex + 1));
				tree->value = std::stoi(tmp);
			}
				  break;
			case 2:
				tree->left = nullptr;
				break;
			case 3:
				tree->right = nullptr;
				break;
			default:
				break;
			}
			lastIndex = idx;
			break;
		default:
			break;
		};
		idx++;
	}
}

void iterationTreeRecurs(Tree<int>* tree) {
	if (!tree)
		return;
	std::cout << tree->value << std::endl;
	if (tree->left)
		iterationTreeRecurs(tree->left);
	if (tree->right)
		iterationTreeRecurs(tree->right);
}

void iterationTreeStack(Tree<int>* tree) {
	std::stack<Tree<int>*>stack;
	stack.push(tree);
	while (!stack.empty()) {
		Tree<int>* node = stack.top();
		stack.pop();
		std::cout << node->value << std::endl;
		if (node->right)
			stack.push(node->right);
		if (node->left)
			stack.push(node->left);
	}
}

void iterationTreeQueue(Tree<int>* tree) {
	std::queue<Tree<int>*>queue;
	queue.push(tree);
	while (!queue.empty()) {
		Tree<int>* node = queue.front();
		queue.pop();
		std::cout << node->value << std::endl;
		if (node->right)
			queue.push(node->right);
		if (node->left)
			queue.push(node->left);
	}
}

Tree<int>* strJsonToTree(std::string* str) {
	Tree<int>* tree = nullptr;
	size_t lastIndex = 0;
	int idx = 0;
	parseJSONtoTree(*str, idx, tree, lastIndex);
	//iterationTreeQueue(tree);
	//iterationTreeStack(tree);
	//iterationTreeRecurs(tree);
	return tree;
}

bool hightS(Tree<int>* t, int s, int sum) {
	if (t == nullptr)
		return false;
	sum += t->value;
	if (hightS(t->left, s, sum))
		return true;
	if (hightS(t->right, s, sum))
		return true;

	if (!t->left && !t->right && sum == s)
		return true;
	return false;
}

/*Given a binary tree t and an integer s, determine whether there is a root to leaf path in t such that the sum of vertex values equals s.
s = 7,
the output should be hasPathWithGivenSum(t, s) = true.
This is what this tree looks like:

	  4
	 / \
	1   3
   /   / \
  -2  1   2
	\    / \
	 3  -2 -3
Path 4 -> 3 -> 2 -> -2 gives us 7, the required sum.
and
s = 7,
the output should be hasPathWithGivenSum(t, s) = false.
This is what this tree looks like:
	  4
	 / \
	1   3
   /   / \
  -2  1   2
	\    / \
	 3  -4 -3
There is no path from root to leaf with the given sum 7.
	 */
bool hasPathWithGivenSum(Tree<int>* t, int s) {
	int sum = 0;
	return hightS(t, s, sum);
}

/*
Given a binary tree t, determine whether it is symmetric around its center, i.e. each side mirrors the other.
the output should be isTreeSymmetric(t) = true.
Here's what the tree in this example looks like:
	1
   / \
  2   2
 / \ / \
3  4 4  3
As you can see, it is symmetric.
the output should be isTreeSymmetric(t) = true.
Here's what the tree in this example looks like:
	1
   / \
  2   2
 / \ / \
3  4 4  3
As you can see, it is symmetric.
*/
bool isTreeSymmetric(Tree<int>* t) {
	if (t == nullptr)
		return true;
	std::stack<Tree<int>*> stackLeft;
	std::stack<Tree<int>*> stackRight;
	stackLeft.push(t);
	stackRight.push(t);
	while (!stackLeft.empty() && !stackRight.empty()) {
		Tree<int>* left = stackLeft.top();
		stackLeft.pop();
		Tree<int>* right = stackRight.top();
		stackRight.pop();
		if (left->value != right->value)
			return false;

		if (left->left) {
			if (right->right) {
				stackLeft.push(left->left);
				stackRight.push(right->right);
			}
			else {
				return false;
			}
		}
		if (left->right) {
			if (right->left) {
				stackLeft.push(left->right);
				stackRight.push(right->left);
			}
			else {
				return false;
			}
		}
	}
	return true;
}

/*Consider a special family of Engineers and Doctors. This family has the following rules:

Everybody has two children.
The first child of an Engineer is an Engineer and the second child is a Doctor.
The first child of a Doctor is a Doctor and the second child is an Engineer.
All generations of Doctors and Engineers start with an Engineer.
We can represent the situation using this diagram:
				E
		   /         \
		  E           D
		/   \        /  \
	   E     D      D    E
	  / \   / \    / \   / \
	 E   D D   E  D   E E   D
Given the level and position of a person in the ancestor tree above, find the profession of the person.
Note: in this tree first child is considered as left child, second - as right.

Example

For level = 3 and pos = 3, the output should be
findProfession(level, pos) = "Doctor".*/
std::string helpFindProfession(int pos) {
	if (pos == 1)
		return "left";
	if (helpFindProfession((pos + 1) / 2) == "right") {
		return (pos) % 2 ? "right" : "left";
	}
	else {
		return (pos) % 2 ? "left" : "right";
	}
}

std::string findProfession(int level, int pos) {

	if (helpFindProfession(pos) == "right")
		return "Doctor";
	else
		return "Engineer";
}

/*Note: Your solution should have only one BST traversal and O(1) extra space complexity, since this is what you will be asked to accomplish in an interview.

A tree is considered a binary search tree (BST) if for each of its nodes the following is true:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and the right subtrees must also be binary search trees.
Given a binary search tree t, find the kth smallest element in it.

Note that kth smallest element means kth element in increasing order. See examples for better understanding.
and k = 4, the output should be
kthSmallestInBST(t, k) = 5.

Here is what t looks like:

   3
 /   \
1     5
	 / \
	4   6
The values of t are [1, 3, 4, 5, 6], and the 4th smallest is 5.
and k = 1, the output should be
kthSmallestInBST(t, k) = -2.

Here is what t looks like:

	 1
	/
  -1
  / \
-2   0
The values of t are [-2, -1, 0, 1], and the 1st smallest is -2.*/

//Tree<int>* treeMin(Tree<int>* min) {
//	while (min->left != nullptr)
//		min = min->left;
//	return min;
//}
//
//Tree<int>* rightItem(Tree<int>* t) {
//	if (t->right != nullptr) {
//		return treeMin(t);
//	} 
//	Tree<int> *right = t->right;
//
//	while(right.)
//}

bool helperKthSmallestInBST(Tree<int>* t, int& k, int& ret, int& counter) {

	if (t->left) {
		if (helperKthSmallestInBST(t->left, k, ret, counter))
			return true;
	}
	counter++;
	if (counter == k) {
		ret = t->value;
		return true;
	}
	if (t->right) {
		if (helperKthSmallestInBST(t->right, k, ret, counter))
			return true;
	}
	return false;
}

int kthSmallestInBST(Tree<int>* t, int k) {


	int ret = 0;
	int counter = 0;
	helperKthSmallestInBST(t, k, ret, counter);
	return ret;
}

/*Given two binary trees t1 and t2, determine whether the second tree is a subtree of the first tree. A subtree for vertex v in a binary tree t is a tree consisting of v and all its descendants in t. Determine whether or not there is a vertex v (possibly none) in tree t1 such that a subtree for vertex v (possibly empty) in t1 equals t2.
* the output should be isSubtree(t1, t2) = true.

This is what these trees look like:

	  t1:             t2:
	   5              10
	  / \            /  \
	10   7          4    6
   /  \            / \    \
  4    6          1   2   -1
 / \    \
1   2   -1
As you can see, t2 is a subtree of t1 (the vertex in t1 with value 10).


the output should be isSubtree(t1, t2) = false.
This is what these trees look like:
		t1:            t2:
		 5             10
	   /   \          /  \
	 10     7        4    6
   /    \           / \    \
  4     6          1   2   -1
 / \   /
1   2 -1
As you can see, there is no vertex v such that the subtree of t1 for vertex v equals t2.
the output should be isSubtree(t1, t2) = false.
*/
bool compareTree(Tree<int>* t1, Tree<int>* t2) {
	std::stack<std::pair<Tree<int>*, Tree<int>*>> stack;
	stack.push({ t1, t2 });
	while (!stack.empty()) {
		auto [tr1, tr2] = stack.top();
		stack.pop();
		if (tr1 != tr1)
			return false;
		if (tr1 == nullptr || tr2 == nullptr)
			return false;
		if (tr1->value != tr2->value)
			return false;
		if (tr1->left || tr2->left) {
			stack.push({ tr1->left, tr2->left });
		}
		if (tr1->right || tr2->right)
			stack.push({ tr1->right, tr2->right });
	}
	return true;
}
bool isSubtree(Tree<int>* t1, Tree<int>* t2) {
	if (t2 == nullptr)
		return true;
	if (t1 == nullptr)
		return false;
	std::stack<Tree<int>*> stack({ t1 });
	while (!stack.empty()) {
		Tree<int>* tree = stack.top();
		stack.pop();
		if (compareTree(tree, t2))
			return true;
		if (tree->left)
			stack.push(tree->left);
		if (tree->right)
			stack.push(tree->right);
	}
	return 	false;
}

/*Note: Your solution should have O(inorder.length) time complexity, since this is what you will be asked to accomplish in an interview.

Let's define inorder and preorder traversals of a binary tree as follows:

Inorder traversal first visits the left subtree, then the root, then its right subtree;
Preorder traversal first visits the root, then its left subtree, then its right subtree.
For example, if tree looks like this:

	1
   / \
  2   3
 /   / \
4   5   6
then the traversals will be as follows:

Inorder traversal: [4, 2, 1, 5, 3, 6]
Preorder traversal: [1, 2, 4, 3, 5, 6]
Given the inorder and preorder traversals of a binary tree t, but not t itself, restore t and return it.

Example

For inorder = [4, 2, 1, 5, 3, 6] and preorder = [1, 2, 4, 3, 5, 6], the output should be
restoreBinaryTree(inorder, preorder) = {
	"value": 1,
	"left": {
		"value": 2,
		"left": {
			"value": 4,
			"left": null,
			"right": null
		},
		"right": null
	},
	"right": {
		"value": 3,
		"left": {
			"value": 5,
			"left": null,
			"right": null
		},
		"right": {
			"value": 6,
			"left": null,
			"right": null
		}
	}
}
For inorder = [2, 5] and preorder = [5, 2], the output should be
restoreBinaryTree(inorder, preorder) = {
	"value": 5,
	"left": {
		"value": 2,
		"left": null,
		"right": null
	},
	"right": null
}*/

int findIndexLeftInorder(std::vector<int>& inorder, int in, int pre) {
	while (inorder[in] != pre)
		in++;
	return in;
}

Tree<int>* createNode(std::vector<int>& inorder, std::vector<int>& preorder, int idx, int indEnd) {
	static int idxPre = 0;
	if (idx > indEnd)
		return nullptr;

	Tree<int>* t = new Tree<int>(preorder[idxPre++]);

	if (idx == indEnd)
		return t;

	int inIndex = findIndexLeftInorder(inorder, idx, t->value);

	t->left = createNode(inorder, preorder, idx, inIndex - 1);
	t->right = createNode(inorder, preorder, inIndex + 1, indEnd);
	return t;
}

Tree<int>* restoreBinaryTree(std::vector<int> inorder, std::vector<int> preorder) {
	Tree<int>* t = nullptr;
	int end = inorder.size() - 1;
	int idx = 0;
	return createNode(inorder, preorder, idx, end);
}

/*You have two arrays of strings, words and parts. Return an array that contains the strings from words, modified so that any occurrences of the substrings from parts are surrounded by square brackets [], following these guidelines:

If several parts substrings occur in one string in words, choose the longest one. If there is still more than one such part, then choose the one that appears first in the string.

Example

For words = ["Apple", "Melon", "Orange", "Watermelon"] and parts = ["a", "mel", "lon", "el", "An"], the output should be
findSubstrings(words, parts) = ["Apple", "Me[lon]", "Or[a]nge", "Water[mel]on"].

While "Watermelon" contains three substrings from the parts array, "a", "mel", and "lon", "mel" is the longest substring that appears first in the string.*/


std::string::size_type KMP(const std::string& S, int begin, const std::string& pattern)
{
	std::vector<int> pf(pattern.length());
	pf[0] = 0;
	for (int k = 0, i = 1; i < pattern.length(); ++i)
	{
		while ((k > 0) && (pattern[i] != pattern[k]))
			k = pf[k - 1];
		if (pattern[i] == pattern[k])
			k++;
		pf[i] = k;
	}

	for (int k = 0, i = begin; i < S.length(); ++i)
	{
		while ((k > 0) && (pattern[k] != S[i]))
			k = pf[k - 1];

		if (pattern[k] == S[i])std::cout << k << "\t" << i + 1 << "\t"; //для просмотра входов
		k++;

		if (k == pattern.length())
			return (i - pattern.length() + 1); //либо продолжаем поиск следующих вхождений

	}

	return (std::string::npos);
	std::cout << std::string::npos;
}

void insertBracket(std::string& word, int strtIdx, int width) {
	word.insert(strtIdx, 1, '[');
	word.insert(strtIdx + width + 1, 1, ']');
}

std::vector<std::string> findSubstrings(std::vector<std::string> words, std::vector<std::string> parts) {
	//std::map<std::string, int> map;
	std::unordered_map<std::string, int> map;
	for (std::string& curStr : parts) {
		for (size_t i = 1; i <= curStr.size(); i++) {
			const std::string& s = curStr.substr(0, i);
			if (i == curStr.size())
				map[curStr] = 1;
			else if (map.find(s) == map.end())
				map[s] = 0;
		}
	}

	for (auto& word : words) {
		size_t idxMaxSize = 0;
		size_t maxSize = 0;
		std::string strtmp;
		char chtmp;
		int position = -1;
		for (size_t i = 0; i < word.length(); i++) {
			for (size_t j = 1; j <= word.length() - i; j++) {		// Ширина подстроки
				const std::string& sub = word.substr(i, j);
				auto val = map.find(sub);

				if (val != map.end()) {
					if (val->second == 1) {
						if (val->first.length() > maxSize) {
							maxSize = val->first.length();
							position = i;
						}
						else if (val->first.length() == maxSize && position > i) {
							maxSize = val->first.length();
							position = i;
						}
					}
				}
				else
					break;
			}
		}
		if (position >= 0)
			insertBracket(word, position, maxSize);
	}
	return words;
}

std::vector<std::string> findSubstringsV1(std::vector<std::string> words, std::vector<std::string> parts) {
	//std::sort(parts.begin(), parts.end());
	std::map<std::string, int> map;
	for (std::string& curStr : parts) {
		for (size_t i = 0; i < curStr.size(); i++) {
			if (i == curStr.size() - 1)
				map[curStr] = 1;
			else
				map[curStr.substr(0, i)] = 0;
		}
	}

	int count = 0;
	//for (auto& it = map.begin(); it != set.end(); it++) {
	//	std::cout << *it << std::endl;
	//}
	//std::for_each(set.begin(), set.end(), []() {
	//	//count++;
	//	//std::cout << count << "stop" << std::endl;
	//});

	for (auto& word : words) {
		size_t idxMaxSize = 0;
		size_t maxSize = 0;
		std::string strtmp;
		char chtmp;
		int position = -1;
		for (size_t p = 0; p < parts.size(); p++) {
			std::string& pattern = parts[p];

			std::vector<int> pf(pattern.length());
			pf[0] = 0;
			for (int k = 0, i = 1; i < pattern.length(); ++i)
			{
				while ((k > 0) && (pattern[i] != pattern[k]))
					k = pf[k - 1];
				if (pattern[i] == pattern[k])
					k++;
				pf[i] = k;
			}
			int k = 0;
			for (size_t i = 0; i < word.length(); i++) {
				//if (word == "uprise" && pattern == "se")
					//std::cout << "stop" << std::endl;
				//int j = 0;
				//while (i + j < word.size() && j < parts[k].size() && word[i + j] == parts[k][j])
				//	j++;
				while ((k > 0) && (pattern[k] != word[i]))
					k = pf[k - 1];
				if (pattern[k] == word[i])
					k++;

				if (k > 0 && k == pattern.length()) {
					if (k > maxSize) {
						maxSize = pattern.length();
						strtmp = pattern;
						position = i - pattern.length() + 1;
						chtmp = word[i];
					}
					else if (k == maxSize && position > i) {
						maxSize = pattern.length();
						strtmp = pattern;
						chtmp = word[i];
						position = static_cast<int>(i - pattern.length() + 1);

					}
				}
			}
		}
		if (position == word.size())
			std::cout << "stop";
		if (position >= 0)
			insertBracket(word, position, maxSize);
	}
	return words;
}


/*A tree is considered a binary search tree (BST) if for each of its nodes the following is true:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and the right subtrees must also be binary search trees.
Removing a value x from a BST t is done in the following way:

If there is no x in t, nothing happens;
Otherwise, let t' be a subtree of t such that t'.value = x.
If t' has a left subtree, remove the rightmost node from it and put it at the root of t';
Otherwise, remove the root of t' and its right subtree becomes the new t's root.
For example, removing 4 from the following tree has no effect because there is no such value in the tree:

	5
   / \
  2   6
 / \   \
1   3   8
	   /
	  7
Removing 5 causes 3 (the rightmost node in left subtree) to move to the root:

	3
   / \
  2   6
 /     \
1       8
	   /
	  7
And removing 6 after that creates the following tree:

	3
   / \
  2   8
 /   /
1   7
You're given a binary search tree t and an array of numbers queries. Your task is to remove queries[0], queries[1], etc., from t, step by step, following the algorithm above. Return the resulting BST.

Example

For

t = {
	"value": 5,
	"left": {
		"value": 2,
		"left": {
			"value": 1,
			"left": null,
			"right": null
		},
		"right": {
			"value": 3,
			"left": null,
			"right": null
		}
	},
	"right": {
		"value": 6,
		"left": null,
		"right": {
			"value": 8,
			"left": {
				"value": 7,
				"left": null,
				"right": null
			},
			"right": null
		}
	}
}
and queries = [4, 5, 6], the output should be

deleteFromBST(t, queries) = {
	"value": 3,
	"left": {
		"value": 2,
		"left": {
			"value": 1,
			"left": null,
			"right": null
		},
		"right": null
	},
	"right": {
		"value": 8,
		"left": {
			"value": 7,
			"left": null,
			"right": null
		},
		"right": null
	}
}
*/

Tree<int>* cutMin(Tree<int>* t) {
	if (t->left->left == nullptr) {
		Tree<int>* node = t->left;
		t->left = nullptr;
		return node;
	}
	cutMin(t->left);
}

Tree<int>* cutMax(Tree<int>* t) {
	if (t->right->right == nullptr) {
		Tree<int>* node = t->right;
		t->right = nullptr;
		return node;
	}
	cutMax(t->right);
}

Tree<int>* searchParentNode(Tree<int>* t, int value) {
	if (t == nullptr)
		return nullptr;
	Tree<int>* node;
	if (value <= t->value)
		node = t->left;
	else
		node = t->right;

	while (node && node->value != value) {
		t = node;
		if (value <= node->value)
			node = node->left;
		else
			node = node->right;
	}

	if (node && node->value == value)
		return t;
	return nullptr;
}

/* Нужно найти который узел будем вставлять на место удалённого, начинаем поиск с лева(максимальные все подходят) и справа(минимальные) BST*/
Tree<int>* delNode(Tree<int>* t) {
	//std::cout << "delete current node" << std::endl;
	//printTree(t);
	//if (t->value == 926273575) {
	//	printTree(t, 5);
	//	std::cout << "stop" << std::endl;
	//}

	Tree<int>* node;
	if (t->left == nullptr) {
		node = t->right;
		delete t;
	}
	else if (t->left->right == nullptr) {
		node = t->left;
		node->right = t->right;
		delete t;
	}
	else {
		node = cutMax(t->left);
		node->left = t->left;
		node->right = t->right;
		delete t;
	}
	return node;
}

Tree<int>* deleteNode(Tree<int>* t, int value) {
	if (t->value == value) 
		t = delNode(t);
	else {
		Tree<int>* parendNodeToDelete = searchParentNode(t, value);
		if (parendNodeToDelete == nullptr)
			return t;
		if (value <= parendNodeToDelete->value) 
			parendNodeToDelete->left = delNode(parendNodeToDelete->left);
		else 
			parendNodeToDelete->right = delNode(parendNodeToDelete->right);
	}
	return t;
}

Tree<int>*_findMax(Tree<int>* n)
{
	if (n == NULL)
		return NULL;
	while (n->right)
		n = n->right;
	return n;
}

Tree<int>* _removeMax(Tree<int>* t) {
	if (t->right == nullptr)
		return t->left;
	else
		t->right = _removeMax(t->right);
	return t;
}

void _remove(Tree<int>*&t, int val) {
	if (t == nullptr)
		return;
	if (val < t->value)
		_remove(t->left, val);
	else if (val > t->value)
		_remove(t->right, val);
	else {
		if (t->left == nullptr && t->right == nullptr) {
			t = nullptr;
			return;
			//Tree<int>* old = t;
			//t = old->right;
			//delete old;
		}
		else if (t->left == nullptr) {
			t = t->right;
			//Tree<int>* old = t;
			//t = old->left;
			//delete old;
		}
		else {
			Tree<int>* maxLeft = _findMax(t->left);
			t->value = maxLeft->value;
			_removeMax(t->left);
		}
	}
}

Tree<int>* deleteFromBST(Tree<int>* t, std::vector<int> queries) {


	for (auto& i : queries) {
		if (t == nullptr)
			return t;
		//std::cout << "delete N=" << i << std::endl;
		//t = deleteNode(t, i);
		_remove(t, i);
		//printTree(t);
		//std::cout << "-------" << std::endl;
	}
	return t;
}

int countNodes(Tree<int>* t, int& counter) {
	if (t != nullptr) {
		countNodes(t->left, counter);
		countNodes(t->right, counter);
		counter++;
	}
	return counter;
}

void checkSequenceTree(Tree<int>* t, int& value) {
	if (t == nullptr)
		return;
	if (t->left)
		checkSequenceTree(t->left, value);

	if (value >= t->value)
		std::cout << "stop" << std::endl;
	value = t->value;

	if (t->right)
		checkSequenceTree(t->right, value);
}

int minElementTree(Tree<int>* t) {
	while (t->left)
		t = t->left;
	return t->value;
}

void treeToArray(Tree<int>* t, std::vector<int>& v) {
	if (t == nullptr)
		return;
	if (t->left)
		treeToArray(t->left, v);
	v.push_back(t->value);
	if (t->right)
		treeToArray(t->right, v);
}

bool checkRepeatValueTree(Tree<int>* t) {
	std::vector<int> v;
	treeToArray(t, v);
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size() - 1; j++)
			if (v[i] == v[j])
				return true;
	}
	return false;
}

int main()
{
	std::string* strTree = loadStringJson("..\\..\\..\\data\\test-9.json");
	//for (int i = 0; i < 11; i++) {
		//std::cout << "N=" << i << std::endl;
		Tree<int>* t = strJsonToTree(loadStringJson("..\\..\\..\\data\\tree1.json"));
		//printTree(t);
		printTree(t);
		t = deleteFromBST(t, { 10 });
		printTree(t);
		std::cout << "------------------------------------------------------------------------------------------------------------------" << std::endl;
	//}


	std::vector<int> values;
	Tree<int>* tree;
	Tree<int>* treeCheck;
	Document d;

	d.Parse(strTree->c_str());
	if (d.IsObject()) {
		for (auto& j_input : d.GetObject()) {
			std::string name = j_input.name.GetString();
			if (name == "input") {
				for (auto& it_t : j_input.value.GetObject()) {
					std::string key = it_t.name.GetString();
					if (key == "t") {
						StringBuffer sb;
						Writer<StringBuffer> writer(sb);
						it_t.value.Accept(writer);
						std::string news = sb.GetString();
						tree = strJsonToTree(&news);
					}
					if (key == "queries") {
						for (auto& it_values : it_t.value.GetArray()) {
							values.push_back(it_values.GetInt());
						}
					}
				}
			}
			if (name == "output") {
				StringBuffer sb;
				Writer<StringBuffer> writer(sb);
				j_input.value.Accept(writer);
				std::string news = sb.GetString();
				treeCheck = strJsonToTree(&news);

			}
		}
	}

	std::stack<Tree<int>*> stackTmp({ tree });
	while (!stackTmp.empty()) {
		Tree<int>* t = stackTmp.top();
		stackTmp.pop();
		//if (t->value == 926368913) {
		if (t->value == 926563538) {
			printTree(t, 5);
		}
		if (t->left) {
			stackTmp.push({ t->left });
			if (t->right)
				stackTmp.push({ t->right });
		}

	}

	//int lastValue = minElementTree(tree)-1;
	//checkSequenceTree(tree, lastValue);
	//std::cout << std::boolalpha << checkRepeatValueTree(tree);

	printTree(tree, 6);
	std::cout << "-----------------------------------------------------" << std::endl;
	tree = deleteFromBST(tree, values);

	//lastValue = minElementTree(tree) - 1;
	//checkSequenceTree(tree, lastValue);

	//std::stack<Tree<int>*> stackV2({ tree });
	//while (!stackV2.empty()) {
	//	Tree<int>* t = stackV2.top();
	//	stackV2.pop();
	//	if (lastValue >= t->value)
	//		std::cout << "stop" << std::endl;
	//	if (t->left)
	//		stackV2.push(t->left);
	//	if (t->right)
	//		stackV2.push(t->right);
	//	lastValue = t->value;
	//}

	int count = 0;
	std::cout << "count nodes tree " << countNodes(tree, count) << std::endl;
	count = 0;
	std::cout << "count nodes treeCheck " << countNodes(treeCheck, count) << std::endl;

	

	std::stack<std::pair<Tree<int>*, Tree<int>*>> stack;
	stack.push({ tree, treeCheck });
	count = 0;
	while (!stack.empty()) {
		count++;
		const auto [t_my, t_check] = stack.top();
		stack.pop();
		if (!t_my && !t_check)
			continue;
		if (t_my->value == t_check->value) {
			if (t_my->left == nullptr && t_my->left != t_check->left) {
				//std::cout << "stop" << std::endl;
				return -1;
			}
			stack.push({ t_my->left, t_check->left });
			if (t_my->right == nullptr && t_my->right != t_check->right) {
				//std::cout << "stop" << std::endl;
				return -1;
			}
			stack.push({ t_my->right, t_check->right });
		}
		else {
			printTree(t_my, 5);
			printTree(t_check, 5);
			std::cout << "stop" << std::endl;
			return -1;
		}
	}



	//std::string* test = loadStringJson("..\\..\\..\\data\\too_vectors_strings.json");

	//std::vector<std::string> words, parts, output;
	//auto json = json::parse(*test);
	//for (auto& item : json.items()) {
	//	std::cout << item.key() << std::endl;
	//	if (item.key() == "input") {
	//		for (auto& j_input : item.value().items()) {
	//			std::cout << j_input.key() << std::endl;
	//			if (j_input.key() == "words") {
	//				words.reserve(j_input.value().size());
	//				for (auto& j_words : j_input.value().items())
	//					words.push_back(j_words.value());
	//			}
	//			if (j_input.key() == "parts") {
	//				parts.reserve(j_input.value().size());
	//				for (auto& j_parts : j_input.value().items())
	//					parts.push_back(j_parts.value());
	//			}

	//		}
	//	}
	//	if (item.key() == "output") {
	//		for (auto& j_output : item.value().items())
	//			output.push_back(j_output.value());
	//	}
	//}
	//std::vector<std::string> result = findSubstrings(words, parts);
	//for (size_t i = 0; i < result.size(); i++) {
	//	if (result[i] != output[i]) {
	//		std::cerr << "error " << result[i] << " " << output[i] << std::endl;
	//		throw;
	//	}
	//}


	//map = json.getObjects();
	//JSONObject jobj = json.getJsonObject();
	//for (auto& item : *map) {
	//	std::cout << item.first << " " << std::endl;
	//	if (item.first == "input") {
	//		std::map<std::string, JSONObject>* mapInput;
	//		mapInput = json.getObjects(item.second.idxStartValue, item.second.end);
	//		std::cout << "stop";
	//	}
	//}
	//for (auto& str : res)
	//	std::cout << str << std::endl;
	//Tree<int>* t = strJsonToTree(loadStringJson("..\\..\\..\\data\\tree1.json"));
	//printTree(t);
	//std::cout << std::endl;
	//Tree<int>* t2 = strJsonToTree(loadStringJson("..\\..\\..\\data\\tree2.json"));
	//std::vector<int> v1;
	//std::vector<int> v2;
	//loadTooVectors(v1, v2, "..\\..\\..\\data\\too_vectors.json");
	//std::vector<int> v1({ 4, 2, 1, 5, 3, 6 });
	//std::vector<int> v2({ 1, 2, 4, 3, 5, 6 });

	//Tree<int>* tree = restoreBinaryTree(v1, v2);
	//printTree(tree);

	//std::cout << std::boolalpha << isSubtree(t, t2);

	//std::cout << kthSmallestInBST(t, 4);

	//std::cout << findProfession(4, 6);

	//std::cout << std::boolalpha << isTreeSymmetric(t);
	//std::cout << std::boolalpha << hasPathWithGivenSum(t, 7);
	//std::cout << std::filesystem::current_path();
	//hashtables();
	//testArcade();
	//linkedlistImpl();
	return 0;
}

