#include <iostream>

using namespace std;

// treap test

typedef int KeyType;

struct Node { // root node 생성
	KeyType key;
	int size, priority;

	Node* left ;
	Node* right;
	
	Node (const KeyType &_key) :
	key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

	void calcSize() {
		size = 1; // 기본 root 노드
		if (left) size  += left->size;
		if (right) size += right->size;
	}

	void setLeft(Node* newLeft) {
		left = newLeft;
		calcSize();
	}
	
	void setRight(Node* newRight) {
		right = newRight;
		calcSize();
	}
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	
	// root 오른쪽에서 끊는 경우
	if (root->key < key) {
		NodePair rs = split(root->right, key);	
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	else {
		NodePair ls = split(root->left, key);
		root->setLeft(ls.second);
		return NodePair(ls.first, root);
	}
}

Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;

	// root 보다 priority가 크면 쪼개기
	if (root->priority <= node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	} 
	
	else if (root->key < node->key) {
		root->setRight(insert(root->right, node));
	}
	else {
		root->setLeft(insert(root->left, node));
	}
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

Node* erase(Node* root, KeyType key) {
	if (root == NULL) return root;

	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key) {
		root->setLeft(erase(root->left, key));
	}
	else {
		root->setRight(erase(root->right, key));
	}
	return root;
}

Node* kth(Node* root, int k) {
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
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

	Node* root = new Node(7);
	// split test
	//root->setLeft(new Node(6));
	//root->setRight(new Node(9));
	//root->right->setRight(new Node(11));
	//root->right->setLeft(new Node(8));
	//NodePair test = split(root, 10);

	// insert test
	//root = insert(root, new Node(6));
	//root = insert(root, new Node(8));
	//root = insert(root, new Node(9));
	//root = insert(root, new Node(4));

	// merge test -> priority check
	//Node* a = new Node(1);
	//a = insert(a, new Node(2));
	//Node* b = new Node(3);
	//Node* test = merge(a, b);

	// erase test
	//Node* root2 = new Node(6);
	//root2 = insert(root2, new Node(3));
	//root2 = insert(root2, new Node(9));
	//root2 = insert(root2, new Node(7));
	//root2 = insert(root2, new Node(11));
	//root2 = erase(root2, 9);
	return 0;
}
