// solutions.cpp : Defines the entry point for the application.
//

#include "solutions.h"
#include "arrays.h"
#include "linkedlist.h"
#include "hashtables.h"
#include "arcade.h"

template<typename T>
struct Tree {
	Tree(const T& v = 0) : value(v), left(nullptr), right(nullptr) {}
	T value;
	Tree* left;
	Tree* right;
};

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


int main()
{
	//std::cout << test(8);
	Tree<int>* t = strJsonToTree(loadStringJson("..\\..\\..\\data\\hasPathWithGivenSum_test1.json"));

	std::cout << findProfession(4, 6);

	//std::cout << std::boolalpha << isTreeSymmetric(t);
	//std::cout << std::boolalpha << hasPathWithGivenSum(t, 7);
	//std::cout << std::filesystem::current_path();
	//hashtables();
	//testArcade();
	//linkedlistImpl();
	return 0;
}

