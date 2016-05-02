/*
3 4
1 2 4
1 3 3
2 3 -1
3 1 -2
*/
#include <stdio.h>
const int MAX_N = 500;

int arr[MAX_N][MAX_N];
int dist[MAX_N];
// bool connected[MAX_N][MAX_N];
int connected[MAX_N][MAX_N];
int N = 0;

// const int MAX_INT = 0x7FFF;
// const int MIN_INT = 0xFFFF;
const int MAX_INT = 10001;
const int MIN_INT = -10001;

void input_proc(void)
{
	int edge_num = 0;
	scanf("%d %d\n", &N, &edge_num);
	for (int i = 0; i < N; i++) {
		dist[i] = MAX_INT;
		for (int j = 0; j < N; j++)
			arr[i][j] = MAX_INT;
	}

	int u, v, val;
	for (int i = 0; i < edge_num; i++) {
		scanf("%d %d %d\n", &u, &v, &val);
		u--, v--;
		if (arr[u][v] > val) 
			arr[u][v] = val;
		if (!connected[u][v])
			connected[u][v] = true;
	}

}

bool do_something(void)
{
	/*
		This loop finds MIN dist from assigned vertex to others. It runs until num of |V-1|.
	*/
	// We consider ith vertex.
	int base = 0;
	dist[base] = 0;
	for (int i = 0; i < N-1; i++) {
		// And iterate it others.
		for (int j = 0; j < N; j++) {
			if (i == j)
				continue;

			if (connected[i][j]) {
				if (dist[j] > dist[i] + arr[i][j])
					dist[j] = dist[i] + arr[i][j];
			}
		}
	}

	// Once more for a cycling check
	int i = N - 1;
	for (int j = 0; j < N; j++) {
		if (i == j)
			continue;

		if (connected[i][j])
			if (dist[j] > dist[i] + arr[i][j])
				return false;
	}

	return true;
}

void output_proc(void)
{
	for (int i = 1; i < N; i++)
		printf("%d\n", (dist[i] == MAX_INT) ? -1 : dist[i]);
}

int main(void)
{
#if _DEBUG
	freopen("input.txt","r", stdin);
#endif
	input_proc();
	if (do_something())
		output_proc();
	else
		printf("-1\n");
	return 0;
}