
// GFFViewerSDI v2.h : GFFViewerSDI v2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGFFViewerSDIv2App:
// �йش����ʵ�֣������ GFFViewerSDI v2.cpp
//

class CGFFViewerSDIv2App : public CWinApp
{
public:
	CGFFViewerSDIv2App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGFFViewerSDIv2App theApp;
