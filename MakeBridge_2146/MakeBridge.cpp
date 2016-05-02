#include <stdio.h>

int N = 0;

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
void input_proc(void)
{
	scanf("%d\n", &N);
}

int main(void)
{
	int n, m;
	scanf("%d %d\n", &n, &m);
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