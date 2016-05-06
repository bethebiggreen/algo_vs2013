#include <stdio.h>

const int MAX_N = 31;
int N;
int d[MAX_N + 1][8];
int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d\n", &N);

	d[2][0] = 0;
	d[2][1] = 1;
	d[2][2] = 0;
	d[2][3] = 0;
	d[2][4] = 1;
	d[2][5] = 0;
	d[2][6] = 0;
	d[2][7] = 3;

	for (int i = 3; i <= N; i++) { 
		d[i][0] = d[i - 1][7];
		d[i][1] = d[i - 1][6];
		d[i][2] = d[i - 1][5];
		d[i][3] = d[i - 1][7] + d[i - 1][4];
		d[i][4] = d[i - 1][3];
		d[i][5] = d[i - 1][2];
		d[i][6] = d[i - 1][7] + d[i - 1][1];
		d[i][7] = d[i - 1][0] + d[i - 1][6] + d[i - 1][3];
	}
	printf("%d\n", d[N][7]);
	return 0;
}