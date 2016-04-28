const int MAX_N = 6;

int arr[MAX_N] = { -1,3,1,-1,3,-1 };
// int arr[MAX_N] = { 3,1,-1,3,-1 };
// int arr[MAX_N] = { 1,3,2,4,5 };
int sorted[MAX_N] ;

#include <stdio.h>

void merge_sort(int l, int r)
{
	if (l >= r) 
		return;

	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);
	//need to merge
	// start - mid, end(mid-1) - r
	int start = l;
	int end = mid + 1;;
	int cnt = l;
	int left = 0;
	while (cnt <= r) {
		if (start > mid || end > r) {
			left = (start > mid) ? end : start;
			break;
		}

		if (arr[start] < arr[end]) 
			sorted[cnt++] = arr[start++];
		else 
			sorted[cnt++] = arr[end++];
	}
	// do not need check
	while (cnt <= r) 
		sorted[cnt++] = arr[left++];
	for (int i = l; i <= r; i++)
		arr[i] = sorted[i];

}

int main(void)
{
	merge_sort(0, MAX_N - 1);
	return 0;
}