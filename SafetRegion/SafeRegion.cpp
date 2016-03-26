/*
  
  0.04 : Add fprintf_a debug module
  0.03 : Confirmed unnecessary recursive-calls are not called. #include <queue> is needed, further investigation.
  0.02 : Timeout is occured after implementing of BFS.
  0.01 : https://www.acmicpc.net/problem/2468
         BFS is adjustd to traverse adjacent verticies.

*/

#include <iostream>
#include <cstdio>
#if _DEBUG
#include <stdio.h>
#include <cstdlib>
#define fprintf_a(fd, fmt, ...)  fprintf(fd, fmt, __VA_ARGS__) 
#else
#define fprintf_a
#endif

#define _STL_QUEUE_ENABLE_ 1
#if _STL_QUEUE_ENABLE_
#include <queue>
#endif

using namespace std;

int N = 0;
//const int MAX_N = 100+2;
const int MAX_N = 5 + 2;
int g_map[MAX_N][MAX_N];
int local_map[MAX_N][MAX_N];
int sol = 0;

FILE* fp = NULL;

enum status {
	FLOODED = -1,
	UNINIT = 0
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
struct node {
	int i;
	int j;
	node(int in_i = -1, int in_j = -1) : i(in_i), j(in_j) {}
	void clear() { i = -1; j = -1; }
};

#if !_STL_QUEUE_ENABLE_
node queue[MAX_QUEUE_SIZE];
int queue_begin = 0;
int queue_end = -1;
#else
queue<node> g_q;
#endif

#if !_STL_QUEUE_ENABLE_
inline void add_queue(int i, int j)
{
#if _DEBUG
	//cout << "i:" << i << ", j:" << j << ", queue_end:" << queue_end << endl;
	
	if (fp)
		fprintf_a(fp, "[%15s] i:%d, j:%d, queue_end:%d\n", __FUNCTION__, i, j, queue_end);
	else
		cout << "fopen is failed" << endl;
#endif
	queue[++queue_end] = node(i, j);
}

inline node pop_queue(void)
{
	if (queue_begin > queue_end)
		return node(-1, -1);
	fprintf_a(fp, "[%15s] i:%d, j:%d, queue_begin:%d\n", __FUNCTION__, queue[queue_begin].i, queue[queue_begin].j, queue_begin);
	return queue[queue_begin++];
}
#endif

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


inline void mark(int i, int j)
{
	fprintf_a(fp, "[%15s] i:%d, j:%d will add belows.\n", __FUNCTION__,i, j);
	if (local_map[i][j] == FLOODED) {
		fprintf_a(fp, "[%15s] i:%d, j:%d is returned with out adding.\n", __FUNCTION__, i, j);
		return;
	}
	else
		local_map[i][j] = FLOODED;

	for (int dir = 0; dir < 4; dir++) {
		int new_i = i + dx[dir];
		int new_j = j + dy[dir];

		if (new_i < 0 || new_j < 0 || new_i >= N || new_j >= N)
			continue;
		if (local_map[new_i][new_j] > 0) {
#if !_STL_QUEUE_ENABLE_
			add_queue(new_i, new_j);
#else
			g_q.push(node(new_i, new_j));
#endif
		}
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
#if !_STL_QUEUE_ENABLE_
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
		queue[i].clear();

	queue_begin = 0;
	queue_end = -1;
#else 
	while (!g_q.empty())
		g_q.pop();
#endif
}

int num_of_safe_region(int start, const int m[MAX_N][MAX_N])
{
	int safe_region = 0;
	copy_map(local_map, m);
	
	while (1) {
		init_queue();
		bool found = false;
		fprintf_a(fp, "[%15s] finding start begins\n", __FUNCTION__);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (local_map[i][j] > 0) {
					fprintf_a(fp, "[%15s] i:%d j:%d will be added\n", __FUNCTION__, i, j);
#if !_STL_QUEUE_ENABLE_
					add_queue(i, j);
#else
					g_q.push(node(i, j));
#endif
					i = j = N;
					found = true;
					safe_region++;
				}
		fprintf_a(fp, "[%15s] finding start ends\n", __FUNCTION__);

		if (found) {
			fprintf_a(fp, "[%15s] marking begins\n", __FUNCTION__);
			while (1) {
#if !_STL_QUEUE_ENABLE_
				node n = pop_queue();
				if (n.i == -1)
					break;
#else
				if (g_q.empty())
					break;
				node n = g_q.front();
				g_q.pop();
#endif
				mark(n.i, n.j);
			}
			fprintf_a(fp, "[%15s] marking ends\n", __FUNCTION__);
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
#if _DEBUG
	fp = fopen("output.txt", "w");
#endif
	input_proc();

	do_something();
	output_proc();
#if _DEBUG
	if (fp)
		fclose(fp);
#endif
	return 0;
}