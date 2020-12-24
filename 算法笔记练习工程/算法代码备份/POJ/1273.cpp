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

vector<int> DFS(int i, vector<vector<int>>E, vector<bool>ok)
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
	vector<bool>ok(E.size());
	ok[0] = true;
	return DFS(0, E, ok);
}

int MaxFlow(vector<vector<int>>E)
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
	int sum = 0;
	for (int i = 0; i < E.size(); i++)
		sum += E[E.size() - 1][i];
	return sum;
}

int main()
{
	int N, M;
	cin >> N >> M;
	vector<vector<int>>E(M);
	for (int i = 0; i < M; i++)
		E[i] = vector<int>(M);
	for (int i = 0; i < N; i++)
	{
		int s, e, c;
		cin >> s >> e >> c;
		E[s - 1][e - 1] = c;
	}
	cout << MaxFlow(E) << endl;
	system("pause");
	return 0;
}

/*WrongAnswer*/