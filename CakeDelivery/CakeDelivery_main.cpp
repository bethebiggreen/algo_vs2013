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

const int MAX_N = 100000+1; // +1 : Due to start point
const int CANDIDATES_N = 5;

enum {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	SELF,
};

int min_dist[MAX_N*CANDIDATES_N];

int x[MAX_N] = { 0, };
int y[MAX_N] = { 0, };

//UP RIGHT DOWN LEFT
int dx[CANDIDATES_N] = { 0, 1, 0,-1, 0 };
int dy[CANDIDATES_N] = { 1, 0,-1, 0, 0 };

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

int do_something(void)
{
	// init
	for (int i = 0; i < CANDIDATES_N; i++) 
		min_dist[i] = get_dist(x[0], y[0], x[1] + dx[i], y[1] + dy[i]);
	
	// min_dist[1] is filled in, already.
	for (int cake = 2; cake <= cake_num; cake++) {	
		for (int n = 0; n < CANDIDATES_N; n++) {
			int x_n = x[cake] + dx[n];
			int y_n = y[cake] + dy[n];
			for (int n_prev = 0; n_prev < CANDIDATES_N; n_prev++) {
				int x_prev = x[cake - 1] + dx[n_prev];
				int y_prev = y[cake - 1] + dy[n_prev];
				int dist_prev = min_dist[CANDIDATES_N*(cake - 2) + n_prev];
				int dist = dist_prev + get_dist(x_prev, y_prev, x_n, y_n);
				if (min_dist[CANDIDATES_N*(cake - 1) + n] > dist)
					min_dist[CANDIDATES_N*(cake - 1) + n] = dist; 
			}
		}
	}

	int sol = BIG_INT;
	for (int i = 0; i < CANDIDATES_N; i++) 
		if (sol > min_dist[CANDIDATES_N*(cake_num - 1) + i])
			sol = min_dist[CANDIDATES_N*(cake_num - 1) + i];

	return sol;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int tc_num = 1;
	for (int i = 0; i < MAX_N*CANDIDATES_N; i++)
		min_dist[i] = BIG_INT;

	for (int tc = 0; tc < tc_num; tc++) {
		cin >> cake_num;
		cin >> x[0] >> y[0];
		for (int cake = 1; cake <= cake_num; cake++) {
			cin >> x[cake] >> y[cake];
		}
		cout << do_something() << endl;
	}
	return 0;
}