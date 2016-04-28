#include <stdio.h>


int arr[7] = { -1,1,1,-1,-1,1,1 };
int sort[7] = { 0, };
void merge_sort(int l, int r)
{
	if (l == r)
		return;

	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	printf("%d %d\n", l, r);
	int p = l;
	int q = mid+1;
	int cnt = p;

	while (p <= mid+1 && q <= r && cnt <= r) {
		if (arr[p] <= arr[q])
			sort[cnt++] = arr[p++];
		else
			sort[cnt++] = arr[q++];
	}
	while (cnt <= r) {
		if (p <= mid + 1) 
			sort[cnt++] = arr[p++];
		else 
			sort[cnt++] = arr[q++];
	}

	for (int i = l; i <= r; i++)
		arr[i] = sort[i];

}


void input_proc(void)
{

}

void do_something(void)
{

}

void output_proc(void)
{

}

int main(void)
{
	merge_sort(0, 6);
	
	return 0;
}