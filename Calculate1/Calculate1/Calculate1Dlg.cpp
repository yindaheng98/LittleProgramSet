
// Calculate1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Calculate1.h"
#include "Calculate1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculate1Dlg �Ի���



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


// CCalculate1Dlg ��Ϣ�������

BOOL CCalculate1Dlg::OnInitDialog()
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

void CCalculate1Dlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	UpdateData(false);// TODO: �ڴ���ӿؼ�֪ͨ����������
}
