/*
4
1 5 6 7
p[] = {1,5,6,7} 
d(n) = N 개 팔았을 때 최대 이익


d(n) = p[1] + d(n-1);
d
*/

#include <stdio.h>

const int MAX_N = 1001;
int p[MAX_N + 1] = { 0, };
int memo[MAX_N + 1] = { 0, };
const int MIN_INT = 0xFFFFFFFF;
inline int min(int a, int b) { return (a > b) ? b : a; }
inline int max(int a, int b) { return (a > b) ? a : b; }

int d(int number)
{
	if (!number)
		return 0;

	if (memo[number] != 0)
		return memo[number];

	int max_profit = MIN_INT;
	for (int i = 1; i <= number; i++) 
		max_profit = max(max_profit, p[i] + d(number-i));
	memo[number] = max_profit;

	return memo[number];
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int N;
	scanf("%d\n", &N);
	for (int i = 1; i <= N; i++) 
		scanf("%d", p+i);

	printf("%d\n", d(N));
	return 0;
}