#include "stdafx.h"
#include<iostream>
#include<stdio.h>
using std::cin;
using std::cout;
using std::endl;

int K;
struct Node
{
	int key;
	bool isred;
	Node*l = nullptr;
	Node*r = nullptr;
	Node(char*node_str)
	{
		isred = node_str[0] == '-';
		key = 0;
		for (int i = isred ? 1 : 0; node_str[i] != '\0'; i++)
			key = key * 10 + node_str[i] - '0';
	}
};

void construct(Node**nodes,int n)
{
	if (n <= 1)return;
	int t = 1;
	while (t < n)
	{
		if (nodes[0]->key < nodes[t]->key)
			break;
		t++;
	}
	nodes[0]->l = (t <= 1 ? nullptr : nodes[1]);
	nodes[0]->r = (t >= n ? nullptr : nodes[t]);
	construct(&nodes[1], t - 1);
	construct(&nodes[t], n - t);
}

int countBlack(Node*top)
{
	if (top == nullptr)return 0;
	int lb = countBlack(top->l);
	int rb = countBlack(top->r);
	if (lb < 0 || rb < 0 || lb != rb)
		return -1;
	return lb + (top->isred ? 0 : 1);
}

bool isRedBlack(Node*top)
{
	if (top == nullptr)return true;
	if (top->isred)
	{
		if (top->l != nullptr&&top->l->isred)
			return false;
		if (top->r != nullptr&&top->r->isred)
			return false;
	}
	return isRedBlack(top->l) && isRedBlack(top->r);
}

int main()
{
	cin >> K;
	for (int k = 0; k < K; k++)
	{
		Node*nodes[30];
		int N;
		cin >> N;
		for (int n = 0; n < N; n++)
		{
			char node_str[100];
			cin >> node_str;
			nodes[n] = new Node(node_str);
		}
		construct(nodes, N);
		Node*top = nodes[0];
		if ((!top->isred) && isRedBlack(top) && (countBlack(top) >= 0))
			cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}

/*ÕýÈ·*/