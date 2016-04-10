/*
https://www.acmicpc.net/problem/11726
*/

#if 0
#include <stdio.h>

const int MAX_N = 1000;
int memo[MAX_N + 1] = { 0, };

int d(int number)
{
	if (memo[number] != -1)
		return memo[number];
	int d_minus_two = d(number - 2);
	int d_minus_one = d(number - 1);

	memo[number] = (d_minus_two + d_minus_one) % 10007;
	return memo[number];
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int number = 0;
	scanf("%d\n", &number);

	for (int i = 0; i <= number; i++)
		memo[i] = -1;

	memo[1] = 1;
	memo[2] = 2;
	printf("%d\n", d(number));

	return 0;
}
#endif