#include <stdio.h>

// NO SPACES ARE ALLOWED

const int MAX_COMMAND_NUM = 500000;
const int MAX_CHARS = 100000;

char line[MAX_CHARS] = { 0, };
int line_pos = 0;

char tmp[MAX_CHARS] = { 0, };
int tmp_pos = 0;

int stack[MAX_COMMAND_NUM] = { 0, };
int stack_pos = 0;
int command_num = 0;

void input_proc(void)
{
	scanf("%s", line);
	scanf("%d", &command_num);
}

void do_something(void)
{
	const static char PASTE = 'P';
	const static char LEFT = 'L';
	const static char RIGHT = 'D';
	const static char BACKSPACE = 'B';

	int cnt = 0;
	char command = 0;
	char arg = 0;
	char prev_cmd = 0;
	int pos_diff = 0;
	while (cnt < command_num) {
		scanf("%c", &command);
		switch (command) {
		case PASTE :
			scanf("%c", &arg);
			break;
		case LEFT :
			if (prev_cmd == LEFT || prev_cmd == RIGHT) {

			}
			break;
		case RIGHT :
			break;
		case BACKSPACE:
			break;
		default :
			break;
		}
		prev_cmd = command;
	}
}

void output_proc(){}


int main(void)
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}