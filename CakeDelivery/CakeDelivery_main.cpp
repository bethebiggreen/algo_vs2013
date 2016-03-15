/*
3
2 2
3 6
6 7
7 3
*/
#include <iostream>

using namespace std;

int start_x = 0;
int start_y = 0;

const int MAX_N = 1000000;

int x[MAX_N] = { 0, };
int y[MAX_N] = { 0, };

//UP RIGHT DOWN LEFT
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

int cake_num = 0;

int do_something(void)
{
	// to choose n ... we could consider both n+1 and n+2.
	return -1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int tc_num = 0;
	cin >> tc_num;
	for (int tc = 0; tc < tc_num; tc++) {
		cin >> cake_num;
		for (int cake = 0; cake < cake_num; cake++) {
			cin >> x[cake] >> y[cake];
		}
		cout << do_something() << endl;
	}
	return 0;
}