#include <stdio.h>
int N;
const int MAX_N = 100000 + 1;
int d[MAX_N+1];

int get_max_root(int n)
{
	int root = 1;
	while (root*root <= n)
		root++;
	return root-1;
}

inline int min_a(int a, int b)
{
	return (a > b) ? b : a;
}

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d", &N);
	d[1] = 1;
	for (int i = 2; i <= N; i++) {
		int max_root = get_max_root(i);
		int min = 0x7FFFFFFF;
		for (int j = 1; j*j <= max_root*max_root; j++) {
			if (min > (d[i - j*j] + 1))
				min = d[i - j*j] + 1;
		}
		d[i] = min;
	}
		
	printf("%d\n", d[N]);

	return 0;
}