
// DataStruct1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DataStruct1.h"
#include "DataStruct1Dlg.h"
#include "afxdialogex.h"
#include"CDataString.h"
#include<vector>
using std::wstring;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataStruct1Dlg �Ի���



CDataStruct1Dlg::CDataStruct1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATASTRUCT1_DIALOG, pParent)
	, text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataStruct1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, text);
}

BEGIN_MESSAGE_MAP(CDataStruct1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_FILE_OPEN, &CDataStruct1Dlg::OnBnClickedFileOpen)
	ON_BN_CLICKED(ID_DATADEAL, &CDataStruct1Dlg::OnBnClickedDatadeal)
END_MESSAGE_MAP()


// CDataStruct1Dlg ��Ϣ�������

BOOL CDataStruct1Dlg::OnInitDialog()
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

void CDataStruct1Dlg::OnPaint()
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
HCURSOR CDataStruct1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDataStruct1Dlg::OnBnClickedFileOpen()
{
	extern CString filepath;
	CFileDialog fdlg(true, _T("gff"), NULL, NULL, _T("�ļ� (*.gff;)|*.gff||"), NULL);
	INT_PTR result = fdlg.DoModal();//ѡ���ļ�
	if (result == IDOK)filepath = fdlg.GetPathName();// ��ȡ�ļ�·��
}


void CDataStruct1Dlg::OnBnClickedDatadeal()
{
	extern CString filepath;
	wifstream file(filepath);
	extern std::vector<CDataString>data;
	do
	{
		data.push_back(CDataString(file));
	} while (!file.eof());
	text=CString(_T("Ⱦɫ���\t��������\t��ʼλ��\t��ֹλ��\t������\r\n"));
	wstring temptext;
	CString temptext1;
	for (CDataString d : data)
		temptext += (d.str[0] + L"\t" + d.str[2] + L"\t" + d.str[3] + L"\t" + d.str[4] + L"\t" + d.str[6] + L"\r\n");// ������������ӳɱ��
	temptext1.Format(_T("%s"), temptext.c_str());
	text += temptext1;
	UpdateData(0);//�������
}
