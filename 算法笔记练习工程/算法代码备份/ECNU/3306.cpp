#include "stdafx.h"
#include<memory.h>
#include<iostream>
#include<unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;

unsigned long P, N[4], v[4] = { 1,5,10,25 };

template<typename T>T min(T a, T b)
{
	return a < b ? a : b;
}

unsigned long DFS(short coin_type, unsigned long pack)
{
	if (pack < v[coin_type])return 0;
	if (coin_type > 0 && pack % 5 != 0)return 0;
	unsigned long sum = 0;
	for (short ct = coin_type; ct < 4; ct++)
		sum += N[ct] * v[ct];
	if (sum < pack)return 0;
	if (coin_type >= 3)
	{
		if (pack%v[3] != 0 || pack / v[3] > N[3])
			return 0;
		else return pack / v[3];
	}

	long coin_n = min<unsigned long>(pack / v[coin_type], N[coin_type]);
	while (coin_n >= 0)
	{
		unsigned long pack_next = pack - v[coin_type] * coin_n;
		if (pack_next <= 0)return coin_n;
		unsigned long coin_n_next = DFS(coin_type + 1, pack_next);
		if (coin_n_next != 0)return coin_n + coin_n_next;
		coin_n--;
	}
	return 0;
}

int main()
{
	cin >> P >> N[0] >> N[1] >> N[2] >> N[3];
	if (N[0] * v[0] + N[1] * v[1] + N[2] * v[2] + N[3] * v[3] < P)
	{
		cout << "Impossible";
		return 0;
	}
	unsigned long coin_n = DFS(0, P);
	if (coin_n > 0)cout << coin_n;
	else cout << "Impossible";
	return 0;
}

/*正确*/
/*DFS的while循环条件那里出了点小问题*/
/*不进行一定程度的剪枝会超时*/
