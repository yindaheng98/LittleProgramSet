
// CalculatorStackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CalculatorStack.h"
#include "CalculatorStackDlg.h"
#include "afxdialogex.h"
#include"calculatorCore.h"
#include<stack>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorStackDlg 对话框



CCalculatorStackDlg::CCalculatorStackDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATORSTACK_DIALOG, pParent)
	, m_expr(_T(""))
	, prior_ope(false)
	, tempnum(0)
	, m_result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorStackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_expr);
	DDX_Text(pDX, IDC_EDIT2, m_result);
}

BEGIN_MESSAGE_MAP(CCalculatorStackDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorStackDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorStackDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorStackDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorStackDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorStackDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorStackDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorStackDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorStackDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorStackDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CCalculatorStackDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CCalculatorStackDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CCalculatorStackDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CCalculatorStackDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CCalculatorStackDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CCalculatorStackDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CCalculatorStackDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON15, &CCalculatorStackDlg::OnBnClickedButton15)
END_MESSAGE_MAP()


// CCalculatorStackDlg 消息处理程序

BOOL CCalculatorStackDlg::OnInitDialog()
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

void CCalculatorStackDlg::OnPaint()
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
HCURSOR CCalculatorStackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorStackDlg::OnBnClickedButton1()
{
	m_expr += '1';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr,i));//运算表达式
	else 
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton2()
{
	m_expr += '2';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton3()
{
	m_expr += '3';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton4()
{
	m_expr += '4';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton5()
{
	m_expr += '5';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton6()
{
	m_expr += '6';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton7()
{
	m_expr += '7';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton8()
{
	m_expr += '8';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton9()
{
	m_expr += '9';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton10()
{
	m_expr += '0';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton11()
{
	m_expr += '+';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton12()
{
	m_expr += '-';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton13()
{
	m_expr += '*';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton14()
{
	m_expr += '/';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButtonLeft()
{
	m_expr += '(';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButtonRight()
{
	m_expr += ')';//增加表达式
	int i = 0;
	if (check(m_expr))//检查表达式
		m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton15()
{
	if (m_expr.GetLength())								//表达式不为空
	{
		m_expr = m_expr.Left(m_expr.GetLength() - 1);	//删最后一位
		int i = 0;
		if (check(m_expr))//检查表达式
			m_result.Format(_T("%f"), calculate(m_expr, i));//运算表达式
		else
			m_result = "error";
		UpdateData(0);
	}
}
