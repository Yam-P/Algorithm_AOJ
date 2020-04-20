#include <iostream>
#include <vector>

using namespace std;

// the concept of insertion sort

void insertionSort(vector<int> &seq) {
	for (int i = 0; i < seq.size(); ++i) {
		int j = i;	
		while (j > 0 && seq[j - 1] > seq[j]) {
			swap(seq[j - 1], seq[j]);
			j--;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	printf("enter the size of seq and elements: \n");
	int N;
	cin >> N;
	vector<int> S(N);
	
	for (int i = 0; i < N; ++i) {
		cin >> S[i];
	}

	insertionSort(S);

	cout << "result: ";
	for (int i = 0; i < N; ++i) {
		cout << S[i] << " ";
	}
	cout << "\n";


	return 0;
}
