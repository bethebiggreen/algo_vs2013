/*

0.02 add traversing all cases with hueristic answer.

0.01 https://www.acmicpc.net/problem/1697
     Initial algorithm describe below.
	 17/2 = 8.5 = 8 -> + 2 times (if no remainder, we add 1 times only)
	 8/2 = 4 -> + 1 times.
	 5 to 4 -> +1 times
	 Totally, 4 times.
	 Every time, the calculation that check half of number is smaller than target.
	 And if it is smaller, check, how small it is.
*/

#include <iostream>

using namespace std;

int g_a = 0 ;
int g_b = 0 ;
int sol = 0;

void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> g_a >> g_b;
}

int calls_of_traverse = 0;
int dx[2] = { -1,1 };
void traverse(int x, int times)
{
	/*
	if (times > sol)
		return;
		*/
	calls_of_traverse++;
	cout << "calls_of_traverse:" << calls_of_traverse << ", x:" << x << endl;

	if (x < 0)
		return;

	if (x == g_b) {
		if (sol > times)
			sol = times;
		return;
	}

	// -1, 1 and x2
	for (int i = 0; i < 2; i++) {
		traverse(x + dx[i], times + 1);
	}
	traverse(2 * x, times + 1);
}
void do_something(void)
{
	int tmp = 0;
	if (g_a > g_b) {
		tmp = g_a;
		g_a = g_b;
		g_b = tmp;
	}

	int a = g_a;
	int b = g_b;
	while (b/2 > a)
	{
		if (b % 2)
			sol += 2;
		else
			sol++;
		b /= 2;		
	}

	bool is_even = false;
	if (b % 2 == 0)
		is_even = true;

	int case1 = a - (b / 2 + is_even) + is_even + 1;
	int case2 = b - a;
	
	sol += (case1 > case2) ? case2 : case1;

	traverse(g_a, 0);
}


void output_proc(void)
{
	cout << sol;
	cout << endl << calls_of_traverse << endl;
}

int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}