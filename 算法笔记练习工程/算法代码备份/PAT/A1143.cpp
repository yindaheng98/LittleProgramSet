#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<vector>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;

int M, N;
struct Node
{
	int key;
	Node*l;
	Node*r;
	Node*p;
};
map<int, Node*>node_list;
int keys[10000];
Node*tree;

void insert(Node**top, int* keys, int n)
{
	*top = nullptr;
	if (n <= 0)return;
	Node*top_node = *top = new Node({ keys[0],nullptr,nullptr });
	node_list.insert(pair<int, Node*>(top_node->key, top_node));
	if (n <= 1)return;

	int i = 1;
	while (i < n&&keys[i] <= keys[0])i++;
	insert(&(top_node->l), &keys[1], i - 1);
	insert(&(top_node->r), &keys[i], n - i);
}

void travel(Node*pre,Node*nxt)
{
	if (nxt == nullptr)return;
	nxt->p = pre;
	travel(nxt, nxt->l);
	travel(nxt, nxt->r);
}

int main()
{
	cin >> M >> N;
	for (int n = 0; n < N; n++)
		cin >> keys[n];
	insert(&tree, keys, N);
	travel(nullptr, tree);
	for (int m = 0; m < M; m++)
	{
		int leaf[2];
		bool yes[2] = { true,true };
		vector<int>pres[2];
		for (int i = 0; i < 2; i++)
		{
			cin >> leaf[i];
			auto find = node_list.find(leaf[i]);
			if (find == node_list.end())
			{
				yes[i] = false;
				continue;
			}
			Node*node = find->second;
			pres[i].push_back(node->key);
			while (node->p != nullptr)
			{
				node = node->p;
				pres[i].push_back(node->key);
			}
		}
		if (yes[0] && yes[1])
		{
			int ok = false;
			int n[2] = { pres[0].size() - 1,pres[1].size() - 1 };
			while (n[0] >= 0 && n[1] >= 0)
			{
				if (pres[0][n[0]] != pres[1][n[1]])
				{
					ok = true;
					break;
				}
				n[0]--;
				n[1]--;
			}
			if (ok)
			{
				printf("LCA of %d and %d is %d.\n", leaf[0], leaf[1], pres[0][n[0] + 1]);
				continue;
			}
			else
			{
				printf("%d is an ancestor of %d.\n", n[0] <= 0 ? leaf[0] : leaf[1], n[0] <= 0 ? leaf[1] : leaf[0]);
				continue;
			}
		}
		if (!yes[0] && !yes[1])
		{
			printf("ERROR: %d and %d are not found.\n", leaf[0], leaf[1]);
			continue;
		}
		for (int i = 0; i < 2; i++)
			if (!yes[i])printf("ERROR: %d is not found.\n", leaf[i]);
	}
	return 0;
}

/*正确*/
/*第一次提交把一个printf的格式写错了*/