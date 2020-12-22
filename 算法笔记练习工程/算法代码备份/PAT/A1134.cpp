#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include<memory.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int N, M, K;
vector<int>edges[10000];

int main()
{
	cin >> N >> M;
	for (int m = 0; m < M; m++)
	{
		int from, to;
		cin >> from >> to;
		edges[from].push_back(m);
		edges[to].push_back(m);
	}
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		bool included[10000];
		memset(&included[0], 0, M * sizeof(bool));
		int Nv;
		cin >> Nv;
		for (int n = 0; n < Nv; n++)
		{
			int v;
			cin >> v;
			for (int e : edges[v])
				included[e] = true;
		}
		bool no = false;
		for (int m = 0; m < M; m++)
			if (!included[m])
			{
				cout << "No" << endl;
				no = true;
				break;
			}
		if (!no)
			cout << "Yes" << endl;
	}
	return 0;
}

/*ÕýÈ·*/