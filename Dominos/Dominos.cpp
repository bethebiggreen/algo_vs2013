#include <cstdio>
#include <iostream>

typedef struct node_t {
	int val;
	int x1, y1, x2, y2;
	node_t(int in_val = -1, int in_x1 = -1, int in_y1 = -1, int in_x2 = -1, int in_y2 = -1) 
		: val(in_val), x1(in_x1), y1(in_y1), x2(in_x2), y2(in_y2)
	{}
} node ;

node node_by_big_order[30]; // Why 30 ?

inline bool is_bigger(const node& a, const node& b)
{
	return (a.val > b.val) ? true : false;
}

inline bool is_smaller(const node& a, const node& b)
{
	return (a.val >= b.val) ? false : true;
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

	//static node* n = node_by_big_order;

	int start = l;
	int pivot = l + 1;
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

	while (start <= end) {
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
			else if(is_equal(n[end], n[pivot]))
			{
				if (end == pivot)
					end--;
				break;
			}
			else
				end--;
		}

		if (start > end) // cross 
		{
			swap(n[pivot], n[end]);
			pivot = end;
			break;
		}
		else {
			swap(n[start], n[end]);
		}
	}

	quick_sort(l, pivot-1,n);
	quick_sort(pivot+1, r,n);
}


int main()
{
	node a[10] = { {-1,0,0,0,0},
 				  {-1,0,0,0,0},
				  {1,0,0,0,0},
				  {0,0,0,0,0},
				  {1, 0, 0, 0, 0},
				  { 1, 0, 0, 0, 0 },
				  {-1, 0, 0, 0, 0 },
				  {-1, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0},
				  {0, 0, 0, 0, 0}};




	quick_sort(0, 9, a);
	return 0;
}
