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
int at_least_once[MAX_N];
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
		at_least_once[i] = false;
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
	at_least_once[0] = true;
	for (int it = 0; it < N - 1; it++) {
		// And iterate it others.
		for (int i = 0; i < N ; i++) {
			for (int j = 0; j < N; j++) {
				if (connected[i][j] && at_least_once[i]){
					if (!at_least_once[j])  {
						dist[j] = dist[i] + arr[i][j];
						at_least_once[j] = true;
						continue;
					} 
					if (dist[j] > dist[i] + arr[i][j])
						dist[j] = dist[i] + arr[i][j];
				}
			}
		}
	}

	// Once more for a cycling check
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (connected[i][j] && at_least_once[i]) {
				if (!at_least_once[j]) {
					return false;
				}
				if (dist[j] > dist[i] + arr[i][j])
					return false;
			}
		}
	}
	return true;
}

void output_proc(void)
{
	for (int i = 1; i < N; i++)
		printf("%d\n", (at_least_once[i]) ? dist[i] : -1) ;
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	input_proc();
	if (do_something())
		output_proc();
	else
		printf("-1\n");
	return 0;
}