#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

string e, digits;
int n, m;
// 15자릿수 중 1~9까지 값

// ZIMBABWE
// 중복이 없는 경우, 입력 값보다 작은 애들 출력
#if 0
bool taken[15] = {false, };
void generate(string price) {
	if (price.size() == e.size()) {
		if (price < e) cout << price << "\n";
		return;
	}
	
	for (int next = 0; next < e.size(); ++next) {
		if (!taken[next]) {
			taken[next] = true;
			generate(price + digits[next], taken);
			taken[next] = false;	
		}
	} 
}
#endif

#if 0
int taken;
void generate(string price, int taken) {
	if (taken == (1 << e.size()) - 1 ) {
		if (price < e) cout << price << "\n";
		return;
	}
	
	for (int next = 0; next < e.size(); ++next) {
		// 일단, next = 0이면 무조건 진행 해야함
		if ((taken & (1 << next)) != 0) continue; 
		// 책에 나온 케이스의 여집합
		if (next > 0 && digits[next] == digits[next - 1] && (taken & (1 << (next - 1))) == 0) 
			continue;
		int nextTaken = taken | (1 << next);
		generate(price + digits[next], nextTaken);
		
	} 
}
#endif

#if 1
const int MOD = 1000000007;
int cache[1 << 14][20][2];
// index: 이전 자릿수
// mod: 이전 인덱스에서 m을 나누고 남은 값
// less: true이면 이전 index 비교에서 만들 수가 작은 값 false이면 같은 값
int price(int index, int taken, int mod, int less) {
	// 작기도 하면서 나누어 떨어지는 경우
	if (index == n) return (less && (mod == 0)) ? 1 : 0;

	int &ret = cache[taken][mod][less];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = 0; next < n; ++next) {
		if ((taken & (1 << next)) != 0) continue;
		// 이전 자릿수 계산에서 앞부분이 일치한다면, 지금 만들 자릿수는 무조건 e[index]보다 작아야 결과는 작은 값.
		if (!less && (e[index] < digits[next])) continue;
		if (next > 0 && digits[next] == digits[next - 1] && (taken & (1 << (next - 1))) == 0)
			continue;
		int nextTaken = taken | (1 << next);
		int nextMod = (mod * 10 + (digits[next] - '0')) % m;	
		// 이전 자릿수 계산에서 작게 나오는 경우, 항상 만족
		// 만약 이전 자릿수 계산에서 값이 같아 less = false가 되더라도, 지금 자릿수에서 digits[next]가 작은 경우는 작은 수로 본다.
		int nextLess = less || (e[index] > digits[next]);
		
		// 만족시키는 경우 1을 카운트
		ret += price(index + 1, nextTaken, nextMod, nextLess);
		ret %= MOD;
	}

	return ret;
}
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int c;
	cin >> c;
	while (c-- > 0) {
		cin >> e >> m;
		digits = e;
		sort(digits.begin(), digits.end()); 

		n = e.size();
		memset(cache, -1, sizeof(cache));
		//generate("", 0);
		cout << price(0, 0, 0, 0) << "\n";
	}
	
	return 0;
}

