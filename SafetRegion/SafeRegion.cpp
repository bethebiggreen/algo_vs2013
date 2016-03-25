/*

  0.02 : Timeout is occured after implementing of BFS.
  0.01 : https://www.acmicpc.net/problem/2468
         BFS is adjustd to traverse adjacent verticies.

*/

#include <iostream>
#include <cstdio>

using namespace std;

int N = 0;
const int MAX_N = 100+2;
int g_map[MAX_N][MAX_N];
int sol = 0;

enum status {
	FLOODED = -1,
	UNINIT = 0
};

struct node {
	int i;
	int j;
	node(int in_i = -1, int in_j = -1) : i(in_i), j(in_j) {}
	void clear() { i = -1; j = -1; }
};


enum DIRECTIONS {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

const int MAX_QUEUE_SIZE = MAX_N*MAX_N*10;
node queue[MAX_QUEUE_SIZE];
int queue_begin = 0;
int queue_end = -1;

inline void add_queue(int i, int j)
{
#if _DEBUG
	cout << "i:" << i << ", j:" << j << ", queue_end:" << queue_end << endl;
#endif
	queue[++queue_end] = node(i, j);
}

inline node pop_queue(void)
{
	if (queue_begin > queue_end)
		return node(-1, -1);

	return queue[queue_begin++];
}

void input_proc() 
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> g_map[i][j];
}

inline bool is_all_covered(void)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (g_map[i][j] > 0)
				return false;

	return true;
}

int flood(int depth)
{
	int first_met = -1;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (g_map[i][j] == depth) {
				g_map[i][j] = FLOODED;
				if (first_met == -1) 
					first_met = i*N + j;
			}
	return first_met;
}


inline void mark(int i, int j, int map[MAX_N][MAX_N])
{
	if (map[i][j] == FLOODED)
		return;
	else
		map[i][j] = FLOODED;

	for (int dir = 0; dir < 4; dir++) {
		int new_i = i + dx[dir];
		int new_j = j + dy[dir];

		if (new_i < 0 || new_j < 0 || new_i >= N || new_j >= N)
			continue;
		if(map[new_i][new_j] > 0)
			add_queue(new_i, new_j);
	}
}

void copy_map(int dst_map[MAX_N][MAX_N], const int org_map[MAX_N][MAX_N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dst_map[i][j] = org_map[i][j];
}

void init_queue(void)
{
	cout << __FUNCTION__ << endl;
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
		queue[i].clear();

	queue_begin = 0;
	queue_end = -1;
}

int num_of_safe_region(int start, const int m[MAX_N][MAX_N])
{

	int safe_region = 0;
	int local_map[MAX_N][MAX_N];
	copy_map(local_map, m);
	
	while (1) {
		init_queue();
		bool found = false;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (local_map[i][j] > 0) {
					add_queue(i, j);
					i = j = N;
					found = true;
					safe_region++;
				}
		if (found) {
			while (1) {
				node n = pop_queue();
				if (n.i == -1)
					break;
				mark(n.i, n.j, local_map);
			}
		}
		else
			break;
	}

	return safe_region;
}

void display_map(void)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3d ", g_map[i][j]);
		}
		printf("\n");
	}
}

void do_something()
{
	int rain_depth = 0;

	while (!is_all_covered())
	{
		int first = 0;

		if (-1 == (first = flood(rain_depth))) {
		}
		else {
			int cur_sol = num_of_safe_region(first, g_map);
			if (sol < cur_sol)
				sol = cur_sol;
		}
		rain_depth++;
	}
}

void output_proc()
{
	cout << sol;
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}