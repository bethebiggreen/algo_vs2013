#include <cstdio>
using namespace std;

// const int MAX_N = 500005;
const int MAX_N = 10;

int accused[MAX_N];
int times_accused[MAX_N];
//bool visited[MAX_N];
int visited[MAX_N];

int num_mafia = 0;

void traverse(int x, bool mafija) {
	if (visited[x]) return;
	visited[x] = 1;
	num_mafia += mafija;
	int y = accused[x];
	if (--times_accused[y] == 0 || mafija)
		traverse(y, !mafija);
}

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", accused + i);
		--accused[i];
		++times_accused[accused[i]];
	}

	for (int i = 0; i < n; ++i)
		if (times_accused[i] == 0)
			traverse(i, true);

	for (int i = 0; i < n; ++i)
		traverse(i, false);

	printf("%d\n", num_mafia);
}
