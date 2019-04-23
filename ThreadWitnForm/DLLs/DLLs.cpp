// DLLs.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))
struct pcb
{ /* ������̿��ƿ� PCB */
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

void sort() /* �����Խ��̽������ȼ����к���*/
{
	PCB *first, *second;
	int insert = 0;
	if ((ready == NULL) || ((p->super) > (ready->super))) /*���ȼ������,�������*/
	{
		p->link = ready;
		ready = p;
	}
	else /* ���̱Ƚ����ȼ�,�����ʵ���λ����*/
	{
		first = ready;
		second = first->link;
		while (second != NULL)
		{
			if ((p->super) > (second->super)) /*��������̱ȵ�ǰ������������,*/
			{ /*���뵽��ǰ����ǰ��*/
				p->link = second;
				first->link = p;
				second = NULL;
				insert = 1;
			}
			else /* ����������������,����뵽��β*/
			{
				first = first->link;
				second = second->link;
			}
		}
		if (insert == 0) { first->link = p; }
	}
}

void input(int num, int initdata[][2]) /* �������̿��ƿ麯��*/
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
		sort(); /* ���� sort ����*/
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

void disp(PCB *pr, int status[][5], int n) /*����������ʾ����,������ʾ��ǰ����*/
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

void check(int status[][5]) /* �������̲鿴���� */
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

void destroy() /*�������̳�������(�������н���,��������)*/
{
	p->state = -1;
	PCB *pf = finish;
	finish = p;
	p->link = pf;//������������
}

void running() /* �������̾�������(��������ʱ�䵽,�þ���״̬*/
{
	if (p == NULL)return;
	(p->rtime)++;
	if (p->rtime == p->ntime)
	{
		destroy(); /* ���� destroy ����*/
	}
	else
	{
		(p->super)--;
		p->state = 0;
		sort(); /*���� sort ����*/
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

void _stdcall INIT(int num, int initdata[][2])//�ó�ʼ��������г�ʼ��
{
	len = h = 0;
	input(num, initdata);
	len = space();
}

void _stdcall RUN(int status[][5])//����һ��ʱ��ƬȻ�󷵻�״̬����
{
	h++;
	run1s(status);
	if (ready != NULL)over = false;
	else over = true;
}

void _stdcall ISFINISH(bool&isf)//�ж��Ƿ����
{
	isf = over;
}


