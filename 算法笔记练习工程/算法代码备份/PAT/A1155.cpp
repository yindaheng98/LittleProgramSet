#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

int N;
struct Node
{
	int key;
	Node*l;
	Node*r;
};
queue<Node**>q;
bool isMax = true;
bool isMin = true;

vector<vector<int>> travel(Node*root)
{
	if (root == nullptr)return vector<vector<int>>();
	vector<vector<int>>paths = vector<vector<int>>();
	if (root->l == nullptr&&root->r == nullptr)
	{
		vector<int>path = vector<int>();
		path.push_back(root->key);
		paths.push_back(path);
		return paths;
	}
	vector<vector<int>>pathss[2] = { travel(root->r),travel(root->l) };
	for (int i = 0; i < 2; i++)
	{
		if ((isMax || isMin)&&pathss[i].size() > 0)
		{
			int s = pathss[i][0].size();
			if (s > 0)
			{
				int front = pathss[i][0][s - 1];
				if (isMax)isMax = front < root->key;
				if (isMin)isMin = front > root->key;
			}
		}
		for (vector<int>path : pathss[i])
		{
			path.push_back(root->key);
			paths.push_back(path);
		}
	}
	return paths;
}

int main()
{
	cin >> N;
	Node*root;
	q.push(&root);
	for (int n = 0; n < N; n++)
	{
		int key;
		cin >> key;
		Node*node = new Node({ key,nullptr,nullptr });
		*q.front() = node;
		q.pop();
		q.push(&node->l);
		q.push(&node->r);
	}
	vector<vector<int>>paths = travel(root);
	for (vector<int>path : paths)
		for (int i = path.size() - 1; i >= 0; i--)
			cout << path[i] << (i > 0 ? ' ' : '\n');
	if (isMax)cout << "Max Heap";
	else if (isMin)cout << "Min Heap";
	else cout << "Not Heap";
	return 0;
}

/*ÕýÈ·*/