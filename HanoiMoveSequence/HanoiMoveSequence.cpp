#include <iostream>

using namespace std;

const int MAX_N = 20;
bool visited[MAX_N][MAX_N][MAX_N];
int status[MAX_N][MAX_N][MAX_N];
int top[3];

const int MAX_Q_SIZE = MAX_N*MAX_N*MAX_N*MAX_N;
int from[MAX_Q_SIZE];
int to[MAX_Q_SIZE];

int q_begin = 0;
int q_end = -1;

int N = 0;
inline bool is_goal(void)
{

}

void add_queue(int src, int dst)
{
	q_end++;
	from[q_end] = src;
	to[q_end] = dst;
}

bool pop_front_queue(int& src, int& dst)
{
	if (q_begin > q_end)
		return false;
	src = from[q_begin];
	dst = to[q_begin];
	q_begin++;

	return true;
}

bool finished = false;

void traverse(int src, int dst)
{
	// 6 candidates are available.
	// a->b
	if (top[0] < top[1]) {
		traverse(0, 1);
	}

	// a->c
	if (top[0] < top[2]) {
		traverse(0, 2);
	}
	
	// b->a
	if (top[1] < top[0]) {
		traverse(1, 0);
	}

	// b->c
	if (top[1] < top[2]) {
		traverse(1, 2);
	}

	// c->a
	if (top[2] < top[0]) {
		traverse(2, 0);
	}

	// c->b
	if (top[2] < top[1]) {
		traverse(2, 1);
	}
}

// status
// 20bit 20bit 20bit
// bool visitied[4][4][4]  
//  1 
//  2
//  3
//  4
//  0000
//  1248

void init()
{
	top[0] = 1;
	top[1] = 0;
	top[2] = 0;
	for (int i = 0; i < N; i++);
		
}
int main()
{
	cin >> N;
	init();
	return 0;
}