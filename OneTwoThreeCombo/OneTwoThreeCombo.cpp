#include <stdio.h>

const int MAX_N = 11;
int memo[MAX_N + 1] = { 0, };

int d(int number)
{
	if (memo[number] != -1)
		return memo[number];
	memo[number] = d(number - 3) + d(number - 2) + d(number - 1);
	return memo[number];
}
int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int T = 0;
	scanf("%d\n", &T);
	while (T--) {
		int num = 0;
		scanf("%d\n", &num);
		for (int i = 0; i <= num; i++)
			memo[i] = -1;
		memo[1] = 1;
		memo[2] = 2;
		memo[3] = 4;
		printf("%d\n", d(num));
	}

	return 0;
}