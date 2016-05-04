#include <stdio.h>

const int MAX_N = 1000 + 1;
int d[MAX_N];
int a[MAX_N];
int N;
int main()
{ 
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d\n", &a[i]);

	d[1] = 1;
	for (int i = 2; i <= N; i++) {
		int max = 1;
		for (int j = 1; j < i; j++) {
			if (a[j] > a[i]) {
				if (max < d[j] + 1)
					max = d[j] + 1;
			}
		}
		d[i] = max;
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (ans < d[i]) 
			ans = d[i];
	
	printf("%d\n", ans);
	return 0;
}