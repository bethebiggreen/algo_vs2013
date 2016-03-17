/*
3
2 2
3 6
6 7
7 3
*/
#include <iostream>
#include <assert.h>

using namespace std;

const int MAX_N = 1000000;

enum {
	UP_RIGHT = 0,
	RIGHT_DOWN,
	DOWN_LEFT,
	LEFT_UP
};

enum {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

int x[MAX_N] = { 0, };
int y[MAX_N] = { 0, };

//UP RIGHT DOWN LEFT
int dx[4] = { 0, 1, 0,-1 };
int dy[4] = { 1, 0,-1, 0 };

int cake_num = 0;
const int BIG_INT = 0x7FFFFFFF;

inline int abs(int a) { return (a < 0) ? -a : a; }

inline int get_dist(int x1, int y1, int x2, int y2)
{
	int x_diff = 0;
	int y_diff = 0;
	if (x1 * x2 < 0)
		x_diff = abs(x1) + abs(x2);
	else
		x_diff = abs(abs(x1) - abs(x2));

	if (y1 * y2 < 0)
		y_diff = abs(y1) + abs(y2);
	else
		y_diff = abs(abs(y1) - abs(y2));
	return (x_diff + y_diff);
}

int get_direction(int x1, int x2, int y1, int y2)
{
	if ((x2 - x1 >= x1) && (y2 - y1 >= y1))
		return UP_RIGHT;
	if ((x2 - x1 >= x1) && (y2 - y1 <= y1))
		return RIGHT_DOWN;
	if ((x2 - x1 <= x1) && (y2 - y1 <= y1))
		return DOWN_LEFT;
	if ((x2 - x1 <= x1) && (y2 - y1 >= y1))
		return LEFT_UP;
	
	assert(true);
	return -1;
}

inline void set_candidates(int rel, int x, int y, int out_x[2], int out_y[2])
{
	switch (rel) {
		case UP_RIGHT:
			out_y[0] = y + dy[UP];
			out_x[0] = x + dx[UP];
			out_x[1] = x + dx[RIGHT];
			out_y[1] = y + dy[RIGHT];
			break;
		case RIGHT_DOWN:
			out_x[0] = x + dx[RIGHT];
			out_x[1] = x + dx[DOWN];
			out_y[0] = y + dy[RIGHT];
			out_y[1] = y + dy[DOWN];
			break;
		case DOWN_LEFT:
			out_x[0] = x + dx[DOWN];
			out_x[1] = x + dx[LEFT];
			out_y[0] = y + dy[DOWN];
			out_y[1] = y + dy[LEFT];
			break;
		case LEFT_UP:
			out_x[0] = x + dx[LEFT];
			out_x[1] = x + dx[UP];
			out_y[0] = y + dy[LEFT];
			out_y[1] = y + dy[UP];
			break;
		default:
			assert(true);
	}
	return;
}

int do_something(void)
{
	for (int i = 0; i < 4; i++) {
		int a[2], b[2];
		set_candidates(i, 2, 2, a, b);
		printf("2,2(%d) : %d %d \n", i, a[0], b[0]);
		printf("2,2(%d) : %d %d \n", i, a[1], b[1]);
	}
	// to choose n ... we could consider both n+1 and n+2.
	int sol = 0;
	for (int cake = 1; cake < cake_num; cake++) {
		int rel_n_cur = get_direction(x[cake], x[cake + 1], y[cake], y[cake + 1]);
		int rel_n_next = -1; // UNINIT 

		if (cake <= cake_num - 2)
			rel_n_next = get_direction(x[cake + 1], x[cake + 2], y[cake + 1], y[cake + 2]);
		else if ( cake == cake_num - 1)
			rel_n_next = get_direction(x[cake + 1], x[cake], y[cake + 1], y[cake]);

		int x1[2] = { 0, }; int x2[2] = { 0, }; int y1[2] = { 0, }; int y2[2] = { 0, };
		set_candidates(rel_n_cur, x[cake], y[cake], x1, y1);
		set_candidates(rel_n_next, x[cake + 1], y[cake + 1], x2, y2);

		int min_dist_prev_cur_next = BIG_INT;
		int min_x = BIG_INT;
		int min_y = BIG_INT;
		for (int i = 0; i < 2; i++) {
			int dist_prev_to_cur = get_dist(x[cake - 1], y[cake - 1], x1[i], y1[i]);
			int min_dist_cur_to_next = BIG_INT;
			for (int j = 0; j < 2; j++) {
				int dist_cur_to_next = get_dist(x1[i], y1[i], x2[j], y2[j]);
				if (min_dist_cur_to_next > dist_cur_to_next)
					min_dist_cur_to_next = dist_cur_to_next;
			}

			if (min_dist_prev_cur_next > dist_prev_to_cur + min_dist_cur_to_next) {
				min_dist_prev_cur_next = dist_prev_to_cur + min_dist_cur_to_next;
				min_x = x1[i];
				min_y = y1[i];
			}
		}

		if (cake <= cake_num - 2)
			sol += get_dist(x[cake - 1], y[cake - 1], min_x, min_y);
		else if (cake == cake_num - 1)
			sol += min_dist_prev_cur_next;

	}
	return sol;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int tc_num = 1;
	for (int tc = 0; tc < tc_num; tc++) {
		cin >> cake_num;
		int start_x = 0;
		int start_y = 0;
		cin >> x[0] >> y[0];
		for (int cake = 1; cake <= cake_num; cake++) {
			cin >> x[cake] >> y[cake];
		}
		cout << do_something() << endl;
	}
	return 0;
}