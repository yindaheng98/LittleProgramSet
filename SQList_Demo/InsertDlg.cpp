// InsertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SQList_Demo.h"
#include "InsertDlg.h"
#include "afxdialogex.h"


// CInsertDlg 对话框

IMPLEMENT_DYNAMIC(CInsertDlg, CDialogEx)

CInsertDlg::CInsertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSERT, pParent)
	, m_start(0)
	, m_end(0)
	, m_chr(_T(""))
	, m_type(_T(""))
	, m_strand(0)
{

}

CInsertDlg::~CInsertDlg()
{
}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_start);
	DDX_Text(pDX, IDC_EDIT2, m_end);
	DDX_Text(pDX, IDC_EDIT3, m_chr);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_CBIndex(pDX, IDC_COMBO2, m_strand);
}


BEGIN_MESSAGE_MAP(CInsertDlg, CDialogEx)
END_MESSAGE_MAP()


// CInsertDlg 消息处理程序
