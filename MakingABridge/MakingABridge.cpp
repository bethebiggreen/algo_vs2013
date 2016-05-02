#include <stdio.h>

typedef struct node_t {
	int x, y, val;
} node;

const int MAX_N = 101;
int map[MAX_N + 1][MAX_N + 1];
int dist_map[MAX_N + 1][MAX_N + 1];
int visited_map[MAX_N + 1][MAX_N + 1];
// QUEUE
int cnt = 0;
int N = 0;

template<typename T>
class Q {
public :
	static const int MAX_DEFAULT_Q_SIZE = 1024 * 1024 * 10;
	Q(int size = MAX_DEFAULT_Q_SIZE) : requested_size(size), head(0), tail(-1), q(NULL) 
	{
		q = new T[requested_size];
	}

	~Q() 
	{
		if (q) {
			delete[] q;
			q = NULL;
		}
	}

	int add(const T n)
	{
		q[++tail] = n;
		return tail;
	}

	bool pop_front(T& n)
	{
		if (head > tail)
			return false;

		n = q[head++];
		return true;
	}

	void clear(void)
	{
		for (int i = 0; i < tail; i++)
			q[i] = { 0,0,0 };
		head = 0, tail = -1;
	}

	bool empty(void)
	{
		return (head > tail);
	}

private:
	T* q;
	int requested_size;
	int head;
	int tail;

};

Q<node> group_q;

void input_proc(void)
{
	scanf("%d\n", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d ", &map[i][j]);
		}
	}

}

//UP RIGHT DOWN LEFT
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void bfs(int i, int j, int group)
{
	visited_map[i][j] = true;
	int x = j, y = i;
	group_q.add({ x,y,group });
	node cur;
	while (group_q.pop_front(cur)) {
		map[cur.y][cur.x] = group;
		for (int dir = 0; dir < 4; dir++) {
			x = cur.x + dx[dir];
			y = cur.y + dy[dir];
			if (x < 0 || y < 0 || x >= N || y >= N)
				continue;

			if (!visited_map[y][x] && map[y][x] == 1) {
				visited_map[y][x] = true;
				group_q.add({ x, y, group });
			}
		}
	}
}

int make_region()
{
	int group = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 1 && !visited_map[i][j]) {
				bfs(i, j, group++);
			}
		}
	}
	return group;
}

int do_something()
{
	int num_group = make_region();
	group_q.clear();

	int x, y;
	bool no_add = false;
	int dist = 0;
	while (!no_add) {
		dist++;
		no_add = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 0) {
					for (int dir = 0; dir < 4; dir++) {
						x = j + dx[dir];
						y = i + dy[dir];

						if (x < 0 || y < 0 || x >= N || y >= N)
							continue;

						if (map[y][x]) {
							group_q.add({ j, i, map[y][x] });
							no_add = false;
							break;
						}
					}
				}
			}
		}
		node cur;
		while (group_q.pop_front(cur)) {
			map[cur.y][cur.x] = cur.val;
			dist_map[cur.y][cur.x] = dist;
		}
	}

	int min = 0x7FFFFFFF;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int dir = 1; dir <= 2; dir++) {
				y = i + dy[dir];
				x = j + dx[dir];
				if (x < 0 || y < 0 || x >= N || y >= N)
					continue;
				if (map[y][x] != map[i][j]) {
					if (min > dist_map[y][x] + dist_map[i][j])
						min = dist_map[y][x] + dist_map[i][j];
				}
			}
		}
	}
	return min;
}

void output_proc()
{

}

int main(void)
{
#if _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	input_proc();
	printf("%d\n", do_something());
	return 0;
}