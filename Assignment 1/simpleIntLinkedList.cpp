#include <iostream>
#include "simpleIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}

void List::insertHead(int n)
{
	ListNode *aNewNode = new ListNode(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

void List::removeHead()
{
	if (_size > 0) {
		ListNode *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

void List::print() {
    ListNode *ptr = _head;
    while (ptr != NULL) {
        cout << ptr->_item << " ";
        ptr = ptr->_next;
    }
    cout << endl; // modify this
}

bool List::exist(int n) {
    ListNode* ptr = _head;
    while (ptr != NULL) {
        if (ptr->_item == n) {
            return 1;
        }
        ptr = ptr->_next;
    }
    return 0; // modify this
}

int List::headItem()
{
	return 0; // modify this
}

List::~List()
{
	while (_size != 0)
		removeHead();
};

