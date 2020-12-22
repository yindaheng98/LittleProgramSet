#include "stdafx.h"
#include<iostream>
#include<vector>
#include<queue>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;

short M, N;

struct Node
{
	queue<Node*>children;
	short K = 0;
};

Node TREE[10][10];//初始值-1表示不存在此节点
queue<Node*>travel_this, travel_next;
vector<short>count;

void travel()
{
	Node*node = travel_this.front();
	travel_this.pop();
	if (node->K <= 0)count[count.size() - 1]++;//当前层叶节点数加一
	else
	{
		while (!node->children.empty())
		{
			travel_next.push(node->children.front());
			node->children.pop();
		}
	}
	if (travel_this.size() <= 0)
	{
		if (travel_next.size() <= 0)return;
		count.push_back(0);
		queue<Node*>t = travel_this;
		travel_this = travel_next;
		travel_next = t;
	}
	travel();
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		char nodestr[2];
		short K;
		cin >> nodestr >> K;
		Node* node = &TREE[nodestr[0] - '0'][nodestr[1] - '0'];
		node->K = K;
		for (int j = 0; j < K; j++)
		{
			cin >> nodestr;
			node->children.push(&TREE[nodestr[0] - '0'][nodestr[1] - '0']);
		}
	}
	count.push_back(0);
	travel_this.push(&TREE[0][1]);
	travel();
	for (int i = 0; i < count.size() - 1; i++)
		cout << count[i] << ' ';
	cout << count[count.size() - 1];
	return 0;
}

