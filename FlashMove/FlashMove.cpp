/*

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

int a = 0 ;
int b = 0 ;
int sol = 0;

void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> a >> b;
}

int get_heuristic(void)
{
	while (b / 2 > a)
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
}

void do_something(void)
{
	int tmp = 0;
	if (a > b) {
		tmp = a;
		a = b;
		b = tmp;
	}
}

void output_proc(void)
{
	cout << sol;
}

int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}