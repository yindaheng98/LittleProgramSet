#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;

int Q;

class Queue
{
public:
	int N, M, K;
	int customers[1010];
	int finish_time[1010];
	void getover()
	{
		while (!ticks());
	}
private:
	int time = 0;
	queue<int>q[22];
	int cpt = 0;
	bool intoline()
	{
		int min = 100, mini = 0;
		for (int i = 0; i < N; i++)
		{
			int qn = q[i].size();
			if (qn < min)
			{
				min = qn;
				mini = i;
			}
		}//找最短的队伍
		if (min < M&&cpt<K)
		{
			q[mini].push(cpt++);
			return true;
		}//放用户
		else return false;
	}
	bool ticks()
	{
		time++;
		while (intoline());//先填满队列
		for (int i = 0; i < N; i++)
			if (!q[i].empty())
			{
				int c = q[i].front();
				if (--customers[c] <= 0)
				{
					q[i].pop();
					finish_time[c] = time;
				}
			}
		if (time >= 540)
		{
			for(int i=0;i<N;i++)
				while (!q[i].empty())
				{
					finish_time[q[i].front()] = 600;
					q[i].pop();
				}
			for (; cpt < K; cpt++)
				finish_time[cpt] = 600;
			return true;
		}
		return false;
	}
};

Queue q = Queue();

int main()
{
	cin >> q.N >> q.M >> q.K >> Q;
	for (int i = 0; i < q.K; i++)
		cin >> q.customers[i];
	q.getover();
	for (int i = 0; i < Q; i++)
	{
		int who;
		cin >> who;
		int fin = q.finish_time[who - 1];
		if (fin > 540)cout << "Sorry" << endl;
		else printf("%02d:%02d\n", 8 + fin / 60, fin % 60);
	}
	return 0;
}

/*部分正确*/