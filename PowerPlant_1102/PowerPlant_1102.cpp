#include <stdio.h>

// const int MAX_N = 16;
const int MAX_N = 4;
int N;
int start;
int goal_cnt;
int a[MAX_N + 1][MAX_N + 1];
long long d[1 << MAX_N] ;
char yesno[MAX_N+1];

inline long long min_a(long long a, long long b) { return (a > b) ? b : a; }
inline long long max_a(long long a, long long b) { return (a > b) ? a : b; }
const int MAX_INT = 0x7FFFFFFF;

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif


	scanf("%d\n", &N);
	int case_num = (1 << N) - 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%d ", &a[i][j]);
		scanf("\n");
	}

	scanf("%s\n", &yesno);
	scanf("%d\n", &goal_cnt);

	int len = 0;
	while (yesno[len++]);
	len--;

	for (int i = 0; i < len; i++) {
		if (yesno[i] == 'Y')
			start |= (1 << i);
	}

	for (int i = 0; i <= case_num; i++)
		d[i] = MAX_INT;

	d[start] = 0;
	for (int s = start+1; s <= case_num; s++) {
		// d[s] = min(d[s 전에 하나 뺀거] + a[s가되기 위해][넣어야 되는것]); 
		int min = MAX_INT;
		for (int i = 0; i < N; i++) {
			if (s & (1 << i)) {
				int s2 = s & ~(1 << i);
				for (int j = 0; j < N; j++) {
					if ((s2 & (1 << j)) && a[j][i]) 
						min = min_a(min, d[s2]+a[j][i]);
				}
			}
		}
		d[s] = min;
	}

	return 0;
}