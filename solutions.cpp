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
	for (;;counter++) {
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
			else if(i+1 < path.length() && path.at(i+1) == '/'){
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

int main()
{
	std::cout << simplifyPath("folder/subfolder/subsubfolder/.//../anotherfolder/file.txt");

	//std::cout << kthLargestElement({ 7, 6, 5, 4, 3, 2, 1 }, 2);

	//testTrees();
	//hashtables();
	//testArcade();
	//linkedlistImpl();
	return 0;
}

