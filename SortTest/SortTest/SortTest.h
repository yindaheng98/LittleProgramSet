
// SortTest.h : SortTest Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSortTestApp:
// �йش����ʵ�֣������ SortTest.cpp
//

class CSortTestApp : public CWinApp
{
public:
	CSortTestApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSortTestApp theApp;
