//插入排序
#pragma once
#include"stdafx.h"
#include<vector>
using std::vector;
//普通插入排序已完成
void InsertSort(int s[],int n)
{
	for (int i = 0; i < n; i++)
	{
		int temp = s[i];
		for (int j = i - 1; j >= 0 && temp < s[j]; j--)
		{
			s[j + 1] = s[j];
			s[j] = temp;
		}
	}
}

//折半插入排序
void BinInsertSort(int s[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int temp = s[i];
		int low = 0, high = i - 1;
		while (low<=high)
		{
			int mid = (low + high) / 2;
			if (temp<s[mid])high = mid - 1;
			else low = mid + 1;
		}
		for (int j = i-1; j >= low; j--)s[j + 1] = s[j];			
			s[low] = temp;
	}
}

//希尔排序已完成
void ShellInsert(int s[], int n, int k)
{
	for (int i = 0; i < k; i++)
		for (int j = k + i; j < n; j += k)
		{
			int temp = s[j];
			for (int l = j - k; l >= 0 && temp < s[l]; l -= k)
			{
				s[l + k] = s[l];
				s[l] = temp;
			}
		}

}

vector<int>Init(int datasize)
{
	vector<int>s;
	s.push_back(1);
	s.push_back(2);
	for (int i = 3; i < datasize; i+=2)
	{
		bool pri=1;
		for (int t : s)
			if ((t != 1) && !(i%t))
				pri = 0;
		if (pri)s.push_back(i);
	}
	return s;
}

vector<int>sr = Init(DATA_WIDTH);

void ShellSort(int s[], int n)
{
	int t = 0;
	while (++t<sr.size()&&sr[t] <= n);
	while (--t>=0)
		ShellInsert(s, n, sr[t]);
}
