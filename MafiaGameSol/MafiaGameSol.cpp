#include <cstdio>
using namespace std;

int accused[500005];
int times_accused[500005];
bool visited[500005];

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
