#include <stdio.h>

// NO SPACES ARE ALLOWED

const int MAX_COMMAND_NUM = 500000;
const int MAX_CHARS = 100000;

char line[MAX_CHARS] = { 0, };
int line_pos = -1;

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
}

typedef enum e_mode{
	EDIT = 0 ,
	NAV = 1
} mode;

inline bool backspacing(int num)
{
	int start_pos = ((line_pos - num) < 0 ) ? 0 : (line_pos - num);
	int num_copied = line_pos - start_pos;

	for (int i = 0; i < num_copied; i++) 
		line[start_pos + i] = line[line_pos + i];
	
	for (int i = line_pos + num_copied; i > num_copied; i--)
		line[i] = '\0';
	
	return true;
}

inline bool paste(void)
{
	int start_copy_pos_of_current_str = ((line_pos + stack_pos) > MAX_CHARS - 1) ? (line_pos+stack_pos): MAX_CHARS - 1;

	for (int i = 0; i < num_copied; i++) 
		line[start_pos + i] = line[line_pos + i];
	
	for (int i = line_pos + num_copied; i > num_copied; i--)
		line[i] = '\0';
	
	return true;
}
void do_something(void)
{
	const static char PASTE = 'P';
	const static char LEFT = 'L';
	const static char RIGHT = 'D';
	const static char BACKSPACE = 'B';

	int cnt = 0;
	char cmd_line[4] = { 0, };
	char command = 0;
	char arg = 0;
	char prev_cmd = 0;
	int pos_diff = 0;

	int optimization_mode = 0;
	
	// Moving cursor is not a big burden.
	while (cnt++ < command_num) {
		scanf("%s\n", cmd_line);
		command = cmd_line[0];
		arg = cmd_line[2];
		switch (command) {
		case PASTE : // 
			scanf("%c", &arg);
			if (stack_pos == -1)
				optimization_mode = PASTE;
			stack[++stack_pos] = arg;
			break;
		case LEFT : // TRIGGERING EDIT MODE
			if (optimization_mode == BACKSPACE)
				backspacing(num_of_backspace);
			optimization_mode = LEFT;
			line_pos++;
			break;
		case RIGHT : // TRIGGERING EDIT MODE
			optimization_mode = RIGHT;
			line_pos--;
			break;
		case BACKSPACE: // KEEP TYPING BACKSPACE CAN BE TREATED IN ONE EXECUTION.
			if (stack_pos == -1)
				optimization_mode = BACKSPACE;
			if (optimization_mode == BACKSPACE)
				num_of_backspace++;
			else if(optimization_mode == PASTE)
				stack_pos--;
			break;
		default :
			break;
		}
		prev_cmd = command;
	}

	switch (optimization_mode) {
	case PASTE: // 
		break;
	case BACKSPACE: // KEEP TYPING BACKSPACE CAN BE TREATED IN ONE EXECUTION.
		backspacing(num_of_backspace);
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
	freopen("input.txt", "r", stdin);
	input_proc();
	do_something();
	output_proc();
	return 0;
}