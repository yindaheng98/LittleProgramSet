#include"stdafx.h"
#define KEY_SIZE 20//图例尺寸
#define SCR_HIGTH 660//屏幕高
#define SCR_WIDTH 1200//屏幕宽
#define UNIT 10//横坐标轴标记数
#define CHANGE 30000//缩放比例

extern vector<Algo>data;

void paint(CDC*pDC)
{
	int i = 0;
	for (int i = 0; i <= UNIT; i++)
	{
		CString num;
		num.Format(_T("%d"), DATA_WIDTH / UNIT*i);
		pDC->TextOutW(SCR_WIDTH / UNIT*i, SCR_HIGTH, num);
	}
	pDC->TextOutW(SCR_WIDTH, SCR_HIGTH, _T("数据量"));
	for (Algo d : data)
	{
		pDC->TextOutW(KEY_SIZE, KEY_SIZE*i, d.name);//画图例上的文字
		CBrush brush(RGB((50 * i) % 255, (100 * i) % 255, (200 * i) % 125 + 125));
		CRect rect(0, i*KEY_SIZE, KEY_SIZE, (i + 1)*KEY_SIZE);
		pDC->FillRect(&rect, &brush);
		pDC->SelectObject(brush);//画图例
		CPen pen(NULL, 1, RGB((50 * i) % 255, (100 * i) % 255, (200 * i) % 125+125));//设置颜色
		pDC->SelectObject(&pen);
		int j = 1;
		pDC->MoveTo(0, SCR_HIGTH);
		for (long long p : d.data)//画线
			pDC->LineTo((j++) * SCR_WIDTH / DATA_COUNT, SCR_HIGTH - p / CHANGE);
		i++;
		pDC->SelectObject(pen);
	}
}