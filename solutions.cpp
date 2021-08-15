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
		for (int j = 0; j < nums.size() - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				nums[j] += nums[j + 1];
				nums[j + 1] = nums[j] - nums[j + 1];
				nums[j] -= nums[j + 1];
			}
		}
	}
	return nums[nums.size() - k];
}

/*Given an absolute file path (Unix-style), shorten it to the format /<dir1>/<dir2>/<dir3>/....

Here is some info on Unix file system paths:

/ is the root directory; the path should always start with it even if it isn't there in the given path;
/ is also used as a directory separator; for example, /code/fights denotes a fights subfolder in the code folder in the root directory;
this also means that // stands for "change the current directory to the current directory"
. is used to mark the current directory;
.. is used to mark the parent directory; if the current directory is root already, .. does nothing.
Example

For path = "/home/a/./x/../b//c/", the output should be
simplifyPath(path) = "/home/a/b/c".

Here is how this path was simplified:
* /./ means "move to the current directory" and can be replaced with a single /;
* /x/../ means "move into directory x and then return back to the parent directory", so it can replaced with a single /;
* // means "move to the current directory" and can be replaced with a single /.*/

void goParendDir(std::string& s, size_t& idx) {
	int seqMax = 2;
	if (idx == 1)
		seqMax = 1;
	size_t seq = 0;
	size_t counter = 1;
	for (;; counter++) {
		if (s[idx] == '/') {
			seq++;
			if (seq == seqMax)
				break;
		}
		--idx;
	}
	s.erase(idx, counter + 1);
}

void checkPath(std::string& s) {
	if (!s.empty() && s.at(0) != '/')
		s.insert(0, 1, '/');
}

std::string simplifyPath(std::string path) {
	if (!path.empty() && path.at(0) != '/')
		path.insert(0, 1, '/');
	for (size_t i = 0; i < path.length() - 1; i++)
		if (path[i] == '/' && path[i + 1] == '/') {
			path.erase(i + 1, 1);
			i--;
		}

	for (size_t i = 0; i < path.length(); i++) {
		char ch = path.at(i);
		if (path.at(i) == '.') {
			if (i + 1 < path.length() && path.at(i + 1) == '.') {
				goParendDir(path, i);
			}
			else if (i + 1 < path.length() && path.at(i + 1) == '/') {
				path.erase(i, 2);
				i = i - 1;
			}
		}
		else if (path.at(i) == '/') {
		}
	}
	if (path.length() != 1 && path.at(path.length() - 1) == '/')
		path.erase(path.length() - 1, 1);
	return path;
}

/*Given an encoded string, return its corresponding decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is repeated exactly k times. Note: k is guaranteed to be a positive integer.

Note that your solution should have linear complexity because this is what you will be asked during an interview.

Example

For s = "4[ab]", the output should be
decodeString(s) = "abababab";

For s = "2[b3[a]]", the output should be
decodeString(s) = "baaabaaa";

For s = "z1[y]zzz2[abc]", the output should be
decodeString(s) = "zyzzzabcabc".*/

void squareBracket(std::string& s, size_t& idx) {
	int counter = 0;
	std::string sDigit;
	for (; idx > 0; idx--) {
		if (std::isdigit(s[idx-1])) {
			sDigit.insert(0, 1, s[idx-1]);
		}
		else
			break;
	}
	s.erase(idx, sDigit.length());
	int digit = 1;
	if (!sDigit.empty())
		digit = std::stoi(sDigit);

	size_t mark1 = idx;
	size_t mark2 = mark1;
	size_t seq_squar = 0;
	for (; mark2 < s.length(); mark2++) {
		if (s[mark2] == ']') {
			s.erase(mark2, 1);
			break;
		}
		else if (s[mark2] == '[') {
			seq_squar++;
			if (seq_squar >= 2) {
				squareBracket(s, mark2);
				mark2--;
				continue;
			}
			s.erase(mark2, 1);
			mark2--;
		}
	}
	size_t seek = mark2;
	std::string suf = s.substr(mark1, mark2 - mark1);
	for (size_t i = 0; i < digit - 1; i++) {
		s.insert(seek, suf);
		seek += mark2 - mark1;
	}
}

std::string decodeString(std::string s) {
	for (size_t i = 0; i < s.length(); i++) {
		switch (s[i])
		{
		case '[':
			squareBracket(s, i);
			break;
		default:
			break;
		}
	}
	return s;
}


int main()
{
	std::cout << decodeString("2[20[bc]31[xy]]xd4[rt]") << std::endl;

	//std::cout << simplifyPath("folder/subfolder/subsubfolder/.//../anotherfolder/file.txt");

	//std::cout << kthLargestElement({ 7, 6, 5, 4, 3, 2, 1 }, 2);

	//testTrees();
	//hashtables();
	//testArcade();
	//linkedlistImpl();
	return 0;
}

