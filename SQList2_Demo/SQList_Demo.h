// SQList_Demo.h : main header file for the SQLIST_DEMO application
//

#if !defined(AFX_SQLIST_DEMO_H__52D42A28_153D_40A8_BA31_9046CA6535C6__INCLUDED_)
#define AFX_SQLIST_DEMO_H__52D42A28_153D_40A8_BA31_9046CA6535C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSQList_DemoApp:
// See SQList_Demo.cpp for the implementation of this class
//

class CSQList_DemoApp : public CWinApp
{
public:
	CSQList_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQList_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSQList_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLIST_DEMO_H__52D42A28_153D_40A8_BA31_9046CA6535C6__INCLUDED_)
