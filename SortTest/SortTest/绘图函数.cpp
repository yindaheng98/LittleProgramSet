#include"stdafx.h"
#define KEY_SIZE 20//ͼ���ߴ�
#define SCR_HIGTH 660//��Ļ��
#define SCR_WIDTH 1200//��Ļ��
#define UNIT 10//������������
#define CHANGE 30000//���ű���

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
	pDC->TextOutW(SCR_WIDTH, SCR_HIGTH, _T("������"));
	for (Algo d : data)
	{
		pDC->TextOutW(KEY_SIZE, KEY_SIZE*i, d.name);//��ͼ���ϵ�����
		CBrush brush(RGB((50 * i) % 255, (100 * i) % 255, (200 * i) % 125 + 125));
		CRect rect(0, i*KEY_SIZE, KEY_SIZE, (i + 1)*KEY_SIZE);
		pDC->FillRect(&rect, &brush);
		pDC->SelectObject(brush);//��ͼ��
		CPen pen(NULL, 1, RGB((50 * i) % 255, (100 * i) % 255, (200 * i) % 125+125));//������ɫ
		pDC->SelectObject(&pen);
		int j = 1;
		pDC->MoveTo(0, SCR_HIGTH);
		for (long long p : d.data)//����
			pDC->LineTo((j++) * SCR_WIDTH / DATA_COUNT, SCR_HIGTH - p / CHANGE);
		i++;
		pDC->SelectObject(pen);
	}
}