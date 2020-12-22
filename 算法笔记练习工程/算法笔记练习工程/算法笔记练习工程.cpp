#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<queue>
#include<vector>
#include<map>
#include <string>
#include<Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;
using std::map;
using std::pair;
using std::string;

//��remainTestCount�����Ի��ᣨ�Ӽ����Ļ��� �����ƶ��Ĵ�������eggsCount����������ȷ����¥������
int getConfirmFloors(int remainTestCount, int eggsCount) {
	if (remainTestCount == 1 || eggsCount == 1) {
		//���remainTestCount == 1��ֻ���ƶ�һ�Σ�����ֻ��ȷ����һ¥�Ƿ�Ҳ����˵����ֻ�ܷ��ڵ�һ¥��������ˣ���F == 0���������û�飬��F == 1
		//���eggsCount == 1������Ϊ1�����������û�м����ˣ�Ϊ�˱��գ���ֻ�ܴӵ�һ¥��ʼ�����ϲ��ԣ������һ¥���ˣ�ͬ�ϣ�����һ¥û��������i¥����ʽ�㲻���������ƵĲ��ԣ���Ϊ��ֻ�ܲ���remainTestCount��
		return remainTestCount;
	}
	return getConfirmFloors(remainTestCount - 1, eggsCount - 1) + 1 + getConfirmFloors(remainTestCount - 1, eggsCount);
}
int superEggDrop(int K, int N) {
	int remainTestCount = 1;//����ƶ����������ԵĴ�����
	while (getConfirmFloors(remainTestCount, K) < N) {
		++remainTestCount;
	}
	return remainTestCount;
}

int main()
{
	int m;
	cin >> m;
	while (m-- > 0)
	{
		int K, N;
		cin >> K >> N;
		printf("%d\n", superEggDrop(K, N));
	}
	system("pause");
	return 0;
}

/*��ȷ*/