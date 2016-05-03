#include <stdio.h>

const int MAX_N = 10000;

int max_a(int a, int b) { return (a > b) ? a : b; }

int d[MAX_N+1][2];
int a[MAX_N+1];
int N;
int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) 
		scanf("%d\n", &a[i]);

	d[1][1] = a[1];
	d[2][0] = d[1][1];
	d[2][1] = d[1][1] + a[2];

	for (int i = 3; i <= N; i++) {
		d[i][0] = max_a( d[i-1][1], d[i-1][0]);
		d[i][1] = a[i] + max_a( a[i-1] + d[i-2][0], d[i-1][0]);
	}

	printf("%d\n", max_a(d[N][0], d[N][1]));
	return 0;
}