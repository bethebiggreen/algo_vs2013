#include <cstdio>
#include <iostream>

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
const int MAX_N = 2000;
int MAP[MAX_N][MAX_N];
int N = 0, K = 0;
int MAX_NODE_SIZE = 0;

// node* node_by_big_order; // Why 30 ?
node node_by_big_order[50]; // Why 30 ?
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

// left -> greater
// right -> lesser 
// -> equal to 
//           p           l    r      
//    -1 ,   -1,   -1,   0 , -1
void quick_sort(int l, int r, node* n)
{
	if (l >= r)
		return;

	//static node* n = node_by_big_order;

	int pivot = l;
	int start = l + 1;
	node pivot_node = n[pivot];
	int end = r;

	// For covering all cases!
	// Legacy algorithm cares only bigger and lesser, so algorithm does not have clear idea for same value as pivot.
	// Goal : Every try makes a partitione like below
	//       | Lesser and equal to PIVOT |  PIVOT  | Greater than PIVOT 
	// 1. From left, two things are stop-triggers. Otherwise, start will be increased.
	//   1) Once it meets greater number.
	//   2) Once 'start', which is assigned from left initially, is over 'end'.
	// 2. From right, three things are stop-triggers.
	//   1) Once it meets lesser number.
	//   2) Once 'end', which is assigned from right initially, is under 'start'.
	//   3) Once it meets pivot. However this case, 'end' should be decreased to avoid dead-lock.
	//      (Our pivot is always next to left, so we could conclude while loop after it.) 
	// 
	// For swapping cases
	// 1. 'start' is over 'end'.
	//  1) 'end' swaps with 'pivot'.
	// 2. Otherwise,
	//  1) 'start' is far from 'end'. We would swap between 'start' and 'end'.
	//  2) 'start' is same as 'end'. It would swap each other, however there is nothing changed in a conclusion.
	//     After this, the loop will be broken. 
	//  3) 'start' is over 'end'. We would swap between 'end' and 'pivot', and next recursion is expected.
	//
	// * Aware that over and under are not including 'equal to'.
    // * Swapping 'is_smaller' and 'is_bigger' effects in-versa- ordering.

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
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> MAP[i][j];
	
	MAX_NODE_SIZE = 2*(2*((N - 1)*(N - 1)) + 2*(N - 1));
	// node_by_big_order = new node[MAX_NODE_SIZE];
}


inline bool add_node(int y, int x, node_type type)
{
	switch (type) {
	case HORIZONTAL:
		if (x+1 < N - 1 && y < N - 1) 
			node_by_big_order[node_by_big_order_pos++] = { MAP[y][x] + MAP[y][x + 1], x, y, x+1, y, type };
		break;
	case VERTICAL:
		if (x < N - 1 && y + 1 < N - 1)
			node_by_big_order[node_by_big_order_pos++] = { MAP[y][x] + MAP[y+1][x], x, y, x, y+1, type };
		break;
	default:
		break;
	}
	return true;
}

// Heap can be the best solution for it due to save the memory.
void do_something(void)
{
	// Make all coup
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int type = VERTICAL; type <= HORIZONTAL; type++)
				add_node(i, j, (node_type)type);


	node a[5] = { {-1,0,0,0,0},
				  { 0,0,0,0,0},
				  {-1,0,0,0,0},
				  {-1,0,0,0,0},
				  {-1,0,0,0,0} };
	// Sort by order
	quick_sort(0, MAX_NODE_SIZE/2 - 1, node_by_big_order);


}

void reset(void)
{
	/*
	if (node_by_big_order)
		delete[] node_by_big_order;
	node_by_big_order = NULL;
	*/

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			MAP[i][j] = -1;
	MAX_NODE_SIZE = 0;
}


void output_proc(void)
{

}

int main()
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
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
