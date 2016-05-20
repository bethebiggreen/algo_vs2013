#include <stdio.h>

const int MAX_N = 16;
int N;
int start;
int goal;
int a[MAX_N + 1][MAX_N + 1];
long long d[1 << MAX_N] ;
char yesno[MAX_N+1];

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int case_num = (1 << N) - 1;

	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%d ", &a[i][j]);
		scanf("\n");
	}

	scanf("%s\n", &yesno);
	scanf("%d\n", &goal);

	int len = 0;
	while (yesno[len++]);
	len--;

	for (int i = 0; i < len; i++) {
		if (yesno[i] == 'Y')
			start |= (1 << i);
	}

	return 0;
}