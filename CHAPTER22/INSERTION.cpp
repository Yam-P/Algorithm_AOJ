#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// INSERTION. using treap algorithm

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

	if (root->priority < node->priority) {
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

int N;
const int MAX_SIZE = 100;
int shifted[MAX_SIZE];
int A[MAX_SIZE];

void solve() {
	Node* candidates = NULL;
	
	srand(time(NULL));
	for (int i = 0; i < N; ++i) {
		// 1, 2, 3... 차례로 넣으며 트리 생성.
		candidates = insert(candidates, new Node(i + 1));
	}
	int treeSize = candidates->size;
	for (int i = N - 1; i >=  0; --i) {
		int larger = shifted[i];
		Node* node = kth(candidates, i + 1 - larger);
		A[i] = node->key;
		candidates = erase(candidates, node->key);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> N;
	
	for (int i = 0; i < N; ++i) {
		cin >> shifted[i];
	}
	solve();

	for (int i = 0; i < N; ++i) {
		cout << A[i] << " ";
	}	
	cout << "\n";

	return 0;
}
