// AddPointDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SDGraph.h"
#include "AddPointDlg.h"
#include "afxdialogex.h"


// CAddPointDlg 对话框

IMPLEMENT_DYNAMIC(CAddPointDlg, CDialogEx)

CAddPointDlg::CAddPointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
{

}

CAddPointDlg::~CAddPointDlg()
{
}

void CAddPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_name);
}


BEGIN_MESSAGE_MAP(CAddPointDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddPointDlg 消息处理程序
