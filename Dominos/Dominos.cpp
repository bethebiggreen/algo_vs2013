#if 0
#include <stdio.h>
#include <iostream>
#define _USE_DYNAMIC_MEMORY_ 1

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
		: val(in_val), x1(in_x1), y1(in_y1), x2(in_x2), y2(in_y2) , type(in_type)
	{}

} node ;

int TC_NUM = 0;
const int MAX_N = 2001;
int MAP[MAX_N][MAX_N];
int N = 0, K = 0;
int MAX_NODE_SIZE = 0;
int SUM = 0;
const int MAX_DEPTH = 35; // heuristic

int answer = 0;
bool visited[MAX_DEPTH] = { false, };
bool visited_map[MAX_N][MAX_N] = { false, };

#if _USE_DYNAMIC_MEMORY_
node* node_by_big_order = NULL;
#else
node node_by_big_order[50];
#endif

int node_by_big_order_pos = 0;

inline bool is_bigger(const node& a, const node& b)
{
	return (a.val > b.val) ? true : false;
}

inline bool is_smaller(const node& a, const node& b)
{
	return (a.val > b.val) ? false : true;
}

inline bool is_equal(const node& a, const node& b)
{
	return (a.val == b.val) ? true : false;
}

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
	
	MAX_NODE_SIZE = 2*(2*((N - 1)*(N - 1)) + 2*(N - 1));
#if _USE_DYNAMIC_MEMORY_
	node_by_big_order = new node[MAX_NODE_SIZE];
#endif
}


inline bool add_node(int y, int x, node_type type)
{
	switch (type) {
	case HORIZONTAL:
		if (x + 1 < N) 
			node_by_big_order[node_by_big_order_pos++] = { MAP[y][x] + MAP[y][x + 1], x, y, x+1, y, type };
		break;
	case VERTICAL:
		if (y + 1 < N)
			node_by_big_order[node_by_big_order_pos++] = { MAP[y][x] + MAP[y+1][x], x, y, x, y+1, type };
		break;
	default:
		break;
	}
	return true;
}

inline bool is_it_possible(const node& n)
{
	if (visited_map[n.y1][n.x1] || visited_map[n.y2][n.x2])
		return false;
	else
		return true;
}

inline bool mark(const node& n)
{
	if (is_it_possible(n)) {
		visited_map[n.y1][n.x1] = true;
		visited_map[n.y2][n.x2] = true;
		return true;
	}
	else
		return false;
}

inline bool unmark(const node& n)
{
	if (!is_it_possible(n)) {
		visited_map[n.y1][n.x1] = false;
		visited_map[n.y2][n.x2] = false;
		return true;
	}
	else
		return false;
}

inline int my_max(int a, int b)
{
	return (a > b) ? a : b;
}

inline int my_min(int a, int b)
{
	return (a > b) ? b : a;
}


// 3 1 2 4
// 3 1 2
// 3 1   4
// 3   2 4
//   1 2 4
void find_max(int value, int num_dominos, int depth)
{
	if (!num_dominos || depth >= 30) {
		if (answer < value)
			answer = value;
		return;
	}

	// 지금 것을 고를수 있으면 고르고 넘어가고.. 아니면 못고르고 넘어감...
	if (is_it_possible(node_by_big_order[depth])) {
		mark(node_by_big_order[depth]);
		find_max(value + node_by_big_order[depth].val, num_dominos - 1, depth + 1);
		unmark(node_by_big_order[depth]);
		find_max(value, num_dominos, depth + 1);
	}
	else {
		find_max(value, num_dominos, depth + 1);
	}
}
// Heap can be the best solution for it due to save the memory.
void do_something(void)
{
	// Make all coup
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int type = VERTICAL; type <= HORIZONTAL; type++)
				add_node(i, j, (node_type)type);

	// Sort by order
	quick_sort(0, MAX_NODE_SIZE/2 - 1, node_by_big_order);
	find_max(0, K, 0);
}

void reset(void)
{

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MAP[i][j] = -1;
			visited_map[i][j] = false;
		}
	}

	for (int i = 0; i < MAX_DEPTH; i++)
		visited[i] = false;

	MAX_NODE_SIZE = 0;
	answer = 0;

#if _USE_DYNAMIC_MEMORY_
	if (node_by_big_order)
		delete[] node_by_big_order;
	node_by_big_order = NULL;
#else
	for (int i = 0; i < MAX_DEPTH; i++)
		node node_by_big_order[i] = { -1,-1,-1,-1,-1 };
#endif
	node_by_big_order_pos = 0;

}

void output_proc(void)
{
	printf("%d\n", answer);
}


int main()
{
#if _DEBUG
	freopen("inp1.txt", "r", stdin);
#endif
	int tc_num = 0;
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
int datum[MAX_COUNT + 1][MAX_COUNT + 1];
int visited[MAX_COUNT + 1][MAX_COUNT + 1];
int domino_count = 0;
struct domino domino_array[MAX_COMBI];
int MAX_SUM = 0;
int called_adddomino = 0;
void addDomino(int x1, int y1, int x2, int y2)
{
	called_adddomino++;
	domino tmp;
	tmp.x1 = x1;
	tmp.y1 = y1;
	tmp.x2 = x2;
	tmp.y2 = y2;
	tmp.sum = datum[x1][y1] + datum[x2][y2];

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

void Recursive(int count, int total_sum)
{
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

		cin >> N >> K;
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> datum[i][j];
				total += datum[i][j];
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
		cout << total - MAX_SUM << endl;

		total = 0;
		MAX_SUM = 0;
		domino_count = 0;
		printf("addDomino is called %d times\n", called_adddomino);
		called_adddomino = 0;
	}


	return 0;
}
#endif