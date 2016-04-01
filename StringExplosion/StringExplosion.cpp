/*

	https://www.acmicpc.net/problem/9935
    
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

using namespace std;

const int MAX_STR_LEN = 20;
const int MAX_EXPLOSION_LEN = 36;

const char IGNORE = '#';
char str[MAX_STR_LEN + 3];
char explosion[MAX_EXPLOSION_LEN + 1];
int exp_size = 0;

struct bomb {
	int pos;
	int len;
	bomb(int in_pos = -1, int in_len = -1) : pos(in_pos), len(in_len) {}
};

bomb bombs[MAX_STR_LEN + 2];
int bomb_cnt = 0;

void input_proc(void)
{
#if _DEBUG
	freopen("inp1.txt", "r", stdin);
#endif

#if 0
	cin >> str;
	cin >> explosion;
#else
	scanf("%s", str);
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
	char output[MAX_STR_LEN+2] = { 0, };
	int output_idx = 0;

	// b[0] = { 1, 3 }
	// b[1] = { 5, 7 }
	// 0-1, 
	if(bomb_cnt) {
		int prev_end = 0;
		for (int i = 0; i < bomb_cnt; i++) {
			bomb& b = bombs[i];
			for (int j = prev_end; j < b.pos ;j++)
				output[output_idx++] = str[j];
			prev_end = b.pos + b.len + 1;
		}

		while(str[prev_end])
			output[output_idx++] = str[prev_end++];
	}
	else
	{
		printf("%s\n", str);
	}

	char frula[6] = "FRULA";
	frula[5] = '\0';
	cnt = 0;
	if (!output_idx) 
		while(frula[cnt] != '\0')
			output[output_idx++] = frula[cnt++];

#if 1
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

// aC4C4a
// aCC44a
// aBABADDa
// aBABADBADBACDB  다음 칸의 것이 새로운 폭발물이 있을때는 무조건 PUSH. 터지는 도중에도 PUSH 가 되어야 함..망할.
// aBABADBADBACDB

// explosion 아니고, bomb 도 아니고... 뭐야?
// AM_I_IN_STACK 함수로 연결성 검사
// POP은, 완전히 연결성이 없을때 -> 새롭게 시작되는게 첫 글자가 아닐때, 또는 NULL terminator 일때.. -1 넣자.
// POP 이 최초 실행되기전에, 진행되던 것이 폭발인지 아닌지 알아야한다.폭발물일때는, 
// POP 은 폭발물이고 그 뒤 문자가 새롭게 시작되는 문자가 아닐떄 일어나야 한다.
// STACK UNWINDING 중 맞지 않는 문자가 하나라도 생기면 다 밀어버림.
// BADBADBAD? ""
// aBBABADBADDAD
// a############BADD

/*
  
*/




void do_something(void)
{
	int cur = 0;
	int exp_cnt = 0;
	int bomb_begin = 0;
	while (str[cur]) {
		if (str[cur] == explosion[exp_cnt]) {
			if (exp_cnt == 0) // 이전 loop 에서 폭발물에 대한 정보가 없는 경우
				bomb_begin = cur;
			cur++, exp_cnt++;

			bool is_bomb = false;
			while (1) {
				// 폭발물을 계속 검사함. explosion 의 마지막은 -1 이기에, 조건문이 끝난후
				// exp_cnt 는 exp_size 이상일 경우는 없음.
				if (exp_cnt == exp_size) {
					is_bomb = true;
					break;
				}

				if (str[cur] != explosion[exp_cnt])
					break;
				else
					cur++, exp_cnt++;
			}

			// 폭발물은 아니지만, 폭발물일 가능성이 있는 경우
			if (!is_bomb && str[cur] && explosion[0]) {
				push(bomb_begin, exp_cnt);
				exp_cnt = 0;
				continue;
			}
			else if (is_bomb) {
				bomb& b = bombs[bomb_cnt];
				b.pos = bomb_begin;
				b.len += exp_cnt; // Aware of num of exp_cnt
				if (str[cur] == explosion[0]) { // 연속 폭발 대비 BA BAD BAD D 에서 마지막 D 를 처리해주려면.. 
					exp_cnt = 0;
					continue;
				}
				int trash = -1;
				int popped_bomb_pos, popped_bomb_cnt;
				// pop 에서 이전 폭발물 후보가 있으면, 같이 검사해야. 이전 정보를 pop 해서 세팅하고,
				// 이 정보가 맞다면, 진행함.
				if (pop(popped_bomb_pos, popped_bomb_cnt)) {
					bomb_begin = popped_bomb_pos;
					exp_cnt = popped_bomb_cnt;

					// POP 을 해서 살짝 검사해봤는데, 얘가 candidate 이 아니라면 이전 stack 다 무너뜨림
					if (str[cur] != explosion[popped_bomb_cnt]) {
						while (pop(trash, trash));
						bomb_cnt++;
						exp_cnt = 0;
						continue;
					}
					else
						continue;

				}
				else {// pop 이 없다면, 처음부터 explosion 정보는 리셋.
					bomb_cnt++;
					exp_cnt = 0;
					continue;
				}
			}
		}
		else
			cur++;

	}
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}