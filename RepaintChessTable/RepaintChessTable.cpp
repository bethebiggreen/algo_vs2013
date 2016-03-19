/*
https://www.acmicpc.net/problem/1018

This version failed to check num of needed changes once checking other chess-table.
*/
#include <iostream>

using namespace std;
const int MAX_N = 10;
const int TABLE_N = 8;

int tbl[MAX_N][MAX_N];

int b_bad_num[TABLE_N] = { 0, };
int w_bad_num[TABLE_N] = { 0, };

enum {
	WHITE = 0,
	BLACK,
};

const int BIG_INT = 0x7FFFFFFF;
int sol = BIG_INT;

int fill_bad_num(int offset)
{
	for (int i = 0; i < TABLE_N; i++) {
		b_bad_num[i] = 0;
		w_bad_num[i] = 0;
	}

	bool* iter = reinterpret_cast<bool*>(tbl);
	
	for (int i = 0; i < TABLE_N; i++) {
		for (int j = 0; j < TABLE_N; j++) {
			if (j % 2 == 0) {
				if ((i % 2 == 0) && tbl[i + offset][j] != BLACK) {
					b_bad_num[i]++;
				}
				else if ((i % 2 == 1) && tbl[i + offset][j] != WHITE) {
					b_bad_num[i]++;
				}

				if ((i % 2 == 0) && tbl[i + offset][j] != WHITE) {
					w_bad_num[i]++;
				}
				else if ((i % 2 == 1) && tbl[i + offset][j] != BLACK) {
					w_bad_num[i]++;
				}
			}
			else
			{
				if ((i % 2==0 && tbl[i + offset][j] != WHITE)) {
					b_bad_num[i]++;
				}
				else if ((i % 2 == 1) && tbl[i + offset][j] != BLACK){
					b_bad_num[i]++;
				}

				if ((i % 2 == 0 && tbl[i + offset][j] != BLACK)) {
					w_bad_num[i]++;
				}
				else if ((i % 2 == 1) && tbl[i + offset][j] != WHITE) {
					w_bad_num[i]++;
				}
			}
		}
	}

	int how_many_bad_for_b = 0;
	int how_many_bad_for_w = 0;
	for (int i = 0; i < TABLE_N; i++) {
		how_many_bad_for_b += w_bad_num[i];
		how_many_bad_for_w += b_bad_num[i];
	}
	return (how_many_bad_for_b > how_many_bad_for_w) ? how_many_bad_for_w : how_many_bad_for_b;
}

void pop_bad_num(void)
{
	for (int i = 1; i < TABLE_N - 1; i++) {
		w_bad_num[i - 1] = w_bad_num[i];
		b_bad_num[i - 1] = b_bad_num[i];
	}
	w_bad_num[TABLE_N - 1] = 0;
	b_bad_num[TABLE_N - 1] = 0;
}

// BW
// WB
void set_last_diff(int w, int h)
{
	for (int i = 0; i < TABLE_N; i++) {
		if (i % 2 == 0) {/*odd must be B and even must be W*/
			if ((h + TABLE_N - 1) % 2 == 0) {
				if (tbl[w + i][h + TABLE_N - 1] != BLACK)
					b_bad_num[TABLE_N - 1]++;
				else
					w_bad_num[TABLE_N - 1]++;
			}
			else {
				if (tbl[w + i][h + TABLE_N - 1] != WHITE)
					w_bad_num[TABLE_N - 1]++;
				else
					b_bad_num[TABLE_N - 1]++;
			}
		}
		else {
			if ((h + TABLE_N - 1) % 2 == 0) {
				if (tbl[w + i][h + TABLE_N - 1] != WHITE)
					b_bad_num[TABLE_N - 1]++;
				else
					w_bad_num[TABLE_N - 1]++;
			}
			else {
				if (tbl[w + i][h + TABLE_N - 1] != BLACK)
					w_bad_num[TABLE_N - 1]++;
				else
					b_bad_num[TABLE_N - 1]++;
			}
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

int do_something(int w, int h)
{
	for (int i = 0; i <= h - TABLE_N; i++) {
		fill_bad_num(i);
		update();

		for (int j = 1; j <= w - TABLE_N; j++) {
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
	int w = 0, h = 0;
	cin >> w >> h;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			char tmp = 0;
			cin >> tmp;
			tbl[i][j] = (tmp == 'B') ? 1 : 0;
		}
	}
	cout << do_something(w,h);
	return 0;
}