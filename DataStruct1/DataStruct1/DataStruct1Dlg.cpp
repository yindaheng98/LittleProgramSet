
// DataStruct1Dlg.cpp : 实现文件
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


// CDataStruct1Dlg 对话框



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


// CDataStruct1Dlg 消息处理程序

BOOL CDataStruct1Dlg::OnInitDialog()
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

void CDataStruct1Dlg::OnPaint()
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
HCURSOR CDataStruct1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDataStruct1Dlg::OnBnClickedFileOpen()
{
	extern CString filepath;
	CFileDialog fdlg(true, _T("gff"), NULL, NULL, _T("文件 (*.gff;)|*.gff||"), NULL);
	INT_PTR result = fdlg.DoModal();//选择文件
	if (result == IDOK)filepath = fdlg.GetPathName();// 获取文件路径
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
	text=CString(_T("染色体号\t基因类型\t起始位置\t终止位置\t正负链\r\n"));
	wstring temptext;
	CString temptext1;
	for (CDataString d : data)
		temptext += (d.str[0] + L"\t" + d.str[2] + L"\t" + d.str[3] + L"\t" + d.str[4] + L"\t" + d.str[6] + L"\r\n");// 将数据组合连接成表格
	temptext1.Format(_T("%s"), temptext.c_str());
	text += temptext1;
	UpdateData(0);//输出数据
}
