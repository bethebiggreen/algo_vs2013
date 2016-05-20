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
	// i : ��� ����� ��
	for (int i = 0; i<(1 << n); i++) {
		for (int j = 1; j<n; j++) { // j : 1 ���� N �����̴�.. 0 �� �������� �ϰ� ������ ��(���� �湮?)
			if (i&(1 << j)) { // i ��쿡 ���Ͽ�, j �� ���ԵǾ� �־�� ��. ������ j�� �ι�° ���� �˻��ϹǷ�.. ��..
				for (int k = 0; k<n; k++) { // j ������ ����� ���� ��� Ȯ���ϱ� ����.
					if (k != j && (i&(1 << k)) && a[k][j]) { // k == j�� �ڱ������� ��������. i&(1<<k) i �� ���ԵǾ��־�� �ϰ�, k�� j�� ����Ǿ� �־����.
						d[i][j] = min(d[i][j], d[i - (1 << j)][k] + a[k][j]); // ��� min �� ���� �ǹ̴�... |  s  |j| .. j �� �ٲ�� ����?
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