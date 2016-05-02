#include <stdio.h>
inline long long max_a(long long a, long long b) { return (a > b) ? a : b; }

int N;
const int MAX_N = 100000;
int arr[2][MAX_N+1];
long long d[2][MAX_N+1];

void input_proc(void)
{
	scanf("%d\n", &N);
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= N; j++)
			scanf("%d ", &arr[i][j]);
	}
}

int do_something(void)
{
	d[0][1] = arr[0][1];
	d[1][1] = arr[1][1];
	for (int i = 2; i <= N; i++) {
		d[0][i] = arr[0][i] + max_a(d[1][i - 1], d[1][i - 2]);
		d[1][i] = arr[1][i] + max_a(d[0][i - 1], d[0][i - 2]);
	}
	return max_a(d[0][N], d[1][N]);
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int T;
	scanf("%d\n", &T);
	while (T--) {
		input_proc();
		printf("%d\n", do_something());
	}
	return 0;
}