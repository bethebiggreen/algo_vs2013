/*
https://www.acmicpc.net/problem/1018
M*N크기의 보드 (가로*세로)

- 0.03 Support variable M*N
- 0.02 We re-use previous result and merge to new one line which is just come up.
       For example, 0-7 is confirmed and move it to 1-8. 1-7 is investigated with previous search and only new line 8 is needed.
	   Let's implement.
	   Checking validation of marking annoying me a lot. Let's make inline function.

- 0.01 This version failed to check num of needed changes once checking other chess-table.
*/

#include <iostream>

using namespace std;
#if 1
const int MAX_N = 51;
const int TABLE_N = 8;
#else
const int MAX_N = 6;
const int TABLE_N = 2;
#endif
int tbl[MAX_N][MAX_N];

int b_bad_num[TABLE_N] = { 0, };
int w_bad_num[TABLE_N] = { 0, };

enum {
	WHITE = 0,
	BLACK,
};

const int BIG_INT = 0x7FFFFFFF;
int sol = BIG_INT;

/* 
   i is treated as row
   j is treated as column
   type lets us know what 0,0 needs. For insatance, type BLACK, it considers 0,0 has to be BLACK. Vice versa, type WHITE 0,0 has to be WHITE.
   type BLACK : BWBW , type WHITE : WBWB
                WBWB                BWBW
				BWBW                WBWB

*/		
inline bool is_it_okay(int i, int j, bool type)
{
	int supposed = -1;
	switch (type) {
	case BLACK:
		if (i % 2 == 0) { // BWBW
			if (j % 2 == 0)
				supposed = BLACK;
			else
				supposed = WHITE;
		}
		else { // WBWB
			if (j % 2 == 0)
				supposed = WHITE;
			else
				supposed = BLACK;
		}
		break;
	case WHITE:
		if (i % 2 == 0) { // WBWB
			if (j % 2 == 0)
				supposed = WHITE;
			else
				supposed = BLACK;
		}
		else { // BWBW
			if (j % 2 == 0)
				supposed = BLACK;
			else
				supposed = WHITE;
		}
		break;
	default :
		break;
	}

	return (tbl[i][j] == (bool)supposed);
}

void fill_bad_num(int offset)
{
	for (int i = 0; i < TABLE_N; i++) {
		b_bad_num[i] = 0;
		w_bad_num[i] = 0;
	}

	bool* iter = reinterpret_cast<bool*>(tbl);
	
	for (int i = 0; i < TABLE_N; i++) {
		for (int j = 0; j < TABLE_N; j++) {
			if (is_it_okay(i+offset, j, BLACK)) {
				w_bad_num[j]++;
			}
			else {
				b_bad_num[j]++;
			}
		}
	}
}

void pop_bad_num(void)
{
	for (int i = 1; i < TABLE_N; i++) {
		w_bad_num[i - 1] = w_bad_num[i];
		b_bad_num[i - 1] = b_bad_num[i];
	}
	w_bad_num[TABLE_N - 1] = 0;
	b_bad_num[TABLE_N - 1] = 0;
}

// BW
// WB
void set_last_diff(int i /*row*/, int j /*column*/)
{
	for (int offset = 0; offset < TABLE_N; offset++) {
		if (is_it_okay(i + offset, j + TABLE_N - 1, BLACK)) {
			w_bad_num[TABLE_N-1]++;
		}
		else { // SHOULD BE WHITE
			b_bad_num[TABLE_N - 1]++;
		}
	}
}

void update(void)
{
	int w_sol = 0;
	int b_sol = 0;
	for (int i = 0; i < TABLE_N; i++) {
		w_sol += w_bad_num[i];
		b_sol += b_bad_num[i];
	}

	if (sol > w_sol)
		sol = w_sol;

	if (sol > b_sol)
		sol = b_sol;
}

int do_something(int row, int col)
{
	for (int i = 0; i <= row - TABLE_N; i++) {
		fill_bad_num(i);
		update();

		for (int j = 1; j <= col - TABLE_N; j++) {
			pop_bad_num();
			set_last_diff(i, j);
			update();
		}
	}
	return sol;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int N = 0, M = 0; // N represents COL, M represents ROW, table[M][N] might be correct grammar.
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			char tmp = 0;
			cin >> tmp;
			tbl[i][j] = (tmp == 'B') ? 1 : 0;
		}
	}
	cout << do_something(M,N);
	return 0;
}