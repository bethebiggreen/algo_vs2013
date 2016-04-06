#if 1
#include <cstdio>
#include <iostream>

#define __USE_DYNAMIC_MEMORY_ALLOCATION__ 1
using namespace std;

typedef enum node_type_e{
	VERTICAL = 0,
	HORIZONTAL = 1,
} node_type;

typedef struct node_t {
	int val;
	int x1, y1, x2, y2;
	node_type type;
	node_t(int in_val = -1, int in_x1 = -1, int in_y1 = -1, int in_x2 = -1, int in_y2 = -1, node_type in_type = VERTICAL) 
		: val(in_val), x1(in_x1), y1(in_y1), x2(in_x2), y2(in_y2) , type(in_type) {}
} node ;

const int MAX_N = 2001;
int MAX_NODE_SIZE = 0;
const int MAX_DEPTH = 30;
int MAP[MAX_N][MAX_N] = { 0, };
bool VISITED[MAX_N][MAX_N] = { 0, };
int N = 0, K = 0;
int SUM = 0;
int solution = 0;

#if __USE_DYNAMIC_MEMORY_ALLOCATION__
node* node_by_big_order = NULL; 
#else
node node_by_big_order[50];
#endif 

int node_by_big_order_pos = 0;

inline bool is_bigger(const node& a, const node& b)  { return (a.val > b.val)  ? true : false; }
inline bool is_smaller(const node& a, const node& b) { return (a.val > b.val)  ? false : true; }
inline bool is_equal(const node& a, const node& b)   { return (a.val == b.val) ? true : false; }

inline bool swap(node& a, node& b)
{
	node tmp = b;
	b = a;
	a = tmp;
	return true;
}

void quick_sort(int l, int r, node* n)
{
	if (l >= r)
		return;

	int pivot = l;
	int start = l + 1;
	node pivot_node = n[pivot];
	int end = r;

	while (start < end) {
		while (start <= end) {
			if (is_smaller(n[start], n[pivot])) {
				break;
			}
			else
				start++;
		}

		while (start <= end) {
			if (is_bigger(n[end], n[pivot])) {
				break;
			}
			else
				end--;
		}

		if (start <= end)
			swap(n[start], n[end]);
	}

	swap(n[pivot], n[end]);
	pivot = end;
	
	quick_sort(l, pivot-1,n);
	quick_sort(pivot+1, r,n);
}

void input_proc(void)
{
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			SUM += MAP[i][j];
		}
	}
	
	MAX_NODE_SIZE = (2*((N - 1)*(N - 1)) + 2*(N - 1));
#if __USE_DYNAMIC_MEMORY_ALLOCATION__
	node_by_big_order = new node[MAX_NODE_SIZE+2];
#endif
}

const int MIN_INT = 0xFFFFFFFF;
const int MAX_INT = 0x7FFFFFFF;
inline bool add_node(int y, int x, node_type type)
{
	// We will add only bigger node than smallest one, at least.
	int min_val = MAX_INT;
	int min_idx = 0;
	for (int i = 0; i < node_by_big_order_pos; i++) {
		if (node_by_big_order[i].val < min_val) {
			min_val = node_by_big_order[i].val;
			min_idx = i;
		}
	}

	node n;
	switch (type) {
	case HORIZONTAL:
		if (x + 1 < N) 
			n = { MAP[y][x] + MAP[y][x + 1], x, y, x + 1, y, type };
		else 
			return false;
		break;
	case VERTICAL:
		if (y + 1 < N) 
			n = { MAP[y][x] + MAP[y + 1][x], x, y, x, y + 1, type };
		else 
			return false;
		break;
	default:
		break;
	}

	if (node_by_big_order_pos < 30)  
		node_by_big_order[node_by_big_order_pos++] = n;
	else if (min_val < n.val) 
		node_by_big_order[min_idx] = n;
	else
		return false;

	return true;
}

inline bool can_it_put(const node& n)
{
	if (VISITED[n.y1][n.x1] || VISITED[n.y2][n.x2]) 
		return false;
	else
		return true;
}

inline bool mark(const node& n)
{
	if (can_it_put(n)) {
		VISITED[n.y1][n.x1] = true;
		VISITED[n.y2][n.x2] = true;
		return true;
	}
	else
		return false;
}

inline bool unmark(const node& n)
{
	if (!can_it_put(n)) {
		VISITED[n.y1][n.x1] = false;
		VISITED[n.y2][n.x2] = false;
		return true;
	}
	else
		return false;
}

// Brute force is not good way to find a solution in limited time.
void find_max(int value, int num_dominos, int depth)
{
	if (!num_dominos || depth >= MAX_DEPTH) {
		if (solution < value)
			solution = value;
		return;
	}

	const node& n = node_by_big_order[depth];
	if (can_it_put(n)) {
		mark(n);
		find_max(value + n.val, num_dominos - 1, depth + 1);
		unmark(n);
		find_max(value, num_dominos, depth + 1);
	}
	else {
		find_max(value, num_dominos, depth + 1);
	}
}

// Heap can be the best solution for it due to save the memory.
void do_something(void)
{
	// Make all couples
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int type = VERTICAL; type <= HORIZONTAL; type++)
				add_node(i, j, (node_type)type);

	quick_sort(0, node_by_big_order_pos-1, node_by_big_order);
	find_max(0,K,0);
}

void reset(void)
{
#if __USE_DYNAMIC_MEMORY_ALLOCATION__
	if (node_by_big_order)
		delete[] node_by_big_order;
	node_by_big_order = NULL;
#endif

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] = -1;
			VISITED[i][j] = false;
		}
	}
	
	MAX_NODE_SIZE = 0;
	solution = 0;
	SUM = 0;
	node_by_big_order_pos = 0;
}

void output_proc(void)
{
	printf("%d\n", SUM - solution);
}

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int TC_NUM = 0;
	cin >> TC_NUM;
	while (TC_NUM--) {
		input_proc();
		do_something();
		output_proc();
		reset();
	}
	return 0;
}
#else
#include <stdio.h>
#define MAX_N 2000

typedef struct {
	int x;
	int y;
}_point;
typedef struct {
	_point a;
	_point b;
	int val;
}_block;

_block block[2 * MAX_N*MAX_N - 2 * MAX_N];
int block_idx;
int matrix[MAX_N][MAX_N];
int check_matrix[MAX_N][MAX_N];
int N, K;
int sum;
int max_block;
int checked[29];
int partial_sum[29];

int val;
int combi_val;

void add_block(int y1, int x1, int y2, int x2)
{
	if (block_idx == max_block)
	{
		int min_idx = 0;
		for (int i = 1; i < max_block; i++) {
			if (block[i].val < block[min_idx].val)
				min_idx = i;
		}
		if (block[min_idx].val > matrix[y1][x1] + matrix[y2][x2])
			return;
		block[min_idx].val = matrix[y1][x1] + matrix[y2][x2];
		block[min_idx].a.x = x1;
		block[min_idx].a.y = y1;
		block[min_idx].b.x = x2;
		block[min_idx].b.y = y2;
		return;
	}
	else {
		block[block_idx].val = matrix[y1][x1] + matrix[y2][x2];
		block[block_idx].a.x = x1;
		block[block_idx].a.y = y1;
		block[block_idx].b.x = x2;
		block[block_idx++].b.y = y2;
	}
}
void manage_input()
{
	block_idx = 0;
	sum = 0;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &matrix[i][j]);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check_matrix[i][j] = 0;
			sum += matrix[i][j];
		}
	}

	for (int h = 0; h < N; h++)
	{
		for (int w = 0; w < N - 1; w++)
		{
			add_block(h, w, h, w + 1);
		}
	}
	for (int w = 0; w < N; w++)
	{
		for (int h = 0; h < N - 1; h++)
		{
			add_block(h, w, h + 1, w);
		}
	}
}

void combi(int lev, int sum, int idx)
{
	if (lev == K)
	{
		if (val < sum)
			val = sum;
		return;
	}
	for (; idx < max_block; idx++)
	{
		if (checked[idx] == 0)
		{
			if (!check_matrix[block[idx].a.y][block[idx].a.x] && !check_matrix[block[idx].b.y][block[idx].b.x]) {
				checked[idx] = 1;
				check_matrix[block[idx].a.y][block[idx].a.x] = check_matrix[block[idx].b.y][block[idx].b.x] = 1;
				combi(lev + 1, sum + block[idx].val, idx + 1);
				checked[idx] = 0;

				check_matrix[block[idx].a.y][block[idx].a.x] = check_matrix[block[idx].b.y][block[idx].b.x] = 0;
			}
		}
	}


}

int main()
{
	int T;
	freopen("input1.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &N, &K);
		max_block = 1 + (K - 1) * 7;

		manage_input();
		val = 0;
		combi_val = 0;

		combi(0, 0, 0);
		printf("%d\n", sum - val);

	}
	return 0;
}
#endif
