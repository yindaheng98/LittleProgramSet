// mystery_hack.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<string.h>
#include<Windows.h>

int __fastcall sub_E01580(int a1, const char *a2)
{
	int v2 = 0;
	int v3 = 0;
	signed int v4 = (signed int)strlen(a2) >> 1;
	int v5 = 1000 * a2[v4];
	int v6 = 0;
	if (v4 >= 2)
	{
		do
		{
			v2 += 10 * a2[v6];
			v3 += 10 * a2[v6 + 1];
			v6 += 2;
		} while (v6 < v4 - 1);
	}
	if (v6 < v4)
		v5 += 10 * a2[v6];
	return v5 + v3 + v2;
}

int main()
{
	char username[80];
	printf("�����û���(һ�����Ȳ�С��5�ַ��Ļ�������)��\n");
	scanf("%s", username);
	int len = strlen(username);
	if (len<5)
	{
		printf("����С��5�ַ�\n");
		system("pause");
		return 0;
	}
	int len_d2 = len >> 1;
	int v4 = 0;
	if (len_d2 > 0)
	{
		char*v5 = username + len - 1;
		do
		{
			if (username[v4] != *v5)
				break;
			++v4;
			--v5;
		} while (v4 < len_d2);
	}
	if (v4 != len_d2)
	{
		printf("���ǻ�������\n");
		system("pause");
		return 0;
	}
	printf("���кţ�\n");
	printf("%d\n", sub_E01580(0, username));
	system("pause");
	return 0;
}

