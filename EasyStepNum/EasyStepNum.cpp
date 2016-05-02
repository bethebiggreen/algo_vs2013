/*
45656

1. Definition : n-1 or n + 1 , n , n - 1 or n + 1 -> A step-number
2. D[n] �� n �ڸ����϶� Step-number �� ����. D[n-1] + 2. �� �ڸ��� 1~9 ���� �� �� ����.
3. D[1] = 9��, D[2] = D[1]*2-1 = 17, D[3] = D[2]*2- (N-1).. D3����? Due to ��ȯ�� �ȵǱ� ������.. 32

1 0 1 
    
1 2 1
    3
2 1 0
    2
2 3 2
    4
3 2 1
    3
3 4 3
    5
4 3 2
    4
4 5 4
    6
5 4 3
    5
5 6 5
    7
6 5 4
    6
6 7 6
    8
7 6 5
    7
7 8 7
    9
8 7 6
    8
8 9 8
    
9 8 7
    9
9 0 X 

D(n) = N�ڸ��϶� ������ ����� �� = ���� 0�̸鼭, N �ڸ��� ������ ��ܼ� + ���� 1�̸鼭, N �ڸ��� ������ ��ܼ� + ... + ���� 9�̸鼭, N �ڸ��� ������ ��ܼ�
���� 0 �̸鼭, N �ڸ��� ��� �� =  m[n][0] = m[n-1][0-1] + m[n-1][0+1] , ��, ÷�� ��� �� Boundary �� ����
*/

#include <stdio.h>

const int MODULAR = 1000000000;
const int MAX_N = 100 + 1;
const int NUM_DIGITS = 10;
long long m[MAX_N + 1][NUM_DIGITS] = { 0, };

long long d(int digits, int last)
{
	if (m[digits][last] != -1)
		return m[digits][last];

	if (last - 1 < 0)
		m[digits][last] = d(digits - 1, last + 1) % MODULAR;
	else if (last + 1 > 9)
		m[digits][last] = d(digits - 1, last - 1) % MODULAR;
	else
		m[digits][last] = (d(digits - 1, last - 1) + d(digits - 1, last + 1)) % MODULAR;

	return m[digits][last];
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int num = 0;
	scanf("%d", &num);
	for (int i = 0; i <= num; i++)
		for (int j = 0; j < NUM_DIGITS; j++)
			m[i][j] = -1;

	m[1][0] = 0;
	for (int i = 1; i <= 9; i++)
		m[1][i] = 1;

	long long sol = 0;
	for (int i = 0; i <= 9; i++)
		sol += d(num, i);
	
	printf("%d\n", sol%MODULAR);
	return 0;
}