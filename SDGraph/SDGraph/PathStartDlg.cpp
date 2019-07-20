// PathStartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SDGraph.h"
#include "PathStartDlg.h"
#include "afxdialogex.h"


// CPathStartDlg 对话框

IMPLEMENT_DYNAMIC(CPathStartDlg, CDialogEx)

CPathStartDlg::CPathStartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_start(_T(""))
{

}

CPathStartDlg::~CPathStartDlg()
{
}

void CPathStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_start);
}


BEGIN_MESSAGE_MAP(CPathStartDlg, CDialogEx)
END_MESSAGE_MAP()


// CPathStartDlg 消息处理程序
