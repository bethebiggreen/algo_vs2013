#include <cstdio>
#include <cstring>
#include <stack>

#define MAXN 1000000
#define MAXM 62

#define from first
#define at second

using namespace std;

typedef pair<int, int> track;

char line[MAXN + 1];
char bomb[MAXM + 1];
int begin_cut[MAXN], end_cut[MAXN];
int n, m, left;

void bomb1(void)
{
	for (int i = 0; i < n; i++) {
		if (line[i] == bomb[0])
		{
			begin_cut[i]++;
			end_cut[i]++;
		}
	}
}

void bomb2(void)
{
	stack<track> S;
	for (int i = 0; i < n; i++) {

		// 첫글자와 같으면 무조건 가능성이 있다고 보고, Stack 에 push
		if (line[i] == bomb[0]) {
			S.push(track(i, 1));
			continue;
		}

		if (!S.empty()) { // 한번만 돌 예정.
			track tmp = S.top();
			S.pop();
			if (line[i] != bomb[tmp.at]) {
#if 1
				printf("pop\n");
				while (!S.empty())
					S.pop();
#endif
				continue;
			}

			tmp.at++;

			if (tmp.at == m) {
				begin_cut[tmp.from]++;
				end_cut[i]++;
			}
			else {
				S.push(track(tmp.from, tmp.at));
			}
			continue;

		}

	}
}

void remove(void)
{
	int erase = 0; left = 0;
	for (int i = 0; i < n; i++) {
		erase += begin_cut[i];
		if (erase)
			line[i] = '*';
		else
			left++;

		erase -= end_cut[i];
	}
}

void write(void)
{
#if 1
	if (left) {
		for (int i = 0; i < n; i++)
			if (line[i] != '*')
				printf("%c", line[i]);
	}
	else {
		printf("FRULA");
	}
	printf("\n");
#else
	FILE* fp = fopen("output.txt", "w");

	if (left) {
		for (int i = 0; i < n; i++)
			if (line[i] != '*')
				fprintf(fp,"%c", line[i]);
	}
	else {
		fprintf(fp, "FRULA");
	}
	fprintf(fp,"\n");
#endif
}

#if 0
int main(void)
{
	freopen("inp1.txt", "r", stdin);
	//freopen("eksplozija.in.10b", "r", stdin);
	
	scanf("%s%s", line, bomb);

	n = strlen(line), m = strlen(bomb);

	if (m == 1)
		bomb1();
	else
		bomb2();

	remove();
	write();

	return 0;
}
#endif
