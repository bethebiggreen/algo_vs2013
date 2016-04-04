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

/*
    1.   p   l       r
 	    1,  0,  1, -1

    2.   p       l   r
 		 1,  0,  1, -1

    3.   p       lr  
		 1,  0,  -1, 1
  
    4.    l      p  l
	     -1  0   1  1

*/
void quick_sort(int l, int r, node* n)
{
	if (l >= r)
		return;

	//static node* n = node_by_big_order;

	int start = l;
	int pivot = l + 1;
	node pivot_node = n[pivot];
	int end = r;

	while (start <= end) {
		while (start <= end) {
			if (is_bigger(n[start], n[pivot])) {
				break;
			}
			else if (is_equal(n[start], n[pivot])) {
				break; 
			}
			else
				start++;
		}

		while (start <= end && end > l) {
			if (is_smaller(n[end], n[pivot])) {
				break;
			}
			else if(is_equal(n[end], n[pivot]))
			{
				end--;
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
	node a[4] = { {1,0,0,0,0},
				  {-1,0,0,0,0},
				  {0,0,0,0,0},
				  {-1,0,0,0,0}};
	quick_sort(0, 3, a);
	return 0;
}
