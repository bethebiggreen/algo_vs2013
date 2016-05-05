/*
    https://www.acmicpc.net/problem/11140

    0.01 :            char
	               l         o
	    	   o   l  any    l
			l           l
		    Every char will traverse above tree.
*/

#include <iostream>
#include <cstdio>
using namespace std;
int N = 0;

const int MAX_TC = 100;
const int MAX_STR_LEN = 50;

char tc[MAX_TC][MAX_STR_LEN + 1];
int sol[MAX_TC];


void input_proc()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	cin >> N;
	for (int i = 0; i < N; i++) {
		//cin.getline(&tc[i][0], MAX_STR_LEN + 1);
		scanf("%s", &tc[i][0]);
	}
}

void do_something()
{
	
	for (int i = 0; i < N; i++) {
		int iter = 0;
		while (tc[i][iter]) {
			int local_sol = 0;

			if ('l' == tc[i][iter+0]) {
				local_sol++;
				if (iter+1 < MAX_STR_LEN && 'o' == tc[i][iter+1]) {
					local_sol++;
					if (iter + 2 < MAX_STR_LEN && 'l' == tc[i][iter+2]) {
						local_sol++;
						sol[i] = local_sol;
						break;
					}
				}
				else if (iter + 1 < MAX_STR_LEN && 'l' == tc[i][iter+1]) {
					local_sol++;
				}
				else if (iter + 2 < MAX_STR_LEN && 'l' == tc[i][iter+2]) {
					local_sol++;
					iter++; // We can skip next char.
				}
			}
			else if ('o' == tc[i][iter+0]) {
				local_sol++;
				if (iter + 1 < MAX_STR_LEN && 'l' == tc[i][iter + 1]) {
					local_sol++;
				}
			} 

			iter++;
			if (sol[i] < local_sol)
				sol[i] = local_sol;
		}
	}
}

void output_proc()
{
	for (int i = 0; i < N; i++)
		cout << 3 - sol[i] << endl;
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}