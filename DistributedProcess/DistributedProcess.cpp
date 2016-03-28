#include <iostream>

using namespace std;
int N = 0;

void input_proc()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	cin >> N;
}

void do_something()
{
	for (int tc = 0; tc < N; tc++) {
		int a = 0, b = 0;
		cin >> a >> b;
		int sol = a;
		for (int i = 1; i < b; i++) 
			sol = sol*a % 10;

		if (sol)
			cout << sol << endl;
		else
			cout << 10 << endl;
	}
}

int main(void)
{
	input_proc();
	do_something();
	return 0;
}