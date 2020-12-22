#include "stdafx.h"
#include<iostream>
#include<string.h>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::sort;

double A[1001];
unsigned Ns[40];

bool cmp(unsigned a, unsigned b)
{
	return a > b;
}

int main()
{
	for (short i = 0; i < 2; i++)
	{
		int K;
		scanf("%d", &K);
		for (int k = 0; k < K; k++)
		{
			int N;
			double a;
			scanf("%d %lf", &N, &a);
			A[N] += a;
			Ns[i * 10 + k] = N;
		}
	}
	sort(&Ns[0], &Ns[20], cmp);
	unsigned N_last = Ns[0], total = 1;
	for (unsigned i = 1; i < 20; i++)
	{
		if (Ns[i] == 0) { Ns[total] = 0; break; }
		if (Ns[i] < N_last)Ns[total++] = Ns[i];
		N_last = Ns[i];
	}
	if (A[0] >= 0.1 || A[0] <= -0.1)total++;
	printf("%d", total);
	for (unsigned i = 0; i < total; i++)
		printf(" %d %.1f", Ns[i], A[Ns[i]]);
	return 0;
}

/*��һ���ύ��������ϵ����*/
/*�ڶ����ύ����̫�����Լ���Ū�����*/
/*����ȷ����Ϊ����̫���ӣ�С����Ĳ�����*/
/*ԭ������д������򵥵ĳ����*/
/*����Ϊ�䣬����ʱ��ע����ṹ�ļ򵥶�����Ч��*/
