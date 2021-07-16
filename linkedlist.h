#pragma once
#include "solutions.h"


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
		while (current != nullptr) {
			std::cout << current->value << " ";
			current = current->next;
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
			head = new ListNode<int>(l1->value);
			ListNode<int>* tmp = new ListNode<int>(0);
			tmp->next = l2;
			l2 = tmp;
		}
		else {
			head = new ListNode<int>(l2->value);
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

ListNode<int>* reverseNodesInKGroups(ListNode<int>* l, int k) {
	if (l != nullptr) {
		if (l->next == nullptr)
			return l;
		ListNode<int>* cur, * head, * triadBegin, * triadEnd, * tmp, * tail;
		triadEnd = cur = nullptr;
		size_t counter = 0;
		while (l != nullptr) {
			if (counter == k) {
				if (cur == nullptr) {
					head = triadBegin;
				}
				else {
					cur->next = triadBegin;
				}
				cur = triadEnd;
				triadEnd = nullptr;
				counter = 0;
			}
			else {
				if (triadEnd == nullptr) {
					tail = l;
					triadEnd = new ListNode<int>(l->value);
					triadBegin = triadEnd;
				}
				else {
					tmp = triadBegin;
					triadBegin = new ListNode<int>(l->value);
					triadBegin->next = tmp;
				}
				l = l->next;
				counter++;

			}
		}
		if (counter == k) {
			cur->next = triadBegin;
		}
		else if (counter != 0) {
			cur->next = tail;
		}
		return head;
	}
	return l;
}

ListNode<int>* rearrangeLastN(ListNode<int>* l, int n) {
	if (n == 0)
		return l;
	if (l != nullptr) {
		if (l->next != nullptr) {
			if (l->next->next != nullptr) {
				ListNode<int>* cur, * rootPart, * tmp, * seek, * head;
				head = l;
				rootPart = new ListNode<int>(l->value);
				cur = rootPart;
				int counterSeek = n;
				int counter = 0;
				seek = l;
				while (l->next != nullptr) {
					counterSeek--;
					if (counterSeek < 0)
						seek = seek->next;


					cur->next = new ListNode<int>(l->next->value); // двигаемся вперёд
					cur = cur->next;
					l = l->next;


					if (counter >= n - 1) {
						tmp = rootPart;
						rootPart = rootPart->next;
						delete tmp;
					}
					else
						counter++;

				}
				if (seek != head) {
					seek->next = nullptr;
					cur->next = head;
				}
				return rootPart;

			}
			else {
				ListNode<int>* tmp = l;
				l = l->next;
				l->next = tmp;
				l->next->next = nullptr;
			}
		}
	}
	return l;
}

void linkedlistImpl() {
	ListNode<int>* list = nullptr, * list2 = nullptr;
	std::vector<int> a{ 2, 1, 3, 5, 4};
	std::vector<int> b{ 0, 3, 5 };
	for (int i = 0; i < a.size(); i++) {
		if (list == nullptr) list = new ListNode<int>(a[i]);
		else list->push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++) {
		if (list2 == nullptr) list2 = new ListNode<int>(b[i]);
		else list2->push_back(b[i]);
	}
	ListNode<int>* list3 = rearrangeLastN(list, 2);

	list3->print();

	//while (list3 != nullptr) {
	//	std::cout << list3->value << " ";
	//	list3 = list3->next;
	//}

}