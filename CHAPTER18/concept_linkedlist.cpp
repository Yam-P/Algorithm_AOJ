#include <iostream>

using namespace std;

// linked list template

struct ListNode{
	int element;
	ListNode *prev, *next;
};

void deleteNode(ListNode *node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

void recoverNode(ListNode *node) {
	node->prev->next = node;
	node->next->prev = node;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	ListNode *head = new ListNode;
	head->element = 4;
	ListNode *node1 = new ListNode;
	node1->element = 5;
	ListNode *node2 = new ListNode;
	node2->element = 6;

	head->next = node1;
	node1->prev = head;
	node1->next = node2;
	node2->prev = node1;

	deleteNode(node1);
	recoverNode(node1);
	

	return 0;
}
