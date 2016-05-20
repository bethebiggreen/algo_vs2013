#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX_N = 4; //20
int d[1 << MAX_N][MAX_N];
int a[MAX_N][MAX_N];
int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int i = 0; i<(1 << n); i++) {
		for (int j = 0; j<n; j++) {
			d[i][j] = 100000000;
		}
	}

	d[1][0] = 0;
	// i : 모든 경우의 수
	for (int i = 0; i<(1 << n); i++) {
		for (int j = 1; j<n; j++) { // j : 1 부터 N 까지이니.. 0 을 고정으로 하고 마지막 수(최종 방문?)
			if (i&(1 << j)) { // i 경우에 대하여, j 가 포함되어 있어야 함. 하지만 j는 두번째 부터 검사하므로.. 흠..
				for (int k = 0; k<n; k++) { // j 이전의 경우의 수를 모두 확인하기 위함.
					if (k != j && (i&(1 << k)) && a[k][j]) { // k == j은 자기참조를 막기위함. i&(1<<k) i 에 포함되어있어야 하고, k와 j가 연결되어 있어야함.
						d[i][j] = min(d[i][j], d[i - (1 << j)][k] + a[k][j]); // 계속 min 을 보는 의미는... |  s  |j| .. j 가 바뀌기 때문?
					}
				}
			}
		}
	}
	int ans = 1000000000;
	for (int i = 1; i<n; i++) {
		if (a[i][0]) {
			ans = min(ans, d[(1 << n) - 1][i] + a[i][0]);
		}
	}
	printf("%d\n", ans);
	return 0;
}