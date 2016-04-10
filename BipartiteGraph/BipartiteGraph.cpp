/*
https://www.acmicpc.net/problem/1707

1. Two color theory! : )
 1) Very pure algorithm (Paint verticies either RED or BLACK)
  A) Start with any vertex and paint it as RED(Of course, we need to set flag it is visited)
  B) Adjacent vertices will be painted as BLACK and put on queue. But aware that possbility it was RED. 
     If it is RED, it returns FAILURE immediately. (We don't welcome same color)
  C) Pop from queue and do A) again. 
*/

#include <stdio.h>

const int MAX_N = 100+2;
int N, EDGES;

bool adj[MAX_N + 2][MAX_N + 2] = { 0, };
bool visited[MAX_N + 2] = { 0, };
bool color[MAX_N + 2] = { 0, };

typedef enum color_e {
	UNDEFINED = -1,
	RED  = 0,
	BLUE = 1
} COLOR ;

const int MAX_Q = MAX_N*MAX_N * 2;
int q_begin = 0;
int q_end = -1;

int q[MAX_Q] = { 0, };

inline bool pop_q(int& vertex)
{
	if (q_begin > q_end)
		return false;

	vertex = q[q_begin++];
	return true;
}

inline bool add_q(const int vertex)
{
	if (q_end > MAX_Q)
		return false;

	q[++q_end] = vertex;
	return true;
}

void input_proc(void)
{
	scanf("%d %d\n", &N, &EDGES);
	
	int u, v;
	for (int i = 0; i < EDGES; i++) {
		scanf("%d %d\n", &u, &v);
		adj[u][v] = true;
		adj[v][u] = true;
	}
}

bool do_something(void)
{
	int here = 1;
	add_q(here);
	color[here] = RED;
	while(pop_q(here)) {
		for (int i = 0; i < N; i++) {
			if (color[i] == color[here])
				return false;
			if (!visited[i] && adj[here][i]) {
					
			}
		}
	}
}

int main(void)
{
	int TOTAL = 0;
	scanf("%d\n", &TOTAL);
	while (TOTAL--) {
		input_proc();
		if (do_something())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}