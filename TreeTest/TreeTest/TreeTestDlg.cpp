
// TreeTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TreeTest.h"
#include "TreeTestDlg.h"
#include "afxdialogex.h"
#include"CGene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeTestDlg 对话框



CTreeTestDlg::CTreeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TREETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CTreeTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CTreeTestDlg::OnTvnSelchangedTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CTreeTestDlg::OnNMClickTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTreeTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTreeTestDlg 消息处理程序

BOOL CTreeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString filepath;
	CFileDialog fdlg(TRUE, _T("gff"), NULL, NULL, _T("文件 (*.gff;)|*.gff||"), NULL);
	INT_PTR result = fdlg.DoModal();
	if (result == IDOK)filepath = fdlg.GetPathName();
	extern CDataString data;
	data = CDataString(filepath);
	extern CGene gene;
	gene = CGene(data);
	HTREEITEM TreeRoot = m_tree.InsertItem(_T("Gene"));
	gene.paint(m_tree, TreeRoot);
	m_list.ModifyStyle(0, LVS_REPORT);// 报表模式                
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 间隔线+行选中 
	m_list.InsertColumn(0, _T("染色体号"));
	m_list.InsertColumn(1, _T("类型"));
	m_list.InsertColumn(2, _T("起始位置"));
	m_list.InsertColumn(3, _T("终止位置"));
	m_list.InsertColumn(4, _T("正负链"));
	CRect rect;
	m_list.GetClientRect(rect); //获得当前客户区信息  
	m_list.SetColumnWidth(0, rect.Width() / 5); //设置列的宽度
	m_list.SetColumnWidth(1, rect.Width() / 5);
	m_list.SetColumnWidth(2, rect.Width() / 5); //设置列的宽度
	m_list.SetColumnWidth(3, rect.Width() / 5);
	m_list.SetColumnWidth(4, rect.Width() / 5); //设置列的宽度
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTreeTestDlg::OnPaint()
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
HCURSOR CTreeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreeTestDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CTreeTestDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	m_list.DeleteAllItems();
	CString str;
	extern CDataString data;								//全局变量引用声明
	int i = m_tree.GetItemData(m_tree.GetSelectedItem());	//获取当前点击位置
	str.Format(_T("%s"), data.data[i].chr.c_str());			//插入行
	m_list.InsertItem(0, str);								//插入列
	str.Format(_T("%s"), data.data[i].type.c_str());		//输出类型
	m_list.SetItemText(0, 1, str);							//插入列
	str.Format(_T("%d"), data.data[i].start);				//输出起点
	m_list.SetItemText(0, 2, str);							//插入列
	str.Format(_T("%d"), data.data[i].end);					//输出终点
	m_list.SetItemText(0, 3, str);							//插入列
	str.Format(_T("%c"), data.data[i].strand ? L'+' : L'-');//输出终点
	m_list.SetItemText(0, 4, str);							//插入列
}


void CTreeTestDlg::OnBnClickedButton2()
{
	m_list.DeleteAllItems();//刷新所有项
	extern CGene gene;//全局变量引用声明
	int n = 0;
	gene.travel(m_list, n);//从0行开始输出
	// TODO: 在此添加控件通知处理程序代码
}
