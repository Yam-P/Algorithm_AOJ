#include <iostream>
#include <vector>

using namespace std;

// BOARDCOVER using BITMASK
int H, W;

int convert(int y, int x) { return 1 << (y * W + x); }

vector<int> moves;
void preCalc() {
	for (int y = 0; y < H - 1; ++y) {
		for (int x = 0; x < W - 1; ++x) {
			
			vector<int> cells;
			for (int dy = 0; dy < 2; ++dy) {
				for (int dx = 0; dx < 2; ++dx) {
					cells.push_back(convert(y + dy, x + dx));
				}
			}
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			
			for (int i = 0; i < 4; ++i) {
				moves.push_back(square - cells[i]);
			}
		}
	}
}

int set(int board) {
	// 모두 채운 경우
	// 놓는 순서가 상관이 없네.. 망..
	if (board == ((1 << H * W) - 1)) {
		return 1;
	}

	int ret = 0;
	for (int k = 0; k < moves.size(); ++k) {
		if (board & moves[k]) continue;
		ret += set(board | moves[k]);
	}

	return ret;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> H >> W;
	int board;	
	for (int j = 0; j < H; ++j) {
		for (int i = 0; i < W; ++i) {
			char placed;
			cin >> placed;
			if (placed == '#') board += convert(j, i);
		}
	}
	
	preCalc();
	cout << set(board) << "\n";


	return 0;
}
