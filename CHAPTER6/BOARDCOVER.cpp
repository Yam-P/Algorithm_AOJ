#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF (987654321)
#define MAX_SIZE (21)
int H, W;
vector<string> boardIn;
int covered[MAX_SIZE][MAX_SIZE];

struct block{
    int y, x;
};

// type[n][m] n번째 블록 m번 좌표
block blockType[4][3] = {{{0, 0}, {1, -1}, {1, 0}},
                         {{0, 0}, {1, 0}, {1, 1}},
                         {{0, 0}, {0, 1}, {1, 1}},
                         {{0, 0}, {0, 1}, {1, 0}}};

// 블럭을 놓는 경우 / 제거하는 경우
bool set(int y, int x, int type, int delta) {
    bool ok = true;
    for (int idx = 0; idx < 3; ++idx) {
        int ny = y + blockType[type][idx].y;
        int nx = x + blockType[type][idx].x;
        // 얘를 그냥 y, x로 해서 시간 많이 버렸다..
        if (ny < 0 || ny >= H || nx < 0 || nx >= W) ok = false;
        else if ((covered[ny][nx] += delta) > 1) ok = false;
    }
    
    vector<string> observer(H, string(W, ' '));
    FOR(j, H) {
        FOR(i, W) {
            if (covered[j][i] == 1) observer[j][i] = '#';
            else if (covered[j][i] == 2) observer[j][i] = '&';
            else if (covered[j][i] == -1) observer[j][i] = '*';
            else observer[j][i] = '.'; 
        }
    }

    return ok;
}

// 덮는 방법 수 반환
int covering() {
    // 빈칸 찾기
    int firstY = -1;
    int firstX = -1;
    for(int j = 0; j < H; ++j) {
        for(int i = 0; i < W; ++i) {
            if (covered[j][i] == 0) {
                firstY = j;
                firstX = i;
                break;
            }
        }
        if (firstY != -1) break;
    }
    // 기저사례: board가 꽉 찬 경우 만족하므로 경우 1 추가
    if (firstY == -1) return 1;

    int ret = 0;
    for (int type = 0; type < 4; ++type) {
        if (set(firstY, firstX, type, 1)) {
            ret += covering();
        }
        set(firstY, firstX, type, -1);
    }

    return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int C;
    cin >> C;
    
    FOR(c, C) {
        cin >> H >> W;
        boardIn.resize(H);
        memset(covered, 0, sizeof(covered));
        int zeroCount = 0;
        FOR(j, H) {
            cin >> boardIn[j];
            FOR(i, W) {
                if (boardIn[j][i] == '#') covered[j][i] = 1;
                else {
                    covered[j][i] = 0;
                    zeroCount++;
                }
            }
        }
        // 가지치기
        if (zeroCount % 3 != 0) {
            cout << 0 << "\n";
        } 
        else {
            cout << covering() << "\n";
        }
    }
    
	return 0;
 }