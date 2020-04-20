#include <iostream>
#include <list>

using namespace std;

// JOSEPHUS

void josephus(int n, int k) {
	list<int> survivors;

	for (int i = 1; i <= n; ++i) {
		survivors.push_back(i);
	}

	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		// erase 후 그 다음 iter를 반환
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();
		n--;
		
		for (int i = 0; i < k - 1; ++i) {
			++kill; // k만큼 건너 뛰기위함. iteration을 수정하기
			if (kill == survivors.end()) kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	while(C-- > 0) {
		int N, K;
		cin >> N >> K;
		josephus(N, K);
	}
	
	return 0;
}
