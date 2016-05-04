#include <iostream>

using namespace std;
int broken[10]; // true -> broken
int possible(int c) { // 결국 이 함수는 한번도 눌러지지 않은 최소의 값을 찾고, 그 값을 통해서...
	if (c == 0) {
		if (broken[0]) 
			return 0;
		else 
			return 1;
	}

	int len = 0;
	while (c > 0) {
		if (broken[c % 10]) { // 여기서 하나라도 부러진 버튼을 누르면, len 은 말짱꽝
			return 0;
		}
		len += 1;
		c /= 10;
	}
	return len;
}

int main(void)
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		broken[x] = true;
	}
	int ans = n - 100;
	if (ans < 0)
		ans = -ans;

	for (int i = 0; i < 1000000; i++) { // exhaustive search
		int c = i;
		int len = possible(c); // check a length
		if (len > 0) {
			int press = c - n; // check how many times the push is occured
			if (press < 0) 
				press = -press;

			if (ans > len + press)
				ans = len + press;
		}
	}
	printf("%d\n", ans);
	return 0;
}