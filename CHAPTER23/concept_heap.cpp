#include <iostream>
#include <vector>

using namespace std;

// conception about heap algorithm

void push_heap(vector<int> &heap, int newValue) {
	heap.push_back(newValue);
	int idx = heap.size() - 1;
	while (idx > 0 && heap[idx] > heap[(idx - 1) / 2]) {
		swap(heap[idx], heap[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}

void pop_heap(vector<int> &heap) {
	int ret = heap[0];
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;

	while (true) {
		int left = here * 2 + 1;
		int right = here * 2 + 2;

		if (left > heap.size()) break;

		int next = here;
		if (heap[next] > heap[left]) 
			next = left;
		if (heap[next] < heap[right] && right < heap.size()) 
			next = right;
		if (heap[next] == heap[here]) 
			break; 
		
		swap(heap[here], heap[next]);
		here = next;
	}
}

int main (int artc, char **argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vector<int> heap;
	push_heap(heap, 1);
	push_heap(heap, 2);
	push_heap(heap, 3);
	push_heap(heap, 4);
	push_heap(heap, 5);
	push_heap(heap, 6);

	return 0;
}
