#include <stdio.h>

typedef struct tuple_t {
	int pos;
	int nr[2];
} tuple;

const int MAX_N = 15;
tuple suffix_arr[MAX_N];

bool is_bigger(int a, int b, tuple arr[])
{
	if (arr[a].pos == arr[b].pos) {
		if (arr[a].nr[0] == arr[b].nr[0]) 
			return (arr[a].nr[1] > arr[b].nr[1]); 
		else
			return (arr[a].nr[0] > arr[b].nr[0]); 
	} else 
		return arr[a].pos > arr[b].pos;
}

bool is_smaller(int a, int b, tuple arr[])
{
	if (arr[a].pos == arr[b].pos) {
		if (arr[a].nr[0] == arr[b].nr[0]) 
			return (arr[a].nr[1] < arr[b].nr[1]); 
		else
			return (arr[a].nr[0] < arr[b].nr[0]); 
	} else 
		return arr[a].pos < arr[b].pos;
}

void swap(int i, int j, tuple arr[])
{
	tuple tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void quick_sort(int l, int r, tuple arr[])
{
	if (l >= r)
		return;

	swap(l, l+1,arr);
	int start = l + 1;
	int end = r;
	int pivot = l;
	while (start < end) {
		while (start <= end) {
			if (is_smaller(start, pivot, arr))
				break;
			else
				start++;
		}

		while (start <= end) {
			if (is_bigger(end, pivot,arr))
				break;
			else
				end--;
		}

		if (start <= end) 
			swap(start, end,arr);
	}

	swap(end, pivot,arr);
	pivot = end;

	quick_sort(l, pivot - 1,arr);
	quick_sort(pivot + 1, r,arr);
}

const char* str = "mississippi";

void display_suffix_arr(tuple sa[], int len)
{
	for (int i = 0; i < len; i++) 
		printf("%s\n", str + sa[i].pos);
}

int main(void)
{
	int len = -1;
	while (str[++len]);
	// Till one
	for (int i = 0; i < len; i++) {
		suffix_arr[i].pos = i;
		suffix_arr[i].nr[0] = 0;
		suffix_arr[i].nr[1] = str[i] - 'a';
	}

	display_suffix_arr(suffix_arr, len);
	quick_sort(0, len-1, suffix_arr);
	suffix_arr[0].pos = 0;
	flor (int i = 0; i < len; i++) {


	}
	display_suffix_arr(suffix_arr, len);

	return 0;
}