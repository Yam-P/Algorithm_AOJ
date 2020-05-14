#include <iostream>
#include <algorithm>
#include <string.h>

// JUMPGAME
#define FOR(i, n) for(int i = 0; i < N; ++i)
using namespace std;
#define MAX_SIZE (100)
int N;
int board[MAX_SIZE][MAX_SIZE];
long long cache[MAX_SIZE][MAX_SIZE];

long long jump (int y, int x) {
    if (y >= N || x >= N) return 0;
    if (board[y][x] == 0) return 1;

    long long &ret = cache[y][x];
    if (ret != -1) {
        //cout << "repeated case!!" << "\n";
        return ret;
    }

    long long goDown  = jump(y + board[y][x], x);
    long long goRight = jump(y, x + board[y][x]);

    // 밑/오른쪽으로 가는 경우가 있으면 모두 합
    ret = goDown + goRight; 

    return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    int C;
    cin >> C;

    while(C--) {
        cin >> N;
        memset(board, -1, sizeof(board));
        memset(cache, -1, sizeof(cache));
        FOR(j, N) {
            FOR(i, N) {
                cin >> board[j][i];
            }
        }
        
        if (jump(0, 0)) cout << "YES\n";
        else cout << "NO\n"; 
    }
    
    return 0;
}