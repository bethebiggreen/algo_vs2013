/*

    0.02 : Dynamic programming
	0.01 : Recursive (timout occured)

*/
#include <iostream>

const int MAX_N = 301;
int scores[MAX_N] = { 0, };
int visited[MAX_N] = { 0, };
int sol = 0;
int N = 0;

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

inline bool is_it_in_subsequence(int step)
{
	if (step < 2)
		return false;

	return (visited[step - 1] && visited[step - 2]);
}

void traverse(int step, int saved_score)
{
	if (is_it_in_subsequence(step) || step > N)
		return;

	visited[step] = true;
	saved_score += scores[step];

	if (step == N) {
		if (sol < saved_score)
			sol = saved_score;
		return;
	}

	traverse(step + 1, saved_score);
	visited[step + 1] = false;
	traverse(step + 2, saved_score);
	visited[step + 2] = false;

	return;
}

void do_something()
{
	traverse(0, 0);
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}