#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include<set>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::set;

int N, M, K;
int E[10000][2];
int V[10000];

int main()
{
	cin >> N >> M;
	for (int m = 0; m < M; m++)
		cin >> E[m][0] >> E[m][1];
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		set<int>colors;
		for (int n = 0; n < N; n++)
		{
			cin >> V[n];
			colors.insert(V[n]);
		}
		bool yes = true;
		for (int m = 0; m < M; m++)
			if (V[E[m][0]] == V[E[m][1]])
			{
				yes = false;
				break;
			}
		if (yes)cout << colors.size() << "-coloring" << endl;
		else cout << "No" << endl;
	}
	return 0;
}

/*ÕýÈ·*/