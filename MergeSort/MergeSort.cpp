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




#if 0 // Æ²¸°°Í
void merge_sort(int l, int r)
{
	if (l >= r)
		return;

	int mid = (l + r) / 2;
	merge_sort(l, mid);
	merge_sort(mid + 1, r);

	int s1 = l;
	int s2 = mid + 1;

	int cnt = l;
	while (s1 <= mid && s2 <= r) {
		if (length[s1] < length[s2])
			sorted_length[cnt++] = length[s1++];
		else
			sorted_length[cnt++] = length[s2++];
	}

	int left = 0;
	if (cnt <= r)
		left = (s1 <= mid + 1) ? s1 : s2;

	while (cnt <= r)
		sorted_length[cnt++] = length[left++];

	for (int i = l; i <= r; i++)
		length[i] = sorted_length[i];
}
#endif