#include <stdio.h>

const int MAX_N = 5001;
char s[MAX_N + 1];
const long long modular = 1000000;

long long d[MAX_N + 1];

inline int get_len(const char* str)
{
	int cnt = 0;
	while (str[cnt++]);
	return cnt - 1;
}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%s\n", s);
	int len = get_len(s);
	d[0] = 1;
	d[1] = 1;
	for (int i = 2; i <= len; i++) {
		if (((s[i - 1] - '0') * 10 + s[i] - '0') > 26)
			d[i] = d[i - 1]%modular;
		else
			d[i] = (d[i - 1]%modular) + (d[i - 2]%modular);

	}
	printf("%lld\n", d[len]);
	return 0;
}