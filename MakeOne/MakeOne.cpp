/*
https://www.acmicpc.net/problem/1463
1. N이 3으로 나누어 떨어지면, 3으로 나눈다.
2. N이 2로 나누어 떨어지면, 2로 나눈다.
3. 1을 뺀다.
연산횟수의 최소값

D[N] = D[N/3] + 1
D[N] = D[N/2] + 1
D[N] = D[N-1] + 1

d(n) ?
*/
#include <stdio.h>

const int MAX_N = 1000000;
int MEMO[MAX_N+1] = { 0, };

inline int min(int a, int b, int c)
{
	int tmp = (a < b) ? a : b;
	return (tmp < c) ? tmp : c;
}

const int MAX_INT = 0x7FFFFFFF;
int d(int number)
{
	if (MEMO[number] != -1)
		return MEMO[number];

	int divide_three = MAX_INT;
	if ((0 == number % 3) && ((number/3) > 0)) 
		divide_three = d(number / 3);
	
	int divide_two = MAX_INT;
	if ((0 == number % 2) && ((number/2) > 0)) 
		divide_two = d(number / 2);

	int minus_one = MAX_INT;
	if(number-1 > 0)
		minus_one = d(number - 1);

	MEMO[number] = min(divide_three, divide_two, minus_one) + 1;

	return MEMO[number];
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	for (int i = 0; i <= MAX_N; i++)
		MEMO[i] = -1;
	int number;
	scanf("%d\n", &number);

	MEMO[1] = 0;
	printf("%d\n", d(number));
	return 0;
}