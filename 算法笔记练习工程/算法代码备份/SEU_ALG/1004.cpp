//#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
//#include<Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

int N;
int M;
int S[1000];

void sort(int* S, int n, int layer)
{
	if (n <= 1)return;
	int mid = (n - 1) / 2;
	sort(S, mid + 1, layer + 1);
	sort(&S[mid + 1], n - (mid + 1), layer + 1);
	if (layer <= 2)return;
	vector<int>temp = vector<int>();
	int i = 0, j = mid + 1;
	while (i <= mid || j <= n - 1)
	{
		if (i > mid)temp.push_back(S[j++]);
		else if (j > n - 1)temp.push_back(S[i++]);
		else if (S[i] < S[j])temp.push_back(S[i++]);
		else temp.push_back(S[j++]);
	}
	for (int i = 0; i < n; i++)S[i] = temp[i];
}

void Print3(int S[1000], int N)
{
	sort(&S[0], N, 1);
	for (int i = 0; i < N; i++)cout << S[i] << ' ';
	cout << endl;
}

int main()
{
	cin >> M;
	while (M-- > 0)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> S[i];
		}
		Print3(S, N);
	}
	//system("pause");
	return 0;
}

/*正确*/