// alg4-1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
const int M = 32, go[5][2] = { { 0,0 },{ 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };

int n, m;
int anx[M][M], ans;
int put[M][M], spy[M][M], tmp, spys = 0;
int lim1, lim2;

void search(int i, int j);
void puta(int x, int y, int i, int j)
{
	put[x][y] = 1;
	tmp++;
	for (int i = 0; i < 5; ++i)
		if (++spy[x + go[i][0]][y + go[i][1]] == 1) spys++;

	search(i, j + 1);

	put[x][y] = 0;
	tmp--;
	for (int i = 0; i < 5; ++i)
		if (--spy[x + go[i][0]][y + go[i][1]] == 0) spys--;
}

void search(int i, int j)
{
	if (tmp >= ans) return;
	while (i <= n && spy[i][j]) //已放置的不再被搜索
	{
		++j;
		if (j > m)	++i, j = 1;
	}
	if (i>n)					//更新答案
	{
		ans = tmp;
		memcpy(anx, put, sizeof(put));
		return;
	}

	int reach = spys + (ans - tmp) * 5;
	if (reach <= lim1) return;
	if (i<n - 1 && reach <= lim2) return;

	if ((i == n&&j == m) || spy[i][j + 1] == 0) puta(i, j, i, j);
	if (i<n) puta(i + 1, j, i, j);
	if (j<m && (spy[i][j + 1] == 0 || spy[i][j + 2] == 0)) puta(i, j + 1, i, j);
}

int main(void)
{
	scanf_s("%d%d", &n, &m);

	ans = n * m / 3 + 2;
	lim1 = n * m, lim2 = n * m + m / 4 + 5;

	for (int i = 0; i <= n + 1; ++i)
		spy[i][0] = spy[i][m + 1] = 1;
	for (int i = 0; i <= m + 1; ++i)
		spy[0][i] = spy[n + 1][i] = 1;
	search(1, 1);

	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			printf("%d%c", anx[i][j], j == m ? '\n' : ' ');
	system("pause");
	return 0;
}