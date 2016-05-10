#include <stdio.h>

const int INVALID = 0xFFFFFFFF;

typedef struct ant_t {
	int id;
	int pos;
	int dir;
	int abs;
	ant_t(int in_id = INVALID, int in_pos = INVALID, int in_dir = 0, int in_abs = INVALID) : 
		id(in_id), pos(in_pos), dir(in_dir), abs(in_abs) {}
} ant;

const int MAX_N = 100000 + 1;
ant abc[MAX_N+1];
ant src_q[MAX_N+1];
ant asc_q[MAX_N+1];

int N, L, K;
// Sort for negative
void merge_sort(int l, int r, ant arr[])
{
	if (l >= r)
		return;

	int mid = (l + r) / 2;

	merge_sort(l, mid, arr);
	merge_sort(mid+1,r, arr);

	int s1 = l;
	int s2 = mid+1;
	int cnt = l;
	while (s1 <= mid + 1 && s2 <= r) {
		if (arr[s1].abs < arr[s2].abs)
			asc_q[cnt++] = arr[s1++];
		else
			asc_q[cnt++] = arr[s2++];
	}

	if (s1 <= mid + 1) {
		while(s1 <= mid+1)
			asc_q[cnt++] = arr[s1++];
	}
	else
	{
		while(s2 <= r)
			asc_q[cnt++] = arr[s2++];
	}
	return ;
}

int main(void)
{

	ant tmp[4];
	tmp[0].abs = 1;
	tmp[1].abs = 2;
	tmp[2].abs = -1;
	tmp[3].abs = -1;
	merge_sort(0, 3, tmp);
	
	return 0;
}