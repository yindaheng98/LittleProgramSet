// OutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SQList_Demo.h"
#include "OutDlg.h"
#include "afxdialogex.h"


// COutDlg �Ի���

IMPLEMENT_DYNAMIC(COutDlg, CDialogEx)

COutDlg::COutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OUT, pParent)
	, m_outtype(_T(""))
{

}

COutDlg::~COutDlg()
{
}

void COutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, m_outtype);
}


BEGIN_MESSAGE_MAP(COutDlg, CDialogEx)
END_MESSAGE_MAP()


// COutDlg ��Ϣ�������
