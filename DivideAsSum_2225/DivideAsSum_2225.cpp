#if 1
#include <stdio.h>

const long long MODULAR_UNIT = 1000000000;

const int MAX_N = 200 + 1;
long long d[MAX_N][MAX_N];

int N, K;
long long go(int k, int n)
{
	if (k == 1)
		return 1;

	if (d[k][n])
		return d[k][n];

	long long sum = 0;
	for (int j = 0; j <= n; j++) {
		sum += go(k-1, n-j);
		sum	%= MODULAR_UNIT;
	}

	return (d[k][n] = (sum));
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d %d\n", &N, &K);
	printf("%lld\n", go(K, N));
	return 0;
}
#else
#include <iostream>
using namespace std;
long long d[201][201];
long long mod = 1000000000;
int main() {
	freopen("input.txt", "r", stdin);
	int n, k;
	cin >> n >> k;
	d[0][0] = 1LL;
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j <= n; j++) {
			for (int l = 0; l <= j; l++) {
				d[i][j] += d[i - 1][j - l];
				d[i][j] %= mod;
			}
		}
	}
	cout << d[k][n] << '\n';
	return 0;
}

#endif