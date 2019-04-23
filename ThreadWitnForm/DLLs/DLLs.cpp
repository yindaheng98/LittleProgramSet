// DLLs.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))
struct pcb
{ /* 定义进程控制块 PCB */
	int name;
	int state;
	int super;
	int ntime;
	int rtime;
	struct pcb *link;
} *ready = NULL, *p, *finish = NULL;
typedef struct pcb PCB;
int len, h;
bool over;

void sort() /* 建立对进程进行优先级排列函数*/
{
	PCB *first, *second;
	int insert = 0;
	if ((ready == NULL) || ((p->super) > (ready->super))) /*优先级最大者,插入队首*/
	{
		p->link = ready;
		ready = p;
	}
	else /* 进程比较优先级,插入适当的位置中*/
	{
		first = ready;
		second = first->link;
		while (second != NULL)
		{
			if ((p->super) > (second->super)) /*若插入进程比当前进程优先数大,*/
			{ /*插入到当前进程前面*/
				p->link = second;
				first->link = p;
				second = NULL;
				insert = 1;
			}
			else /* 插入进程优先数最低,则插入到队尾*/
			{
				first = first->link;
				second = second->link;
			}
		}
		if (insert == 0) { first->link = p; }
	}
}

void input(int num, int initdata[][2]) /* 建立进程控制块函数*/
{
	int i;
	for (i = 0; i < num; i++)
	{
		p = getpch(PCB);
		p->name = i;
		p->super = initdata[i][0];
		p->ntime = initdata[i][1];
		p->rtime = 0;
		p->state = 0;
		p->link = NULL;
		sort(); /* 调用 sort 函数*/
	}
}

int space()
{
	int l = 0;
	PCB *pr = ready;
	while (pr != NULL)
	{
		l++;
		pr = pr->link;
	}
	return (l);
}

void disp(PCB *pr, int status[][5], int n) /*建立进程显示函数,用于显示当前进程*/
{
	/*printf("\n qname \t state \t super \t ndtime \t runtime \n");
	printf("|%d\t", pr->name);
	printf("|%d\t", pr->state);
	printf("|%d\t", pr->super);
	printf("|%d\t", pr->ntime);
	printf("|%d\t", pr->rtime);
	printf("\n");*/
	status[n][0] = pr->state;
	status[n][1] = pr->name;
	status[n][2] = pr->super;
	status[n][3] = pr->ntime;
	status[n][4] = pr->rtime;
}

void check(int status[][5]) /* 建立进程查看函数 */
{
	int n = 0;
	PCB *pr;
	if (p != NULL)
	{
		disp(p, status, n++);
	}

	pr = ready;
	while (pr != NULL)
	{
		disp(pr, status, n++);
		pr = pr->link;
	}
	PCB*pf;
	pf = finish;
	while (pf != NULL)
	{
		disp(pf, status, n++);
		pf = pf->link;
	}
}

void destroy() /*建立进程撤消函数(进程运行结束,撤消进程)*/
{
	p->state = -1;
	PCB *pf = finish;
	finish = p;
	p->link = pf;//并入辣鸡链表
}

void running() /* 建立进程就绪函数(进程运行时间到,置就绪状态*/
{
	if (p == NULL)return;
	(p->rtime)++;
	if (p->rtime == p->ntime)
	{
		destroy(); /* 调用 destroy 函数*/
	}
	else
	{
		(p->super)--;
		p->state = 0;
		sort(); /*调用 sort 函数*/
	}
}

void run1s(int status[][5])
{
	p = ready;

	if (p != NULL)
	{
		ready = p->link;
		p->link = NULL;
		p->state = 1;
	}

	check(status);
	running();
}

void _stdcall INIT(int num, int initdata[][2])//用初始化矩阵进行初始化
{
	len = h = 0;
	input(num, initdata);
	len = space();
}

void _stdcall RUN(int status[][5])//运行一个时间片然后返回状态矩阵
{
	h++;
	run1s(status);
	if (ready != NULL)over = false;
	else over = true;
}

void _stdcall ISFINISH(bool&isf)//判断是否完成
{
	isf = over;
}


