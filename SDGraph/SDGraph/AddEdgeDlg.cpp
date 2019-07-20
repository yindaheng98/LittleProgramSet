// AddEdgeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SDGraph.h"
#include "AddEdgeDlg.h"
#include "afxdialogex.h"


// CAddEdgeDlg 对话框

IMPLEMENT_DYNAMIC(CAddEdgeDlg, CDialogEx)

CAddEdgeDlg::CAddEdgeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_start(_T(""))
	, m_end(_T(""))
	, m_weight(0)
{

}

CAddEdgeDlg::~CAddEdgeDlg()
{
}

void CAddEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_start);
	DDX_Text(pDX, IDC_EDIT4, m_end);
	DDX_Text(pDX, IDC_EDIT1, m_weight);
}


BEGIN_MESSAGE_MAP(CAddEdgeDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddEdgeDlg 消息处理程序
