#include <stdio.h>

const int MAX_N = 1000 + 1;
int a[MAX_N];
int dl[MAX_N]; // from l
int dr[MAX_N]; // from r

int N;
int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d ", &a[i]);

	dl[1] = 1;

	for (int i = 2; i <= N; i++) {
		int max = 1;
		for (int j = 1; j < i; j++) {
			if (a[j] < a[i]) {
				if (max < dl[j] + 1)
					max = dl[j] + 1;
			}

		}
		dl[i] = max;
	}
	
	dr[N] = 1;
	for (int i = N-1; i >= 1; i--) {
		int max = 1;
		for (int j = N; j > i; j--) {
			if (a[i] > a[j]) {
				if (max < dr[j] + 1)
					max = dr[j] + 1;
			}

		}
		dr[i] = max;
	}

	int ans = 0;
	for (int i = 2; i < N; i++)
		if (ans < dl[i] + dr[i])
			ans = dl[i] + dr[i];

	printf("%d\n", ans - 1);
	return 0;
}