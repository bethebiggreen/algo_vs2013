#include <stdio.h>

int N;
const int MAX = 100;
unsigned int a[MAX][MAX];
unsigned long long d[MAX][MAX];

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d\n", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			scanf("%d", &a[i][j]);
		scanf("\n");
	}

	d[0][0] = 1ULL;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)  {
			if (j - 1 >= 0) {
				for (int k = j - 1; k >= 0; k--)
					if (a[i][k] == j-k)
						d[i][j] += d[i][k];
			}
			if (i - 1 >= 0) {
				for (int k = i - 1; k >= 0; k--)
					if (a[k][j] == i-k)
						d[i][j] += d[k][j];
			}
		}
	}

	printf("%llu\n", d[N - 1][N - 1]);
	return 0;
}