#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)

vector<int> h;
int N;

int makeFence(int beg, int end) {
    // 분해과정: 높이 너비 1인경우 높이가 넓이
    if (beg == end) return h[beg];

    int mid = (beg + end) / 2;
    int ret = 0;

    int leftH  = makeFence(beg, mid);
    int rightH = makeFence(mid + 1, end);

    // leftH/rightH = [beg ~ mid]/[mid + 1 ~ end]까지 최대 넓이

    // 병합과정1 - [beg ~ mid], [mid + 1 ~ end] 중 더 큰 넓이
    ret = max(ret, max(leftH, rightH));

    // 병합과정2 - 중앙 기준으로 너비 2인 경우
    int left = mid;
    int right = mid + 1;
    int minHeight = min(h[left], h[right]);
    ret = max(ret, minHeight * 2);

    // 병합과정3 - 우 혹은 좌로 넓혀가기
    // 오른쪽 울타리가 왼쪽 울타리보다 높으면 확장하되, 높이는 최소 높이로
    while (left > beg || right < end) {
        if ((right < end) && (left == beg || h[left -  1] < h[right + 1])) {
            right += 1;
            minHeight = min(minHeight, h[right]);
        }
        else {
            left -= 1;
            minHeight = min(minHeight, h[left]);
        }
        ret = max(ret, minHeight * (right - left + 1));
    }

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

    int C;
    cin >> C;
    FOR (c, C) {
        cin >> N;
        h.resize(N);
        FOR(i, N) {
            cin >> h[i];
        }
        cout << makeFence(0, N - 1) << "\n";
    }
    
	return 0;
 }