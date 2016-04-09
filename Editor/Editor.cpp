/*
1. TEST CASES
MAX 10 chars, INPUT 3 chars 'abc', MAXLINE 6
	1) EXCEED MAX CHRAS
		Never happened.
	2) UNDER ZERO
abc
5
B
B
B
B
B
	3) L, D during PB to exceed or go under.
abc
13
B
P d
L
P e
L
L
L
L
D
P f
P g
D
B
-> ab, abd, abed, afgbed, afged 



1. TEST CASE
-
abc
P a
B
B
P a

*/

#include <stdio.h>

// NO SPACES ARE ALLOWED

const int MAX_COMMAND_NUM = 500000;
const int MAX_CHARS = 100000;

char line[MAX_CHARS] = { 0, };
int line_pos = -1;
int line_len = 0;

char tmp[MAX_CHARS] = { 0, };
int tmp_pos = -1;

int stack[MAX_COMMAND_NUM] = { 0, };
int stack_pos = -1;
int command_num = 0;

int num_of_backspace = 0;
void input_proc(void)
{
	scanf("%s\n", line);
	scanf("%d\n", &command_num);
	while (line[++line_pos]);
	line_len = line_pos;
}

typedef enum e_mode{
	EDIT = 0 ,
	NAV = 1
} mode;

inline bool backspacing(void)
{
	int target_pos = ((line_pos - num_of_backspace) < 0 ) ? 0 : (line_pos - num_of_backspace);
	int num_copies = line_pos - target_pos;

	for (int i = 0; i < num_copies; i++) 
		line[line_pos-num_copies+i] = (line_pos + i < line_len) ? line[line_pos + i] : '\0';
	
	line_pos -= num_copies;
	line_len -= num_copies;
	num_of_backspace = 0;

	return true;
}

inline bool paste(void)
{
	for (int i = 0; i < (line_len - line_pos); i++) 
		line[line_len + stack_pos - i] = line[line_len - i - 1];
	
	for (int i = 0; i < (stack_pos + 1); i++)
		line[line_pos + i] = stack[i];

	line_pos += (stack_pos+1);
	line_len += (stack_pos+1);
	stack_pos = -1;
	return true;
}

void do_something(void)
{
	const static char PASTE = 'P';
	const static char LEFT = 'L';
	const static char RIGHT = 'D';
	const static char BACKSPACE = 'B';

	int cnt = 0;
	char cmd_line[5] = { 0, };
	char command = 0;
	char arg = 0;
	char prev_cmd = 0;
	int pos_diff = 0;

	int optimization_mode = 0;
	
	// Moving cursor is not a big burden.
	while (cnt++ < command_num) {
		scanf("%[^\n]\n", cmd_line);
		command = cmd_line[0];
		arg = cmd_line[2];
		switch (command) {
		case PASTE : // 
			if (stack_pos == -1 && optimization_mode == BACKSPACE)
				backspacing();
			if (stack_pos == -1)
				optimization_mode = PASTE;
			if(optimization_mode == PASTE)
				stack[++stack_pos] = arg;
			break;
		case LEFT : // TRIGGERING EDIT MODE
			if (optimization_mode == BACKSPACE)
				backspacing();
			else if (optimization_mode == PASTE)
				paste();
			optimization_mode = LEFT;
			if(line_pos != 0)
				line_pos--;
			break;
		case RIGHT : // TRIGGERING EDIT MODE
			if (optimization_mode == BACKSPACE)
				backspacing();
			else if (optimization_mode == PASTE)
				paste();
			optimization_mode = RIGHT;
			if(line_len != line_pos)
				line_pos++;
			break;
		case BACKSPACE: // KEEP TYPING BACKSPACE CAN BE TREATED IN ONE EXECUTION.
			if (stack_pos == -1)
				optimization_mode = BACKSPACE;
			if (optimization_mode == BACKSPACE)
				num_of_backspace++;
			else if (optimization_mode == PASTE) 
				stack[stack_pos--] = '\0';
			break;
		default :
			break;
		}
		prev_cmd = command;
	}

	switch (optimization_mode) {
	case PASTE: // 
		paste();
		break;
	case BACKSPACE: // KEEP TYPING BACKSPACE CAN BE TREATED IN ONE EXECUTION.
		backspacing();
		break;
	default:
		break;
	}
}

void output_proc()
{
	printf("%s\n", line);
}


int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	input_proc();
	do_something();
	output_proc();
	return 0;
}