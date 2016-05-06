#include <stdio.h>

const int MAX_N = 100 + 1;

long long d[MAX_N + 1];

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int tc_num = 0;
	scanf("%d\n", &tc_num);

	int n = 0;
	d[1] = 1;
	d[2] = 1;
	d[3] = 1;
	d[4] = 2;
	d[5] = 2;
	d[6] = 3;
	
	while (tc_num--) {
		scanf("%d\n", &n);
		if (n > 6 && d[n] == 0) {
			for (int i = 7; i <= n; i++) 
				d[i] = d[i - 1] + d[i - 1 - 4];
		}
		printf("%lld\n", d[n]);
	}

	return 0;
}