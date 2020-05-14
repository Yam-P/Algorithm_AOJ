#include <iostream>
#include <cstring>

using namespace std;
#define MAX_SIZE 1001
int n, m;
double cache[MAX_SIZE][MAX_SIZE];
double climb(int day, int height) {
	// 무사히 day 안에 도착한 경우
	if (day <= m && height >= n) return 1; 
	if (day == m) return 0;
	
	double &ret = cache[day][height];
	if (ret != -1) return ret;

	ret  = climb(day + 1, height + 2) * 0.75;
	ret += climb(day + 1, height + 1) * 0.25;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;
	for(int c = 0; c < C; ++c) {
		cin >> n >> m;
		for (int j = 0; j < MAX_SIZE; ++j) {
			for (int i = 0; i < MAX_SIZE; ++i) {
				cache[j][i] = -1;
			}
		}
		printf("%.10lf\n", climb(0, 0));
	}	
	return 0;
}
