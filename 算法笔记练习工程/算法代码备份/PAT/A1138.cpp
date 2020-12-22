#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<memory.h>
using std::cin;
using std::cout;
using std::endl;

int N;
int preorder[50000];
int inorder[50000];

int find_left(int *po, int*io, int n)
{
	if (n <= 1)return po[0];
	int k = 0;
	while (po[0] != io[k])k++;
	if (k < 1)return find_left(&po[1], &io[1], n - 1);
	return find_left(&po[1], io, k);
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> preorder[i];
	for (int i = 0; i < N; i++)
		cin >> inorder[i];
	int r = find_left(&preorder[0], &inorder[0], N);
	cout << r;
	return 0;
}

/*ÕýÈ·*/