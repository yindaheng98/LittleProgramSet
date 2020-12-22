#include "stdafx.h"
#include<iostream>
#include<stdio.h>
using std::cin;
using std::cout;
using std::endl;

int N, M, K;

class Highways
{
private:
	int cities;
	bool highways[1010][1010];
public:
	Highways(int n)
	{
		cities = n;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				highways[i][j] = false;
	}
	Highways(const Highways & h)
	{
		cities = h.cities;
		for (int i = 0; i < cities; i++)
			for (int j = 0; j < cities; j++)
				highways[i][j] = h.highways[i][j];
	}
	void set(int from, int to, bool state)
	{
		highways[from][to] = state;
		highways[to][from] = state;
	}
	bool get(int from, int to)
	{
		return highways[from][to];
	}
	int DFS(int except)
	{
		for (int i = 0; i < cities; i++)
			tvd[i] = false;
		bool finish = false;
		int total = -1;
		while (!finish)
		{
			finish = true;
			for (int i = 0; i < cities; i++)
			{
				if (i != except && !tvd[i])
				{
					finish = false;
					dfs(i, except);
					total++;
					break;
				}
			}
		}
		return total;
	}
private:
	bool tvd[1000];
	void dfs(int n,int except)
	{
		if (tvd[n])return;
		if (n == except)return;
		tvd[n] = true;
		for (int i = 0; i < cities; i++)
			if (highways[n][i])dfs(i, except);
	}
};

int main()
{
	cin >> N >> M >> K;
	Highways highways(N);
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		highways.set(from - 1, to - 1, true);
	}
	for (int i = 0; i < K; i++)
	{
		int k;
		cin >> k;
		cout << highways.DFS(k - 1) << endl;
	}
	return 0;
}

/*ÕýÈ·*/