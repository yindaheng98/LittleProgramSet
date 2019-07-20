
// CalculatorStackDlg.cpp : ʵ���ļ�
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


// CCalculatorStackDlg �Ի���



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


// CCalculatorStackDlg ��Ϣ�������

BOOL CCalculatorStackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCalculatorStackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCalculatorStackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorStackDlg::OnBnClickedButton1()
{
	m_expr += '1';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr,i));//������ʽ
	else 
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton2()
{
	m_expr += '2';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton3()
{
	m_expr += '3';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton4()
{
	m_expr += '4';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton5()
{
	m_expr += '5';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton6()
{
	m_expr += '6';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton7()
{
	m_expr += '7';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton8()
{
	m_expr += '8';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton9()
{
	m_expr += '9';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton10()
{
	m_expr += '0';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton11()
{
	m_expr += '+';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton12()
{
	m_expr += '-';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton13()
{
	m_expr += '*';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton14()
{
	m_expr += '/';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButtonLeft()
{
	m_expr += '(';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButtonRight()
{
	m_expr += ')';//���ӱ��ʽ
	int i = 0;
	if (check(m_expr))//�����ʽ
		m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
	else
		m_result = "error";
	UpdateData(0);
}


void CCalculatorStackDlg::OnBnClickedButton15()
{
	if (m_expr.GetLength())								//���ʽ��Ϊ��
	{
		m_expr = m_expr.Left(m_expr.GetLength() - 1);	//ɾ���һλ
		int i = 0;
		if (check(m_expr))//�����ʽ
			m_result.Format(_T("%f"), calculate(m_expr, i));//������ʽ
		else
			m_result = "error";
		UpdateData(0);
	}
}
