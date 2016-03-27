/*

 0.02 : SImple but most beautiful algorithm is imeplemented.
 0.01 : Due to memory constraints, brute-force is very hard to implemented.
        However, on the line, there is very simple solution for HANOI specific which I hate.

*/

#include <iostream>

using namespace std;

int N = 0;
int sol = 0;

const int MAX_QUEUE_SIZE = 10000000;
int src[MAX_QUEUE_SIZE];
int dst[MAX_QUEUE_SIZE];

inline void output_proc() {
	cout << sol << endl;

	for (int i = 0; i < sol; i++)
		cout << src[i] << " " << dst[i] << endl;
}
inline void move_internal(int from, int to)
{
	src[sol] = from;
	dst[sol++] = to;
}

void move(int num, int from, int to, int by)
{
	if (1 == num) {
		move_internal(from, to);
		return;
	}

	move(num - 1, from, by, to);
	move_internal(from, to);
	move(num - 1, by, to, from);
}

int main()
{
	cin >> N;
	move(N, 1, 3, 2);
	output_proc();
	return 0;
}