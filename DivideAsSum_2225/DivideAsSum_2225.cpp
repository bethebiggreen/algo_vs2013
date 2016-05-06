#include <stdio.h>

const long long MODULAR_UNIT = 1000000000;


inline int abs_a(int a)
{
	return (a < 0) ? -a : a;
}

const int MAX_N = 200 + 1;
long long d[MAX_N][MAX_N];

int N, K;
long long go(int n, int k)
{
	if (d[n][k])
		return d[n][k];

	if (n == 0 || k == 1)
		return 1;
	

	long long sum = 0;
	for (int j = 0; j <= n; j++) {
		sum += ((go(N - j, k - 1) * go(j, k - 1)) % MODULAR_UNIT);
	}

	return (d[n][k] = (sum));
	
}
int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d %d\n", &N, &K);
#if 0
	for (int i = 0; i < MAX_N; i++)
		d[i][1] = 1;

	for (int i = 1; i < MAX_N; i++)
		d[1][i] = i;
	go(N, K);
#else 
	d[0][0] = 1LL;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= K; j++) {
			for (int l = 0; l <= j; l++) {
				d[i][j] += d[i - 1][j - l];
				d[i][j] %= MODULAR_UNIT;
			}
		}
	}
#endif
	printf("%lld\n", d[N][K]);
	return 0;
}