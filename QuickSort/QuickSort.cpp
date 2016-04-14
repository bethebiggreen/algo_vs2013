#include <stdio.h>

int samples[11] = { 0, };

bool is_bigger(int a, int b, int arr[])
{
	return (arr[a] > arr[b]);
}

bool is_smaller(int a, int b, int arr[])
{
	return (arr[a] < arr[b]);
}

void swap(int i, int j, int arr[])
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void quick_sort(int l, int r, int arr[])
{
	if (l >= r)
		return;

	swap(l, l + 1,arr);
	int start = l + 1;
	int end = r;
	int pivot = l;
	while (start < end) {
		while (start <= end) {
			if (is_bigger(start, pivot,arr))
				break;
			else
				start++;
		}

		while (start <= end) {
			if (is_smaller(end, pivot,arr))
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

int main(void)
{
	int len = -1;
	while (str[++len]);
	for (int i = 0; i < len; i++)
		samples[i] = str[i] - 'a';
	quick_sort(0, len - 1, samples);
	return 0;
}