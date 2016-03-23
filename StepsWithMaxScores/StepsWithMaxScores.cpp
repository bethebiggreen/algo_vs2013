/*

0.02 : Dynamic programming
	    0(1step) 1(2steps)
	0   10       10
    1   30       20
	2   35       25
	3   55       55
	4   65       45
	5   65       75 

	i > 2
	a[i][0] = scores[i] + a[i-1][1]
	a[i][1] = scores[i] + MAX(scores[i-2][0], scores[i-2][1])


	0.01 : Recursive (timout occured)

*/
#include <iostream>

const int MAX_N = 301;
int scores[MAX_N] = { 0, };
int visited[MAX_N] = { 0, };
int sol = 0;
int N = 0;

int max_scores[MAX_N][2];

using namespace std;

void input_proc()
{
	freopen("input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> scores[i];
}

void output_proc()
{
	cout << sol;
}

inline int my_max(int a, int b)
{
	return (a > b ? a : b);
}

void do_something()
{
	max_scores[0][0] = max_scores[0][1] = scores[0];
	max_scores[1][0] = scores[1] + max_scores[0][1];
	max_scores[1][1] = scores[1];
	for (int i = 2; i < N; i++) {
		max_scores[i][0] = scores[i] + max_scores[i - 1][1];
		max_scores[i][1] = scores[i] + my_max(max_scores[i - 2][0], max_scores[i - 2][1]);
	}
	sol = my_max(max_scores[N - 1][0], max_scores[N - 1][1]);
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}