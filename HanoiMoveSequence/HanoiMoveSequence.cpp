/*

 0.03 : printf is used instead of cout due to performace suspect.
 0.02 : Simple but most beautiful algorithm is imeplemented.
 0.01 : Due to memory constraints, brute-force is very hard to implemented.
        However, on the line, there is very simple solution for HANOI specific which I hate.

*/

#define _USING_PRINTF_ 1
#if _USING_PRINTF_
#include <cstdio>
#else
#include <iostream>
#endif
using namespace std;

int N = 0;
int sol = 0;

const int MAX_QUEUE_SIZE = 10000000;
int src[MAX_QUEUE_SIZE];
int dst[MAX_QUEUE_SIZE];

inline void output_proc() {
#if _USING_PRINTF_ 
	printf("%d\n", sol);

	for (int i = 0; i < sol; i++)
		printf("%d %d\n", src[i] , dst[i]);

#else
	cout << sol << endl;

	for (int i = 0; i < sol; i++)
		cout << src[i] << " " << dst[i] << endl;
#endif
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
#if _USING_PRINTF_
	scanf("%d", &N);
#else
	cin >> N;
#endif
	move(N, 1, 3, 2);
	output_proc();
	return 0;
}