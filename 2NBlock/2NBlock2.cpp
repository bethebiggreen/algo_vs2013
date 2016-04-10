#include <stdio.h>

const int MAX_N = 1000;
const int MODULAR = 10007;
int memo[MAX_N + 1] = { 0, };

int d(int number) 
{
	if (memo[number] != -1)
		return memo[number];
	int d_minus_two = 2*d(number - 2);
	int d_minus_one = d(number - 1);
	memo[number] = (d_minus_two + d_minus_one)%MODULAR;
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
	memo[2] = 3;
	printf("%d\n", d(number));
	
	return 0;
}