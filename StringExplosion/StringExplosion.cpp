/*
	https://www.acmicpc.net/problem/9935
    
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

using namespace std;

const int MAX_STR_LEN = 1000000;
const int MAX_EXPLOSION_LEN = 36;

char str[MAX_STR_LEN + 3];
char explosion[MAX_EXPLOSION_LEN + 1];
int next_idx[MAX_STR_LEN + 2];
int prev_idx[MAX_STR_LEN + 2];
const char IGNORE = '#';
int exp_size = 0;

void input_proc(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif

#if 0
	cin >> str+1;
	cin >> explosion;
#else
	scanf("%s", str + 1);
	scanf("%s", explosion);
#endif
	while (explosion[exp_size++]);
	exp_size--;
	for (int i = 0; i < MAX_STR_LEN; i++) {
		next_idx[i] = i + 1;
		prev_idx[i] = i - 1;
	}
	explosion[exp_size] = -1;
	str[0] = -1;
}

void output_proc(void)
{
#if _DEBUG
	FILE* fp = fopen("output.txt", "w");
#endif
	int cnt = 0;
	bool has_printed = false;
	while (str[cnt]) {
		if (str[cnt] != -1) {
			// cout << str[cnt];
			printf("%c", str[cnt]);
			// fprintf(fp, "%c", str[cnt]);
			has_printed = true;
		}
		cnt = next_idx[cnt];
	}

	if (!has_printed) {
		//cout << "FRULA";
		printf("FRULA");
	}
}

void do_something(void)
{
	int cur = 1;
	while (str[cur]) {
		int exp_cnt = 0;
		if (str[cur] == explosion[exp_cnt]) {
			int tmp = next_idx[cur];
			while (str[tmp] == explosion[++exp_cnt])
				tmp = next_idx[tmp];
			if (exp_size == exp_cnt) {
				next_idx[prev_idx[cur]] = tmp;
				prev_idx[tmp] = prev_idx[cur];
			}
			else {
				cur = next_idx[cur];
				exp_cnt = 0;
				continue;
			}
			exp_cnt = 0;
			int iter = 0;
			while(iter++ < exp_size || -1 != prev_idx[cur])
				cur = prev_idx[cur];
		}
		else {
			cur = next_idx[cur];
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