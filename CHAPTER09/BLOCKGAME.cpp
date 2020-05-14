#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

// BLOCKGAME

inline int cell(int y, int x) { return 1 << (y * 5 + x); }

vector<int> moves;
void preCalc() {
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 4; ++x) {
			moves.push_back(cell(y, x) + cell(y, x + 1));	
			moves.push_back(cell(x, y) + cell(x + 1, y));
		}
	}

	for (int y = 0; y < 4; ++y) {
		for (int x = 0; x < 4; ++x) {

			vector<int> cells;
			for (int dy = 0; dy < 2; ++dy) {
				for (int dx = 0; dx < 2; ++dx) {
					cells.push_back(cell(y + dy, x + dx));
				}
			}
			int square = cells[0] + cells[1] + cells[2] + cells[3];

			for (int i = 0; i < cells.size(); ++i) {
				moves.push_back(square - cells[i]);
			}
		}
	}
}

char cache[1 << 25];
char play(int board) {
	char &ret = cache[board];
	if (ret != -1) {
		//printf("repeated case!\n");
		return ret;
	}
	ret = 0;
	for (int k = 0; k < moves.size(); ++k) {
		// and 연산 결과가 0이 아니면 채울 수 없다는 뜻.
		if (board & moves[k]) continue;
		// 내가 board | moves[k]를 넣고 상대에게 판을 넘긴 경우.
		// 상대가 놓을 수 없어서 0을 반환하면 내가 이긴 것.
		if (!play(board | moves[k])) {
			ret = 1;
			break;
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int C;
	cin >> C;

	preCalc();
	while (C-- > 0) {
		int board = 0;
		for (int j = 0; j < 5; ++j) {
			for (int i = 0; i < 5; ++i) {
				char placed;
				cin >> placed;
				if (placed == '#') board += cell(j, i); 
			}
		}	

		memset(cache, -1, sizeof(cache));
		if (play(board)) cout << "WINNING\n";
		else cout << "LOSING\n";
	}

	return 0;
}
