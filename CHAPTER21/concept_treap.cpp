#include <iostream>

using namespace std;

// Treap 구현

// key type이 변할 경우 int 대신 바꿔주기
typedef int KeyType;

struct Node {
	KeyType key;

	Node *left, *right;
	int priority, size;

	Node(const KeyType &_key)
	: key(_key), priority(rand()), size(1), left(NULL), right(NULL) 
	{}
	
	void calcSize() {
		size = 1; // root의 사이즈
		// left 혹은 right의 subtree가 존재한다면 size가 증가
		if (left)  size += left->size;
		if (right) size += right->size;
		
	}

	void setLeft(Node *newLeft) {
		left = newLeft;
		calcSize();
	}

	void setRight(Node *newRight) {
		right = newRight;
		calcSize();
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node *root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	// root의 key 값이 쪼개는 기준 key 값보다 작은 경우
	// 오른쪽을 쪼개야한다.
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	else {
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(root, ls.first);
	}
}

Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key) 
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}

Node* merge(Node* a, Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	else {
		a->setRight(merge(a->right, b));
		return a;
	}
}

Node* kth(Node* root, int KeyType) {
	int leftSize = 0;
	if (k != 0) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);

}

int countLessThan(Node* root, KeyType key) {
	if (root == NULL) return 0;
	if (root->key >= key) 
		return countLessThan(root->left, key);
	int leftSize = root->left ? root->left->size : 0;
	return leftSize + 1 + countLessThan(root->right, key);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	Node *root = new Node(0);	
	root->setLeft(new Node(1));
	root->setRight(new Node(2));

	delete root;

	return 0;
}
