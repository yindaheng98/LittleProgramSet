// Feistel.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include<stdlib.h>
//#define MAX 0xFFFFFFFFFFFFFFFF
typedef unsigned long long ull;
//#define RANDKEY ((ull)(rand()*MAX))


ull F(ull r, ull K)
{
	//return 0;
	//return r;
	//return K;
	return r^K;
}

int main()
{
	srand(0);
	ull C[2] = { 0x0123456789ABCDEF,0xFEDCBA9876543210 };
	printf("明文:0x%llx,0x%llx\n", C[0], C[1]);
	ull L[5] = { C[0],0,0,0,0 };
	ull R[5] = { C[1],0,0,0,0 };
	ull K[4] = { 0x5314710854D4FA1E,0x686245650AA3A625,0x4FA496920576A2AC,0x935EF3BA573192D6};
	for (int i = 1; i <= 4; i++)
	{
		L[i] = R[i - 1];
		R[i] = L[i - 1] ^ F(R[i - 1], K[i - 1]);
	}
	printf("密文:0x%llx,0x%llx\n", L[4], R[4]);
	getchar();
    return 0;
}

