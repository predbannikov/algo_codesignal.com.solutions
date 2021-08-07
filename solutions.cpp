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

#define WIDTH 40
#define HALF_WIDTH (WIDTH/2)

void traversalTree(std::vector<std::string>& v, Tree<int>* tree, int lvl, int i1) {

	std::string val = std::to_string(tree->value);
	for (size_t i = i1, j = 0; i < i1 + val.size(); i++, j++)
		v[lvl * 2][i] = val[j];
	int diff;
	if (tree->left != nullptr) {
		diff = HALF_WIDTH / pow(2, lvl);
		v[(lvl * 2) + 1][i1 - diff / 2] = '/';
		traversalTree(v, tree->left, lvl + 1, i1 - diff);

	}
	if (tree->right != nullptr) {
		diff = HALF_WIDTH / pow(2, lvl);
		v[(lvl * 2) + 1][i1 + diff / 2] = '\\';
		traversalTree(v, tree->right, lvl + 1, i1 + diff);
	}
	return;
}

void printTree(Tree<int>* tree) {
	std::vector<std::string> pic(30, std::string(WIDTH, ' '));
	traversalTree(pic, tree, 1, HALF_WIDTH);
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

void makeBT(std::vector<int>::iterator& cur_it, std::vector<int>::iterator& end, Tree<int>* t) {
	if (cur_it == end)
		return;
	if (t == nullptr) {
		t = new Tree<int>(*cur_it);
		cur_it++;
		//if(cur_it)
		makeBT(cur_it, end, t);
	}
}

void fillBranch(std::vector<int>::iterator& pre, std::vector<int>::iterator& marker, Tree<int>* t) {
	if (*pre == *marker)
		return;
	pre++;
	t->left = new Tree<int>(*pre);
	fillBranch(pre, marker, t->left);
}

//void createNode(std::vector<int>::iterator& it, std::vector<int>::iterator& end, Tree<int>* t) {
//	if (it != end) {
//		t = new Tree<int>(*it);
//		fillBranch();
//		createNode(it, end, t);
//	}
//}



Tree<int>* test1(std::vector<int> &inorder, std::vector<int> &preorder) {
	static int idx = 0;
	static int idxPre = 0;
	int startIdx = idx;
	if (inorder[startIdx] != preorder[idxPre]) {
		for ( ; inorder[startIdx] != preorder[idxPre]; startIdx++);

	}
	Tree<int>* t = new Tree<int>(preorder[idxPre]);

	idx++;
	idxPre++;
	t->left = test1(inorder, preorder);
	t->right = test1(inorder, preorder);
}

Tree<int>* restoreBinaryTree(std::vector<int> inorder, std::vector<int> preorder) {
	Tree<int>* t = nullptr;
	std::vector<int>::iterator in_it = inorder.begin();
	std::vector<int>::iterator save_it = in_it;
	std::vector<int>::iterator pre_it = preorder.begin();
	if (pre_it != preorder.end())
		t = new Tree<int>(*pre_it);
	else
		return new Tree<int>();
	Tree<int>* tmpTree = t;
	while (in_it != inorder.end()) {
		while (*in_it != *pre_it)
			in_it++;
		fillBranch(pre_it, save_it, tmpTree);
		in_it++;
		pre_it++;
		if (pre_it != preorder.end())
			tmpTree->right = new Tree<int>(*pre_it);
		else
			break;
		if (in_it == inorder.end())
			break;
		save_it = in_it;
		tmpTree = tmpTree->right;
	}
	return t;
}
int main()
{
	Tree<int>* t = strJsonToTree(loadStringJson("..\\..\\..\\data\\tree1.json"));
	//printTree(t);
	std::cout << std::endl;
	Tree<int>* t2 = strJsonToTree(loadStringJson("..\\..\\..\\data\\tree2.json"));
	std::vector<int> v1;
	std::vector<int> v2;
	loadTooVectors(v1, v2, "..\\..\\..\\data\\too_vectors.json");
	Tree<int>* tree = restoreBinaryTree(v1, v2);
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

