
// Calculate1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculate1.h"
#include "Calculate1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculate1Dlg 对话框



CCalculate1Dlg::CCalculate1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATE1_DIALOG, pParent)
	, m_xstr(_T("0"))
	, m_ystr(_T("0"))
	, m_zstr(_T("0"))
	, x(0)
	, y(0)
	, z(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculate1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_xstr);
	DDX_Text(pDX, IDC_EDIT2, m_ystr);
	DDX_Text(pDX, IDC_EDIT3, m_zstr);
}

BEGIN_MESSAGE_MAP(CCalculate1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculate1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculate1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculate1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculate1Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCalculate1Dlg 消息处理程序

BOOL CCalculate1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculate1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculate1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculate1Dlg::OnBnClickedButton1()
{
	UpdateData(true);
	x = _ttof(m_xstr);
	y = _ttof(m_ystr);
	z = x + y;
	if (z - int(z) <= 1e-5)m_zstr.Format(_T("%d"), (int)z);
	else m_zstr.Format(_T("%lf"), z);
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CCalculate1Dlg::OnBnClickedButton2()
{
	UpdateData(true);
	x = _ttof(m_xstr);
	y = _ttof(m_ystr);
	z = x - y;
	if (z - int(z) <= 1e-5)m_zstr.Format(_T("%d"), (int)z);
	else m_zstr.Format(_T("%lf"), z);
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CCalculate1Dlg::OnBnClickedButton3()
{
	UpdateData(true);
	x = _ttof(m_xstr);
	y = _ttof(m_ystr);
	z = x * y;
	if (z - int(z) <= 1e-5)m_zstr.Format(_T("%d"), (int)z);
	else m_zstr.Format(_T("%lf"), z);
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CCalculate1Dlg::OnBnClickedButton4()
{
	UpdateData(true);
	x = _ttof(m_xstr);
	y = _ttof(m_ystr);
	if (y)
	{
		z = x / y;
		if (z - int(z) <= 1e-5)m_zstr.Format(_T("%d"), (int)z);
		else m_zstr.Format(_T("%lf"), z);
	}
	else
	{
		m_zstr = "error";
	}
	UpdateData(false);// TODO: 在此添加控件通知处理程序代码
}
