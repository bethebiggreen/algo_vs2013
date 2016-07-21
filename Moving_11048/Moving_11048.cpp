#include <stdio.h>

int N, M;
const int MAX = 1000;
int d[MAX][MAX];
int a[MAX][MAX];

inline int max_a(const int &a, const int &b) { return (a > b) ? a : b; }
inline int min_a(const int &a, const int &b) { return (a < b) ? a : b; }

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d %d\n", &N, &M);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			scanf("%d", &a[i][j]);
		scanf("\n");
	}

	d[0][0] = a[0][0];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i - 1 >= 0)
				d[i][j] = d[i-1][j]+ a[i][j];
			if (j - 1 >= 0)
				d[i][j] = max_a(d[i][j - 1] + a[i][j], d[i][j]);
			if(i-1 >=0 && j-1 >= 0)
				d[i][j] = max_a(d[i-1][j-1]+a[i][j],d[i][j]);
		}
	}
	printf("%d\n", d[N - 1][M - 1]);
	return 0;
}