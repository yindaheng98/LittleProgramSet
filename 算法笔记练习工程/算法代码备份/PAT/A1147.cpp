#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;

int M, N;
struct Node
{
	int i;
	Node*l;
	Node*r;
};
queue<Node**>q;

bool judge(Node*top,bool (*J)(int,int))
{
	if (top == nullptr)return true;
	if (top->l != nullptr)
	{
		if (!J(top->i, top->l->i))return false;
		if (!judge(top->l, J))return false;
	}
	if (top->r != nullptr)
	{
		if (!J(top->i, top->r->i))return false;
		if (!judge(top->r, J))return false;
	}
	return true;
}

void travel(Node*top, void(*F)(int))
{
	if (top != nullptr)
	{
		travel(top->l, F);
		travel(top->r, F);
		F(top->i);
	}
}

queue<int>qq;

int main()
{
	cin >> M >> N;
	for (int m = 0; m < M; m++)
	{
		Node*top = nullptr;
		q = queue<Node**>();
		q.push(&top);
		for (int n = 0; n < N; n++)
		{
			int i;
			cin >> i;
			Node* node = new Node({ i,nullptr,nullptr });
			*q.front() = node;
			q.pop();
			q.push(&(node->l));
			q.push(&(node->r));
		}
		if (judge(top, [](int a, int b) {return a > b; }))
			cout << "Max Heap" << endl;
		else if (judge(top, [](int a, int b) {return a < b; }))
			cout << "Min Heap" << endl;
		else
			cout << "Not Heap" << endl;
		qq = queue<int>();
		travel(top, [](int a) {qq.push(a); });
		while (qq.size() > 1)
		{
			cout << qq.front() << ' ';
			qq.pop();
		}
		cout << qq.front() << endl;
	}
	return 0;
}

/*ÕýÈ·*/