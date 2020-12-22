#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::vector;

int M, N;
int preorder[10000];
int inorder[10000];
struct Node
{
	int key;
	Node* l;
	Node* r;
	Node* p;
};

Node* construct(int*in, int* pre, int n)
{
	if (n <= 0)return nullptr;
	if (n <= 1)
	{
		if (in[0] != pre[0])throw "´íÎó";
		else return new Node({ pre[0], nullptr, nullptr, nullptr });
	}
	Node*node = new Node({ pre[0], nullptr, nullptr, nullptr });
	int pc;
	for (int i = 0; i < n; i++)
		if (in[i] == pre[0]) { pc = i; break; }
	node->l = construct(&in[0], &pre[1], pc);
	node->r = construct(&in[pc + 1], &pre[pc + 1], n - pc - 1);
	return node;
}

map<int, Node*>tree_map;
void traversal(Node*node)
{
	tree_map.insert(pair<int, Node*>(node->key, node));
	if (node->l != nullptr)
	{
		node->l->p = node;
		traversal(node->l);
	}
	if (node->r != nullptr)
	{
		node->r->p = node;
		traversal(node->r);
	}
}

int main()
{
	cin >> M >> N;
	for (int i = 0; i < N; i++)
		cin >> inorder[i];
	for (int i = 0; i < N; i++)
		cin >> preorder[i];
	Node*tree = construct(inorder, preorder, N);
	traversal(tree);

	for (int i = 0; i < M; i++)
	{
		int key[2];
		cin >> key[0] >> key[1];
		Node*node[2];
		bool find[2] = { true,true };
		for (int j = 0; j < 2; j++)
		{
			auto map_node = tree_map.find(key[j]);
			if (map_node == tree_map.end())
			{
				find[j] = false;
				continue;
			}
			node[j] = map_node->second;
		}
		if (!find[0] && !find[1])
		{
			printf("ERROR: %d and %d are not found.\n", key[0], key[1]);
			continue;
		}
		if (!find[0] || !find[1])
		{
			printf("ERROR: %d is not found.\n", (!find[0]) ? key[0] : key[1]);
			continue;
		}
		vector<int>ps[2];
		for (int j = 0; j < 2; j++)
		{
			Node*pn = node[j];
			while (pn->p != nullptr)
			{
				ps[j].push_back(pn->key);
				pn = pn->p;
			}
			ps[j].push_back(pn->key);
		}
		int pt[2] = { ps[0].size() - 1,ps[1].size() - 1 };
		while (pt[0] > 0 && pt[1] > 0 && ps[0][pt[0]] == ps[1][pt[1]])
		{
			pt[0]--;
			pt[1]--;
		}
		if (ps[0][pt[0]] != ps[1][pt[1]])
			printf("LCA of %d and %d is %d.\n", key[0], key[1], ps[0][pt[0] + 1]);
		else printf("%d is an ancestor of %d.\n", pt[0] <= 0 ? key[0] : key[1], pt[0] > 0 ? key[0] : key[1]);
	}
	return 0;
}

/*ÕýÈ·*/