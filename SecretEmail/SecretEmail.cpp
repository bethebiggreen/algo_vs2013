/*

0.01 This problem is from https://www.acmicpc.net/problem/2999 , http://hsin.hr/coci/archive/2007_2008/ .
     Simple algorithm seems below,
	 1. Find the smallest R(row) which is satifsfied with condition that R is bigger than C(column).
	 2. Outer for loop runs c < COL, 
	    Inner for loop runs r < ROW,
		an execution is Num of ROW * r(icremental) + Num of COL * c(incremental)
   
*/
#include <iostream>
using namespace std;

const int MAX_N = 100+1;
char input[MAX_N] = { 0, };
char output[MAX_N] = { 0, };
void input_proc(void)
{
	freopen("input.txt", "r", stdin);
	cin >> input;
}

inline int get_size(const char* str)
{
	int size = 0;
	while(str[size++] != 0);
	return size-1;
}

inline void get_row_col(const int& size, int& row, int& col)
{
	for (int r = size; r >= 0; r--) {
		if (0 == (size % r)) {
			if (r < size / r)
				return;
			else {
				row = r;
				col = size / r;
			}
		}
	}
}

void do_something(void)
{
	int size = get_size(input);
	int row = 0;
	int col = 0;
	get_row_col(size, row, col);

	int cnt = 0;
	for (int c = 0; c < col; c++) {
		for (int r = 0; r < row; r++) {
			output[cnt++] = input[r*col + c];
		}		
	}
}

void output_proc(void)
{
	cout << output;
}

int main()
{
	input_proc();
	do_something();
	output_proc();
	return 0;
}