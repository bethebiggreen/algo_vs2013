/*

0.03 DFS seems failed. BFS is implemented.
0.02 add traversing all cases with hueristic answer. 

0.01 https://www.acmicpc.net/problem/1697
     Initial algorithm describe below.
	 17/2 = 8.5 = 8 -> + 2 times (if no remainder, we add 1 times only)
	 8/2 = 4 -> + 1 times.
	 5 to 4 -> +1 times
	 Totally, 4 times.
	 Every time, the calculation that check half of number is smaller than target.
	 And if it is smaller, check, how small it is.
*/

#include <iostream>

using namespace std;

int g_a = 0 ;
int g_b = 0 ;
int sol = 0x7FFFFFFF;

void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> g_a >> g_b;
}

const int MAX_N = 100000*2;
int visited[MAX_N+1] = { 0, };

struct node {
	int vertex;
	int depth;
	node(int in_vertex = 0, int in_depth = 0) : vertex(in_vertex), depth(in_depth) {}
};

node queue[MAX_N*10] = { 0, };
int queue_begin = 0;
int queue_end = -1;

void add_queue(int vertex, int depth) 
{
	queue[++queue_end] = node(vertex, depth);
}

node pop_queue(void)
{
	if (queue_end < queue_begin)
		return node(-2,-2);

	return queue[queue_begin++];
}

bool finished = false;

int dx[2] = { -1,1 };
void traverse(int x, int depth)
{
	if (finished)
		return;

	if (visited[x])
		return;

	visited[x] = true;

	if (x == g_b) {
		if (sol > depth)
			sol = depth;
		finished = true;
		return;
	}
	
	if (!visited[x + dx[0]] && x+dx[0] >= 0 && x + dx[0] <= MAX_N)
		add_queue(x + dx[0], depth + 1);
	
	if (!visited[x + dx[1]] && x + dx[1] >= 0 && x + dx[1] <= MAX_N)
		add_queue(x + dx[1], depth + 1);
	
	if (!visited[(x *2)] && (x * 2) >= 0 && (x*2) <= MAX_N)
		add_queue(x * 2, depth + 1);

	return;
}

void do_something(void)
{
	add_queue(g_a, 0);
	while (1) {
		node n = pop_queue();
		if (n.vertex == -2)
			break;
		traverse(n.vertex, n.depth);
	}	
}

void output_proc(void)
{
	cout << sol;
}

int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}