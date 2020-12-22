#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int N, M, K;
struct Node
{
	vector<int>pre;
	vector<int>nxt;
};
Node graph[1011];
bool traveled[1011];
vector<int>r;

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int from, to;
		cin >> from >> to;
		graph[from].nxt.push_back(to);
		graph[to].pre.push_back(from);
	}
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		memset(&traveled[1], 0, N * sizeof(bool));
		bool over = false;
		for (int j = 0; j < N; j++)
		{
			int ni;
			cin >> ni;
			if (over)continue;
			Node node = graph[ni];
			for (int pre_ni : node.pre)
				if (!traveled[pre_ni])
				{
					r.push_back(i);
					over = true;
					break;
				}
			traveled[ni] = true;
		}
		if (!over)
			for (int j = 1; j <= N; j++)
				if (!traveled[j])
				{
					r.push_back(i);
					break;
				}
	}
	for (int i = 0; i < r.size() - 1; i++)
		cout << r[i] << ' ';
	cout << r[r.size() - 1];
	return 0;
}

/*正确*/
/*即使不是拓扑序列，仍要把数据读完*/