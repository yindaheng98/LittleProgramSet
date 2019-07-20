// ShortPathDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SDGraph.h"
#include "ShortPathDlg.h"
#include "afxdialogex.h"


// CShortPathDlg 对话框

IMPLEMENT_DYNAMIC(CShortPathDlg, CDialogEx)

CShortPathDlg::CShortPathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_start(_T(""))
	, m_end(_T(""))
{

}

CShortPathDlg::~CShortPathDlg()
{
}

void CShortPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_start);
	DDX_Text(pDX, IDC_EDIT4, m_end);
}


BEGIN_MESSAGE_MAP(CShortPathDlg, CDialogEx)
END_MESSAGE_MAP()


// CShortPathDlg 消息处理程序
