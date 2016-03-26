#include <stdio.h>
#define MaxN 500
#define NSQR 250000
static int n, m, Map[MaxN + 2][MaxN + 2], h, Max, qx[NSQR + 1], qy[NSQR + 1];
static int dx[5] = { 0, 0, 1, 0, -1 }, dy[5] = { 0, 1, 0, -1, 0 };
static bool Check[MaxN + 2][MaxN + 2];
void Input(void)
{
	int i, j;
	FILE *In = fopen("input.txt", "r");
	fscanf(In, "%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			fscanf(In, "%d", &Map[i][j]);
			if (Map[i][j] > h)
				h = Map[i][j];
		}
	}
	fclose(In);
}
void BFS(int Limit, int y, int x)
{
	int i, Head, Tail;
	Head = 0, Tail = 1;
	qy[1] = y; qx[1] = x;
	while (Head != Tail)
	{
		Head++;
		for (i = 1; i <= 4; i++)
		{
			y = qy[Head] + dy[i];
			x = qx[Head] + dx[i];
			if (!Check[y][x])
			{
				if (Map[y][x] >= Limit)
				{
					qy[++Tail] = y;
					qx[Tail] = x;
					Check[y][x] = true;
				}
			}
		}
	}
}

void Process(void)
{
	int i, j, Loop, t;
	for (Loop = 1; Loop <= h; Loop++)
	{
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				Check[i][j] = false;
		for (t = 0, i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (!Check[i][j] && Map[i][j] >= Loop)
					BFS(Loop, i, j), t++;
		if (t > Max)
			Max = t;
	}
}

void Output(void)
{
	FILE *Out = fopen("output.txt", "w");
	fprintf(Out, "%d", Max);
	fclose(Out);
}

int main(void)
{
	Input();
	Process();
	Output();
	return 0;
}