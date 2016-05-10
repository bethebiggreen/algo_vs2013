/*
2
6 30 3
5 4
8 5
19 -1
22 -3
24 -2
25 6
4 35 2
5 -1
12 3
20 4
30 2
*/
#include <stdio.h>

#define _USE_STL_ 1

#if _USE_STL_
#include<algorithm>
#endif
const int INVALID = 0xFFFFFFFF;

typedef struct ant_t {
	int id;
	int abs;
	int pos;
	ant_t(int in_id = INVALID, int in_abs = INVALID, int in_pos = INVALID) : 
		id(in_id), abs(in_abs), pos(in_pos) {}
	bool operator<(const ant_t& rhs) { return this->abs < rhs.abs; }
	bool operator>(const ant_t& rhs) { return this->abs > rhs.abs; }
} ant;

const int MAX_N = 100000 + 1;
// const int MAX_N = 8 + 1;
bool chosen[MAX_N + 1];
ant pos_q[MAX_N+1];
ant src_q[MAX_N+1];
ant asc_q[MAX_N+1];
int sol[MAX_N+1];

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
	while (s1 <= mid && s2 <= r) {
		if (arr[s1].abs == arr[s2].abs) {
			if(arr[s1].id < arr[s2].id)
				asc_q[cnt++] = arr[s1++];
			else
				asc_q[cnt++] = arr[s2++];
		}
		else if (arr[s1].abs < arr[s2].abs)
			asc_q[cnt++] = arr[s1++];
		else
			asc_q[cnt++] = arr[s2++];
	}

	if (s1 <= mid) {
		while(s1 <= mid)
			asc_q[cnt++] = arr[s1++];
	}
	else
	{
		while(s2 <= r)
			asc_q[cnt++] = arr[s2++];
	}

	cnt = l;
	while (cnt <= r)
		src_q[cnt++] = asc_q[cnt];

	return ;
}

#if _USE_STL_
bool comp(ant a, ant b)
{
	return a.abs < b.abs;
}
#endif

int main(void)
{

	int tc;
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d\n", &tc);
	while (tc--) {
		scanf("%d %d %d\n", &N, &L, &K);
		
		int pos, id;
		for (int i = 0; i < N;i++) {
			scanf("%d %d\n", &pos, &id);
			if (id > 0)
				src_q[i] = { id, L - pos, pos };
			else
				src_q[i] = { id, pos, pos };

			pos_q[i] = { id, 0, pos };
		}

#if !_USE_STL_
		merge_sort(0, N-1, src_q);
#else
		std::sort(src_q, src_q + N, comp);
#endif

		int l = 0, r = N - 1;
		int must_be = 0;
		for (int i = 0; i < N; i++) {
			if (must_be != 0) {
				if (must_be > 0)
					sol[i] = pos_q[r--].id;
				else
					sol[i] = pos_q[l++].id;
				must_be = 0;
				continue;
			}

			if (i + 1 < N) {
				if (asc_q[i].abs == asc_q[i + 1].abs) {
					if (pos_q[l].id < pos_q[r].id) {
						sol[i] = pos_q[l++].id;
						must_be = 1; //r
					}
					else {
						sol[i] = pos_q[r--].id;
						must_be = -1; //l
					}
				}
				else {
					if (asc_q[i].id < 0) {
						sol[i] = pos_q[l++].id;
					}
					else {
						sol[i] = pos_q[r--].id;
					}
				}
			}
			else {
				if (asc_q[i].id < 0) {
					sol[i] = pos_q[l++].id;
				}
				else {
					sol[i] = pos_q[r--].id;
				}
			}
		}
		printf("%d\n", sol[N-1]);
	}

	return 0;
}