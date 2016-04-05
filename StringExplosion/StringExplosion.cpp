/*

	https://www.acmicpc.net/problem/9935
    
	0.11 : Implementation inspired by reference answer.
	0.10 : 1. push : when it meets starting character of explosion.
	       2. pop : when it meets bomb. It would be launched continuosly.
		   3. bomb[n] : store range of bomb. For instance, if bomb[0] stores integer 24, range from 0 to 24 is doomed.
	0.09 : Stack
	0.08 : Previous suspector is stored in stack.
	0.07 : Calling printf burstly causes timeout. answer string is stored in buffer temporary and printed out once.
	0.06 : Fix BABADD (BAD) case. Still timout is occured. 
	0.05 : printf is used, instead of cout.
	0.04 : Array is going to start with -1 for a 'void'.
	       Traversing is started from str[1], not str[0].

	0.03 : We will implement similar as linked list.
	       char str[MAX_N] ; // store string
		   int next[MAX_N] ; // store next index 
		   For example, if str stores 'TEST' then, next[0] = 1;, next[1] = 2, so on.
		   Here is bomb scenario, TESTC4C4TEST.
		   TEST[3] stores digit 8 and it helps iterator skips bomb range.
		   It needs to solve 'C4C4C4', and FRULA case. 

	0.02 : For the performance issue, having chunk is preferred.
	       a[0] = 0, b[0] = 3; -> The first chunk exists in 0 to 3.
		   a[1] = 7, b[1] = 9; -> The second chunk exists in 7 to 9.
		   So on..

	0.01 :  Input characters are copied to solution buffer until meet first char of explosion.
	        It checks following char is part of explosion.
			 1. Following characters are matched with explosion
			   1) Buffer(explosion) will be re-written as IGNORED('#').
			   2) A position is set to current - num of explosion.
			   3) It re-start checking explosion.
			 2. If it's not matched, it will keep checking.

*/

#include <iostream>
#include <cstdio>
#include <stdio.h>

using namespace std;

const int MAX_STR_LEN = 1000010;
const int MAX_EXPLOSION_LEN = 40;

char str[MAX_STR_LEN + 1] = { 0, };
char explosion[MAX_EXPLOSION_LEN + 2] = { 0, };
int exp_size = 0;
int bombs_begin[MAX_STR_LEN];
int bombs_end[MAX_STR_LEN];
const char IGNORE = '#';

void input_proc(void)
{
#if _DEBUG
	freopen("inp1.txt", "r", stdin);
#endif
	scanf("%s", str);
	scanf("%s", explosion);
	while (explosion[exp_size++]);
	exp_size--;
	explosion[exp_size] = -1;
}

void output_proc(void)
{
#if 1
	int erase = 0;
	bool printed = false;
	for (int cnt = 0; str[cnt]; cnt++) {
		erase += bombs_begin[cnt];
		if (erase)
			str[cnt] = IGNORE;
		else {
			printed = true;
			printf("%c", str[cnt]);
		}
		erase -= bombs_end[cnt];
	}


	if (!printed)
		printf("%s\n", "FRULA");
#else
	FILE* fp = fopen("output.txt", "w");
	int erase = 0;
	bool printed = false;
	for (int cnt = 0; str[cnt]; cnt++) {
		erase += bombs_begin[cnt];
		if (erase)
			str[cnt] = IGNORE;
		else {
			printed = true;
			fprintf(fp, "%c", str[cnt]);
		}
		erase -= bombs_end[cnt];
	}
	fprintf(fp, "\n");
	if (!printed)
		fprintf(fp, "%s\n", "FRULA");
	if (fp)
		fclose(fp);

#endif
}

struct suspector {
	int index;
	int explosion_cnt;
};

suspector stack[MAX_STR_LEN + 1] = { 0, };
int stack_cnt = 0;

bool push(const int index, const int explosion_cnt)
{
	if (stack_cnt > MAX_STR_LEN) {
		return false;
	}

	stack[++stack_cnt] = { index, explosion_cnt };
	return true;
}

bool pop(int& index, int& explosion_cnt)
{
	if (stack_cnt < 1)
		return false;

	index = stack[stack_cnt].index;
	explosion_cnt = stack[stack_cnt].explosion_cnt;
	stack[stack_cnt].index = 0;
	stack[stack_cnt--].explosion_cnt = 0;

	return true;
}

void do_something(void)
{
	for (int cnt = 0; str[cnt] ; cnt++) {
		if (str[cnt] == explosion[0]) {
			if (exp_size == 1) {
				bombs_begin[cnt]++;
				bombs_end[cnt]++;
				continue;
			}
			push(cnt, 1);
			continue;
		}
		
		int pos = 0;
		int exp_cnt = 0;
		if (pop(pos, exp_cnt)) {
			if (str[cnt] == explosion[exp_cnt]) {
				exp_cnt++;

				if (exp_cnt == exp_size) {
					bombs_begin[pos]++;
					bombs_end[cnt]++;
				}
				else {
					push(pos, exp_cnt);
				}
				continue; // see the next element
			}
			else {
				while (pop(pos, exp_cnt));
			}
		}
	}
}

#if 1
int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}
#endif