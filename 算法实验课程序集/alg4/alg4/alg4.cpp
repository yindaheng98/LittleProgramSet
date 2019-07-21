// alg4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>

int s[100][100];

int mid(int a, int b,int c)
{
	if (a > b)return a;
	else if (b > c)return c;
	else return b;
}

void put(int x, int y,int m,int n,int*c)
{
	if (s[mid(1, x, m)][mid(1, y, n)] == 1)return;
	s[mid(1, x, m)][mid(1, y, n)]=1;
	(*c)++;
	if (mid(1, x, m) == x && mid(1, y, n) == y)
	{
		put(x + 2, y + 1, m, n,c);
		put(x + 1, y - 2, m, n,c);
		put(x - 2, y - 1, m, n,c);
		put(x - 1, y + 2, m, n,c);
	}
}

int main()
{
	int m = 11;
	int n = 12;
	int c = 0;

	put(1, 1, m, n,&c);
	/*
int c = 0;
	int x = 0;
	int y = -1;
	while (x <= m + 1 && y <= n + 1)
	{
		int i = 0;
		while (x + i <= m + 1)
		{
			c++;
			s[mid(1, x + i, m)][mid(1, y, n)]=1;
			printf("(%d,%d)\n", mid(1, x + i, m), mid(1, y, n));
			i += 5;
		}
		int j = 0;
		while (y + j <= n + 1)
		{
			c++;
			s[mid(1, x, m)][mid(1, y + j, n)]=1;
			printf("(%d,%d)\n", mid(1, x, m), mid(1, y + j, n));
			j += 5;
		}
		x += 1;
		y += 2;
	}
	*/
	
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			printf("%d ", s[i][j]);
		printf("\n");
	}
	printf("(%d)", c);
	system("pause");
    return 0;
}

