
// SDGraph.h : SDGraph Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CSDGraphApp:
// �йش����ʵ�֣������ SDGraph.cpp
//

class CSDGraphApp : public CWinApp
{
public:
	CSDGraphApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDGraphApp theApp;
