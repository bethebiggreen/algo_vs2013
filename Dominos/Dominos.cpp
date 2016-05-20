#if 1
#include <stdio.h>
#include <iostream>

#define __USE_DYNAMIC_MEMORY_ALLOCATION__ 0
using namespace std;

typedef enum node_type_e {
	VERTICAL = 0,
	HORIZONTAL = 1,
} node_type;

typedef struct node_t {
	int val;
	int x1, y1, x2, y2;
	node_type type;
	node_t(int in_val = -1, int in_x1 = -1, int in_y1 = -1, int in_x2 = -1, int in_y2 = -1, node_type in_type = VERTICAL)
		: val(in_val), x1(in_x1), y1(in_y1), x2(in_x2), y2(in_y2), type(in_type) {}
} node;

const int MAX_N = 2001;
int MAX_NODE_SIZE = 0;
int MAX_DEPTH = 0;

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

inline bool is_bigger(const node& a, const node& b) { return (a.val > b.val) ? true : false; }
inline bool is_smaller(const node& a, const node& b) { return (a.val > b.val) ? false : true; }
inline bool is_equal(const node& a, const node& b) { return (a.val == b.val) ? true : false; }

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

	quick_sort(l, pivot - 1, n);
	quick_sort(pivot + 1, r, n);
}

void input_proc(void)
{
	// scanf("%d %d", &N, &K);
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			// scanf("%d", &MAP[i][j]);
			cin >> MAP[i][j];
			SUM += MAP[i][j];
		}
	}

	MAX_NODE_SIZE = (2 * ((N - 1)*(N - 1)) + 2 * (N - 1));
#if __USE_DYNAMIC_MEMORY_ALLOCATION__
	node_by_big_order = new node[MAX_NODE_SIZE + 2];
#endif
	MAX_DEPTH = (MAX_NODE_SIZE < 10) ? MAX_NODE_SIZE : 10;
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
	if (!num_dominos) {
		if (solution < value)
			solution = value;
		return;
	}

	for (int i = depth; i < node_by_big_order_pos; i++) {
		const node& n = node_by_big_order[i];
		if (!VISITED[n.y1][n.x1] && !VISITED[n.y2][n.x2]) {
			VISITED[n.y1][n.x1] = true;
			VISITED[n.y2][n.x2] = true;
			find_max(value + n.val, num_dominos - 1, depth + 1);
			VISITED[n.y1][n.x1] = false;
			VISITED[n.y2][n.x2] = false;
		}

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


	quick_sort(0, node_by_big_order_pos - 1, node_by_big_order);
	find_max(0, K, 0);
}

void reset(void)
{
#if __USE_DYNAMIC_MEMORY_ALLOCATION__
	if (node_by_big_order)
		delete[] node_by_big_order;
	node_by_big_order = NULL;
#endif
#if 0
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] = -1;
			VISITED[i][j] = false;
		}
	}
#endif
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
	freopen("inp1.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	int TC_NUM = 0;
	//scanf("%d", &TC_NUM);
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
#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;

struct domino
{
	int x1, y1;
	int x2, y2;
	int sum;
};

const int MAX_COUNT = 2000;
const int MAX_COMBI = 29;

int N, K, total;
int g_data[MAX_COUNT + 1][MAX_COUNT + 1];
int visited[MAX_COUNT + 1][MAX_COUNT + 1];
int domino_count = 0;
struct domino domino_array[MAX_COMBI];
int MAX_SUM = 0;

void addDomino(int x1, int y1, int x2, int y2)
{
	domino tmp;
	tmp.x1 = x1;
	tmp.y1 = y1;
	tmp.x2 = x2;
	tmp.y2 = y2;
	tmp.sum = g_data[x1][y1] + g_data[x2][y2];

	if (domino_count == 0)
	{
		domino_array[0] = tmp;
		domino_count++;
		return;
	}

	if (domino_count >= MAX_COMBI && domino_array[MAX_COMBI - 1].sum >= tmp.sum) return;

	for (int i = 0; i < domino_count; i++)
	{
		if (domino_array[i].sum < tmp.sum)
		{
			int start = (domino_count == MAX_COMBI) ? MAX_COMBI - 1 : domino_count;
			for (int j = start; j > i; j--)
			{
				domino_array[j] = domino_array[j - 1];
			}
			domino_array[i] = tmp;
			if (domino_count < MAX_COMBI) domino_count++;
			return;
		}
	}

	domino_array[domino_count] = tmp;
	domino_count++;

	return;
}
int times = 0;
void Recursive(int count, int total_sum)
{
	times++;
	int x1, y1, x2, y2, sum;

	if (MAX_SUM < total_sum) MAX_SUM = total_sum;
	if (count >= K) return;

	for (int i = 0; i < domino_count; i++)
	{
		x1 = domino_array[i].x1;
		y1 = domino_array[i].y1;
		x2 = domino_array[i].x2;
		y2 = domino_array[i].y2;
		sum = domino_array[i].sum;

		if (!visited[x1][y1] && !visited[x2][y2])
		{
			visited[x1][y1] = 1;
			visited[x2][y2] = 1;
			Recursive(count + 1, total_sum + sum);
			visited[x1][y1] = 0;
			visited[x2][y2] = 0;
		}
	}

}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("inp1.txt", "r", stdin);

	std::ios::sync_with_stdio(false);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		printf("Starting adding input\n");
		clock_t begin = clock();

		cin >> N >> K;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> g_data[i][j];
				total += g_data[i][j];
				visited[i][j] = 0;
			}
		}

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (j + 1 <= N) addDomino(i, j, i, j + 1);
				if (i + 1 <= N) addDomino(i, j, i + 1, j);
			}
		}

	
		Recursive(0, 0);
		printf("Time lapsed in %lf seconds\n", double(clock() - begin) / CLOCKS_PER_SEC);
		cout << total - MAX_SUM << ", " << times << " times" << endl;

		total = 0;
		MAX_SUM = 0;
		domino_count = 0;
	}


	return 0;
}
#endif
