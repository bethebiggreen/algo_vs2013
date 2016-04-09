/*
It would be much slower if my stack keeps an array which is not linked-list.
*/
#include <stdio.h>

// NO SPACES ARE ALLOWED
const int MAX_COMMAND_NUM = 500000+1;
const int MAX_CHARS = 100000+1;

char line[MAX_CHARS] = { 0, };
int line_pos = -1;
int line_len = 0;

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

// line_pos : A current position of string. This position is used for adding new char.
// line_len : A length of string. It would get same value as line_pos if cursor is in right-most.
// num_of_backspace : In order to handle continuous backspace behaviours, this value is increased by every 'B'.
inline bool backspacing(void)
{
	// target_pos : This value stores future-line_pos after backspacing. Due to save performance, under 0 is treated as 0.
	// num_copies : A times of occurrence of copy to backspace.
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
	// This loop copies every character to position by adding stack_pos.
	for (int i = 0; i < (line_len - line_pos); i++) 
		line[line_len + stack_pos - i] = line[line_len - i - 1];
	
	// This loop copies every character , belongs to stack , to line_pos.
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
	
	while (cnt++ < command_num) {
		scanf("%[^\n]\n", cmd_line);
		command = cmd_line[0];
		arg = cmd_line[2];
		switch (command) {
		case PASTE : 
			// backspacing is needed to resolve from beginning of PASTE MODE.
			if (stack_pos == -1 && optimization_mode == BACKSPACE)
				backspacing();
			if (stack_pos == -1)
				optimization_mode = PASTE;
			// stack is storing chracter(s) temporary.
			if(optimization_mode == PASTE)
				stack[++stack_pos] = arg;
			break;
		case LEFT : 
			if (optimization_mode == BACKSPACE)
				backspacing();
			else if (optimization_mode == PASTE)
				paste();
			optimization_mode = LEFT;
			if(line_pos != 0)
				line_pos--;
			break;
		case RIGHT : 
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

	// Resolving remaining job.
	switch (optimization_mode) {
	case PASTE: 
		paste();
		break;
	case BACKSPACE: 
		backspacing();
		break;
	default:
		break;
	}
}

void output_proc()
{
#if 0/_DEBUG
	FILE* fp = fopen("output.txt", "w");
	fprintf(fp, "%s\n",line);
	if (fp)
		fclose(fp);
#else
	line[line_len] = '\0';
	printf("%s\n", line);
#endif
}

#if 1

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
#endif