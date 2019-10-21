#include "NodeList.h"

NodeList::NodeList() {
	head = NULL;
	tail = NULL;
}

NodeList::~NodeList() {
}

void NodeList::append(Node * node) {
	if (head == NULL) {
		head = node;
		tail = head;
	}
	else {
		tail->next = node;
		tail = node;
	}
}

void NodeList::addSorted(Node * node) {
	if (head == NULL) {
		head = node;
		tail = head;
	}
	else {
		Node * cur = head;
		Node * prev = NULL;
		while (cur != NULL) {
			if (node->f < cur->f) {
				if (cur == head) {
					node->next = head;
					head = node;
				}
				else {
					node->next = cur;
					prev->next = node;
				}
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		if (cur == NULL) {
			prev->next = node;
			tail = node;
		}
	}
}

Node * NodeList::peekHead() {
	return head;
}

Node * NodeList::removeHead() {
	Node * temp = head;
	head = head->next;
	if (temp == tail) {
		tail = NULL;
	}
	return temp;
}

Node * NodeList::getNode(Node * node) {
	Node * cur = head;
	while (cur != NULL) {
		if (cur->x == node->x && cur->y == node->y) {
			return cur;
		}
		cur = cur->next;
	}
    return NULL;
}

bool NodeList::isEmpty() {
	if (head == NULL) { return true; }
	else { return false; }
}

bool NodeList::isInList(Node * node) {
	Node * cur = head;
	while (cur) {
		if (cur->x == node->x && cur->y == node->y) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}
