#include "stdafx.h"
#include<iostream>
#include<string.h>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	int T, dp[31][31] = { { 0 } };
	dp[2][3] = dp[3][2] = 1;
	for (int i = 3; i<31; i++)
		for (int j = 3; j<31; j++)
		{
			dp[i][j] += dp[i - 1][j - 2];
			dp[i][j] += dp[i - 2][j - 1];
		}
	cin >> T;
	for (int I = 0; I<T; I++)
	{
		int a, b;
		cin >> a >> b;
		cout << "Chessboard #" << I + 1 << ':' << dp[a][b] << endl;
	}
	return 0;
}

/*这不是动态规划*/
/*题中所述走法不可能出现两点间路径不唯一的情况*/
/*正确*/
