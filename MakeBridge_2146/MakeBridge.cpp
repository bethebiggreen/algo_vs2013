// The project goes wrong on different project.
// This code was from 'https://gist.github.com/Baekjoon/2c32984ad5c42b333c38' which resolves
// 'Broken remote controller'
// It solves with exhaustive search.

#include <stdio.h>

bool broken[10];
int possible(int c)
{
	if (c == 0) {
		if (broken[0]){
			return 0;
		}
		else {
			return 1;
		}
	}
	int len = 0;
	while (c > 0) {
		if (broken[c % 10]) {
			return 0;
		}
		len += 1;
		c /= 10;
	}
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d\n", &n);
	scanf("%d\n", &m);
	for (int i = 0; i < m; i++) {
		int x;
		scanf("%d ", &x);
		broken[x] = true;
	}
	int ans = n - 100;
	if (ans < 0) {
		ans = -ans; // absolute value
	}

	for (int i = 0; i < 1000000; i++) {
		int c = i;
		int len = possible(c);
		if (len > 0) {
			int press = c - n;
			if (press < 0) {
				press = -press;
			}
			if (ans > len + press) {
				ans = len + press;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}