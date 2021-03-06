#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<map>
#include <string>
#include<Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;
using std::map;
using std::pair;
using std::string;

vector<int> Dijkstra(int i, vector<vector<int>>E)
{
	if (i == E.size() - 1)
	{
		vector<int>r(1);
		r[0] = i;
		return r;
	}
	for (int j = 0; j < E.size(); j++)
	{
		if (!ok[j] && E[i][j] > 0)
		{
			ok[j] = true;
			vector<int> r = DFS(j, E, ok);
			if (r.size() > 0)
			{
				vector<int> rr(r.size() + 1);
				rr[0] = i;
				for (int i = 0; i < r.size(); i++)
					rr[i + 1] = r[i];
				return rr;
			}
		}
	}
	return vector<int>(0);
}

vector<int>getPath(vector<vector<int>>E)
{
	return Dijkstra(0, E);
}

int MCMF(vector<vector<int>>E, vector<vector<int>>C)
{
	for (int i = 0; i < E.size(); i++)
	{
		E[E.size() - 1][i] = 0;
		E[i][0] = 0;
	}
	vector<int>p = getPath(E);
	while (p.size() > 0)
	{
		int maxflow = -1;
		for (int i = 0; i < p.size() - 1; i++)
			if (maxflow == -1 || maxflow > E[p[i]][p[i + 1]])
				maxflow = E[p[i]][p[i + 1]];
		for (int i = 0; i < p.size() - 1; i++)
		{
			E[p[i]][p[i + 1]] -= maxflow;
			E[p[i + 1]][p[i]] += maxflow;
		}
		p = getPath(E);
	}
	int sum = 0,cost = 0;
	for (int i = 0; i < E.size(); i++)
	{
		sum += E[E.size() - 1][i];
		cos += 
	}
	return sum,cos;
}

int translate(int k, int s, int t, int N)
{
	if (k == s)return 0;
	if (k == t)return N + 1;
	return k;
}

int main()
{
	int N, M, s, t;
	cin >> N >> M >> s >> t;
	vector<vector<int>>E(N + 2), C(N + 2);
	for (int i = 0; i < N + 2; i++)
	{
		E[i] = vector<int>(N + 2);
		C[i] = vector<int>(N + 2);
	}
	for (int i = 0; i < M; i++)
	{
		int f, d, cap, cost;
		cin >> f >> d >> cap >> cost;
		f = translate(f, s, t, N);
		d = translate(d, s, t, N);
		E[f][d] = cap;
		C[f][d] = cost;
	}
	cout << MCMF(E, C) << endl;
	system("pause");
	return 0;
}

/*WrongAnswer*/