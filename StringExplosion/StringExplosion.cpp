/*
	https://www.acmicpc.net/problem/9935
    
	0.03 : We will implement similar as linked list.
	       char str[MAX_N] ; // store string
		   int next[MAX_N] ; // store next index 
		   For example, if str stores 'TEST' then, next[0] = 1;, next[1] = 2, so on.
		   Here is bomb scenario, TESTC4C4TEST.
		   TEST[3] stores digit 8 and it helps iterator skips bomb range.

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

using namespace std;

const int MAX_STR_LEN = 1000000;
const int MAX_EXPLOSION_LEN = 36;

char str[MAX_STR_LEN + 1];
char explosion[MAX_EXPLOSION_LEN + 1];

int chunk_begin[MAX_STR_LEN];
int chunk_end[MAX_STR_LEN];
int chunk_cnt = 0;

void input_proc(void)
{
	cin >> str;
	cin >> explosion;
}

void output_proc(void)
{
	int cnt = 0;
	for (int i = 0; i < chunk_cnt; i++)
		for (int j = chunk_begin[chunk_cnt]; j < chunk_end[chunk_cnt]; j++)
			cout << str[j];
}

void do_something(void)
{
	int iter = 0;
	char cur = 0;
	int exp_cnt = 0;
	bool in_checking = false;
	chunk_begin[chunk_cnt] = iter;
	// TEST C4C4TEST end[0] = 4 begin[1] = 6, iter = 6 end[1] = 6  
	// TEST CC44TEST end[0] = 5 
	// TEST C4CC44TEST

	while (0 != (cur = str[iter])) {		
		if (cur == explosion[exp_cnt]) {
			in_checking = true;
			exp_cnt++;
		}
		else {
			in_checking = false;
			exp_cnt = 0;
		}
	}
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}