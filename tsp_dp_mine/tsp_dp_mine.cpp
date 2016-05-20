#include <stdio.h>

const int MAX_N = 16;
int a[MAX_N + 1][MAX_N + 1];
long long d[1<<MAX_N][MAX_N + 1];
int N;

const int MAX_INT = 0x7FFFFFFF;

inline long long min_a(long long a, long long b) { return (a > b) ? b : a; }
inline long long max_a(long long a, long long b) { return (a > b) ? a : b; }

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			scanf("%d ", &a[i][j]);
		scanf("\n");
	}

	int case_num = (1 << N) - 1;

	for (int i = 0; i <= case_num; i++) 
		for (int j = 0; j < MAX_N; j++)  
			d[i][j] = MAX_INT;

	d[1][0] = 0;

	// starting point is fixed as 0.
	for (int s = 2; s <= case_num; s++) {
		for (int i = 0; i < N; i++) {
			if (s & (1 << i)) { // i belongs to s!
				for (int j = 0; j < N; j++) { // Why does it starts from 0 ?
					if ((s & (1 << j))/*s 에는 포함되어야함*/ && 
						(((s - (1 << i)) & (1 << j))) /* j 는 s2 에 포함되어야 함 */ &&
						(a[j][i]) &&
						(i != j)/* 같은것도 안됨 */ )
						d[s][i] = min_a(d[s][i], d[s - (1 << i)][j] + a[j][i]);
				}
			}
		}
	}
	long long sol = MAX_INT;

	for (int i = 0; i < MAX_N; i++) {
		if (a[i][0])
			sol = min_a(sol, d[case_num][i] + a[i][0]);
	}
	
	printf("%ld\n", sol);
	return 0;
}