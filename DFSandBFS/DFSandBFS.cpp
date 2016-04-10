/*

https://www.acmicpc.net/problem/1260
DFS and BFS
     A
   B   C
 D  E F  G

1. DFS - Depth First Search
 A) Order : A B D E C F G
 B) Algorithm : 
  1) Get the root first! check a visit.
  2) Make a loop for visiting(recursive) all adjacent nodes with check.
  3) Selected vertex should be checked.
 
2. BFS - Breadth First Search
 A) Order : A B C D E F G
 B) Algorithm :
  1) Get the root first! and check a visit.
  2) Make a queue(First-In-First-Out style) for all adjacent nodes.
  3) Selected vertex sould be checked.

*/

#include <stdio.h>

// For both DFS and BFS
const int MAX_N = 1000+1+1;
int EDGES = 0;
int N = 0;
int START = 0;
bool visited[MAX_N] = { 0, };
bool adj[MAX_N][MAX_N];

// For a BFS
const int MAX_Q = MAX_N*MAX_N * 2;
int queue[MAX_Q] = { 0, };
int queue_begin = 0;
int queue_end = -1;

inline bool pop_q(int& vertex)
{
	if (queue_begin > queue_end)
		return false;
	vertex = queue[queue_begin++];
	return true;
}

inline bool add_q(const int vertex)
{
	if (queue_end > MAX_Q)
		return false;

	queue[++queue_end] = vertex;
	return true;
}

void dfs(int cur)
{
	printf("%d ", cur);
	for (int i = 1; i <= N; i++) {
		if (!visited[i] && adj[cur][i]) {
			visited[i] = true;
			dfs(i);
		}
	}
}

void bfs(int start)
{
	add_q(start);
	int cur = 0;
	while (pop_q(cur)) {
		printf("%d ", cur);
		for (int i = 1; i <= N; i++) {
			if (!visited[i] && adj[cur][i]) {
				visited[i] = true;
				add_q(i);
			}
		}
	}
}

void input_proc(void)
{
	scanf("%d %d %d\n", &N, &EDGES, &START);
	int vertex1, vertex2;
	for (int i = 0; i < EDGES; i++) {
		scanf("%d %d\n", &vertex1, &vertex2);
		adj[vertex1][vertex2] = true;
	}
}

inline void init(void)
{
	for (int i = 1; i <= N; i++)
		visited[i] = false;
}

void do_something(void)
{
	init();
	visited[START] = true;
	dfs(START);
	printf("\n");

	init();
	visited[START] = true;
	bfs(START);
	printf("\n");
}

int main()
{
	freopen("input.txt", "r", stdin);
	input_proc();
	do_something();
	return 0;
}