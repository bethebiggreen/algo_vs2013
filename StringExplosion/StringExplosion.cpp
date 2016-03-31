/*

	https://www.acmicpc.net/problem/9935
    
	0.09 : (in progress) Stack
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

using namespace std;

const int MAX_STR_LEN = 1000000;
const int MAX_EXPLOSION_LEN = 36;

const char IGNORE = '#';
char str[MAX_STR_LEN + 3];
char explosion[MAX_EXPLOSION_LEN + 1];
int exp_size = 0;

void input_proc(void)
{
#if _DEBUG
	freopen("input", "r", stdin);
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
	explosion[exp_size] = -1;
}


void output_proc(void)
{
	int cnt = 0;
	
	bool has_printed = false;
	char output[MAX_STR_LEN] = { 0, };
	int output_idx = 0;
	while (str[cnt]) {
		if (str[cnt] != IGNORE)
			output[output_idx++] = str[cnt];
	}

	char frula[6] = "FRULA";
	frula[5] = '\0';
	cnt = 0;
	if (!output_idx) 
		while(frula[cnt] != '\0')
			output[output_idx++] = frula[cnt++];

#if 0
	printf("%s\n", output);
#else
	FILE* fp = fopen("output.txt", "w");
	fprintf(fp,"%s\n", output);
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
	if (stack_cnt > MAX_STR_LEN)
		return false;
	
	stack[++stack_cnt] = { index, explosion_cnt };
	return true;
}

bool pop(int& index, int& explosion_cnt)
{
	if (stack_cnt < 1)
		return false;
	
	index = stack[stack_cnt].index;
	explosion_cnt = stack[stack_cnt--].explosion_cnt;
	
	return true;
}

void do_something(void)
{
	int cur = 0;
	int exp_cnt = 0;
	while (str[cur]) {
		if (str[cur] == explosion[exp_cnt]) {
			while (1) 
				if(str[cur++] != explosion[exp_cnt++])
					break;

			if (exp_cnt == exp_size) {

			}
			else {
				push(cur, exp_cnt);
			}
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