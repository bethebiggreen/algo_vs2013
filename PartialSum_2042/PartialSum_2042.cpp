#include <stdio.h>

typedef struct node_t{
	int l;
	int r;
	long long val;
	node_t(int in_l = -1, int in_r = -1, long long in_val=-1) : l(in_l), r(in_r), val(in_val){}
} node;

const int MAX_N = 1000000 + 1;
node tree[MAX_N * 8];
int arr[MAX_N];

int N, M, K;

long long query_tree(int l, int r, int index)
{
	if (l < tree[index].l && tree[index].r > r) // no range at all
		return 0;

	if (l == tree[index].l && tree[index].r == r)
		return tree[index].val;

	int mid = (l + r) / 2;
	long long from_left = query_tree(l, mid, index*2);
	long long from_right = query_tree(mid+1, r, index*2+1);

	return from_left+from_right;
}

long long update_tree(int l, int r, int index, int req)
{
	if (l == r) {
		arr[l] = req;
		tree[index] = { l,r,arr[l] };
		return arr[l];
	}

	int mid = (l + r) / 2;
	long long from_left = update_tree(l, mid, index*2, req);
	long long from_right = update_tree(mid+1, r, index*2+1,req);

	if (from_left > from_right)
		tree[index] = { l,r,from_left };
	else
		tree[index] = { l,r,from_right };

	return tree[index].val;
}

long long build_tree(int l, int r, int index)
{
	if (l == r) {
		tree[index] = { l,r,arr[l] };
		return arr[l];
	}

	int mid = (l + r) / 2;
	long long from_left = build_tree(l, mid, index*2);
	long long from_right = build_tree(mid+1, r, index*2+1);

#if 0 // find max
	if (from_left > from_right)
		tree[index] = { l,r,from_left };
	else
		tree[index] = { l,r,from_right };
#else  // sum
	tree[index] = { l,r,from_left + from_right };
#endif 
	return tree[index].val;
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d %d %d\n", &N, &M, &K);

	for (int i = 0; i < N; i++) 
		scanf("%d\n", arr + i);
	
	printf("%lld\n", build_tree(0, N-1,1));
	return 0;
}