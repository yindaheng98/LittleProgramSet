#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::pair;

int N, K;

struct Node
{
	int address;
	int data;
	Node* next;
};

map<int, Node*>nodes;

int main()
{
	Node* root = new Node({ -1,0,nullptr });
	cin >> root->address >> N >> K;
	nodes.insert(pair<int, Node*>(root->address, root));
	for (int n = 0; n < N; n++)
	{
		int address;
		cin >> address;
		Node*node;
		auto find = nodes.find(address);
		if (find == nodes.end())
		{
			node = new Node({ address,0,nullptr });
			nodes.insert(pair<int, Node*>(address, node));
		}
		else node = find->second;
		cin >> node->data;
		Node*next;
		cin >> address;
		if (address < 0)
		{
			node->next = nullptr;
			continue;
		}
		find = nodes.find(address);
		if (find == nodes.end())
		{
			next = new Node({ address,0,nullptr });
			nodes.insert(pair<int, Node*>(address, next));
		}
		else next = find->second;
		node->next = next;
	}
	Node*beg[3] = { nullptr,nullptr,nullptr };
	Node*end[3] = { nullptr,nullptr,nullptr };
	while (root != nullptr)
	{
		int i = root->data < 0 ? 0 : (root->data > K ? 2 : 1);
		if (beg[i] == nullptr)
		{
			beg[i] = root;
			end[i] = root;
		}
		else
		{
			end[i]->next = root;
			end[i] = root;
		}
		Node*next = root->next;
		root->next = nullptr;
		root = next;
	}
	root = beg[0] != nullptr ? beg[0] : (beg[1] != nullptr ? beg[1] : beg[2]);
	if (end[0] != nullptr)end[0]->next = beg[1] != nullptr ? beg[1] : beg[2];
	if (end[1] != nullptr)end[1]->next = beg[2];
	while (root != nullptr)
	{
		printf("%05d %d ", root->address, root->data, root->next != nullptr ? root->next->address : -1);
		if (root->next != nullptr)
			printf("%05d\n", root->next->address);
		else
			printf("%d\n", -1);
		root = root->next;
	}
	return 0;
}

/*ÕıÈ·*/