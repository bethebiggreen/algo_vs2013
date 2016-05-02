/*
7
0110100
0110101
1110101
0000111
0100000
0111110
0111000
*/
#include <stdio.h>

const int MAX_N = 26;
int length[(MAX_N + 1) * (MAX_N +1)];
int sorted_length[(MAX_N + 1) * (MAX_N +1)];

char map[MAX_N + 1][MAX_N + 1];
int check_map[MAX_N + 1][MAX_N + 1];
int N = 0;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = { 0, 1, 0,-1};

void input_proc(void)
{
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) 
			scanf("%c", &map[i][j]);
		scanf("\n");
	}
}

typedef struct pos {
	int x, y;
};

pos q[1024 * 1024*10];
int head = 0, tail = -1;

int add_q(const pos cur,const int cnt)
{
	length[cnt]++;
	q[++tail] = cur;
	return tail;
}

bool pop_front(pos& cur)
{
	if (head > tail)
		return false;

	cur = q[head++];
	return true;
}

void bfs(int x, int y, int cnt)
{
	pos cur = { x,y };
	check_map[y][x] = true;
	add_q(cur,cnt);

	while (pop_front(cur)) {
		for (int i = 0; i < 4; i++) {
			x = cur.x + dx[i];
			y = cur.y + dy[i];
			if (x < 0 || x >= N)
				continue;
			if (y < 0 || y >= N)
				continue;

			if (!check_map[y][x] && map[y][x] == '1') {
				check_map[y][x] = true;
				add_q({ x, y },cnt);
			}
		}
	}
}

void merge_sort(int l, int r)
{
	if (l >= r)
		return;

	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);

	int s1 = l;
	int s2 = mid+1;

	int cnt = l;
	while (s1 <= mid && s2 <= r) {
		if (length[s1] < length[s2]) 
			sorted_length[cnt++] = length[s1++];
		else 
			sorted_length[cnt++] = length[s2++];
	}

	int left = (s1 == mid+1) ? s2 : s1;
	
	while (cnt <= r) 
			sorted_length[cnt++] = length[left++];
	
	for (int i = l; i <= r; i++)
		length[i] = sorted_length[i];
}

void do_something(void)
{
	int cnt = 0;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (!check_map[row][col] && map[row][col] == '1') {
				bfs(col, row, cnt++);
			}
		}
	}
	printf("%d\n", cnt);
	merge_sort(0, cnt-1);
	for (int i = 0; i < cnt; i++)
		printf("%d\n", length[i]);
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	// merge_sort(0, MAX_N - 1);
	input_proc();
	do_something();
	return 0;
}