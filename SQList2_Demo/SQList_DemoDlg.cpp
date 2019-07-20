// SQList_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SQList_Demo.h"
#include "SQList_DemoDlg.h"
#include"InsertDlg.h"
#include"OutDlg.h"
#include <fstream>
#include <string>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQList_DemoDlg dialog

CSQList_DemoDlg::CSQList_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSQList_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQList_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSQList_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQList_DemoDlg)
	DDX_Control(pDX, IDC_LIST_DEAL, m_list_deal);
	DDX_Control(pDX, IDC_LIST_ORIG, m_list_orig);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSQList_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSQList_DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INSERT, &CSQList_DemoDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_CLEAR, &CSQList_DemoDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_OUT2, &CSQList_DemoDlg::OnBnClickedOut2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQList_DemoDlg message handlers

BOOL CSQList_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_list_orig.ModifyStyle(0, LVS_REPORT);// 报表模式                
    m_list_orig.SetExtendedStyle(m_list_orig.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 间隔线+行选中 
	m_list_orig.InsertColumn(0,"染色体号");  
    m_list_orig.InsertColumn(1,"类型");
	m_list_orig.InsertColumn(2,"起始位置");
	m_list_orig.InsertColumn(3,"终止位置");
	m_list_orig.InsertColumn(4,"正负链");
	CRect rect;  
	m_list_orig.GetClientRect(rect); //获得当前客户区信息  
	m_list_orig.SetColumnWidth(0, rect.Width()/5); //设置列的宽度。  
	m_list_orig.SetColumnWidth(1, rect.Width()/5);  
	m_list_orig.SetColumnWidth(2, rect.Width()/5); //设置列的宽度。  
	m_list_orig.SetColumnWidth(3, rect.Width()/5);  
	m_list_orig.SetColumnWidth(4, rect.Width()/5); //设置列的宽度。   

	m_list_deal.ModifyStyle(0, LVS_REPORT);// 报表模式                
    m_list_deal.SetExtendedStyle(m_list_deal.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 间隔线+行选中 
	m_list_deal.InsertColumn(0,"染色体号");  
    m_list_deal.InsertColumn(1,"类型");
	m_list_deal.InsertColumn(2,"起始位置");
	m_list_deal.InsertColumn(3,"终止位置");
	m_list_deal.InsertColumn(4,"正负链");
	 
	m_list_deal.GetClientRect(rect); //获得当前客户区信息  
	m_list_deal.SetColumnWidth(0, rect.Width()/5); //设置列的宽度。  
	m_list_deal.SetColumnWidth(1, rect.Width()/5);  
	m_list_deal.SetColumnWidth(2, rect.Width()/5); //设置列的宽度。  
	m_list_deal.SetColumnWidth(3, rect.Width()/5);  
	m_list_deal.SetColumnWidth(4, rect.Width()/5); //设置列的宽度。
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSQList_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSQList_DemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSQList_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSQList_DemoDlg::OnOpen() 
{
	InitList(TairList);
	InitList(TairList1);//初始化线性表
	CFileDialog openDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"GFF File(*.gff)|*.gff||");
	if(openDlg.DoModal()==IDOK)  
	{  
		  CString FilePathName;  
		  FilePathName=openDlg.GetPathName();  
		  std::ifstream GffFile(FilePathName);
		  GFF gene;	
		  //使用临时变量进行赋值
		  std::string chr,source,type,start,end,score,strand,phase,attr;
		  int i = 1;
		  while(!GffFile.eof()){
			GffFile >> chr >> source >> type >> start >> end >> score >> strand >> phase >> attr;
			gene.chr.Format("%s", chr.c_str());
			gene.source.Format("%s", source.c_str());
			gene.type.Format("%s", type.c_str());
			gene.start= atoi(start.c_str());
			gene.end=atoi(end.c_str());
			gene.phase=atoi(phase.c_str());
			gene.score=atof(score.c_str());
			gene.strand=strand[0];
			gene.attributes.Format("%s",attr.c_str());
			InsertList(TairList, gene, i++);//线性表最后插入
		  }
		  Travel(TairList, m_list_orig);
	} 
}

ElemType CSQList_DemoDlg::ReturnElem(Linklist & L, int i)
{
	ElemType temp;//临时变量
	GetElem(L, i, temp);//调用取元素函数
	return temp;//返回所取元素
}

Status CSQList_DemoDlg::GetElem(Linklist & L, int i, ElemType & e)
{
	Linklist p = L->next;
	int j = 1;//初始化
	while (p&&j < i) {
		p = p->next; ++j;
	}//顺指针向后查找，直到p指向第i个元素或p为空
	if (!p || j > i)return ERROR;
	e = p->data;
	return OK;
}

Status CSQList_DemoDlg::InitList(Linklist &L)
{
	if (L = (Linklist)malloc(sizeof(LNode)))//分配头节点
	{
		L->next = NULL;
		return OK;
	}
	else return ERROR;
}

Status CSQList_DemoDlg::InsertList(Linklist &L, ElemType e, int i)
{
	Linklist p = L;
	int j = 0;
	while (p&&j < i - 1) {
		p = p->next; ++j;
	}//寻找第i-1个节点
	if (!p || j > i - 1)return ERROR;				//i小于1或者大于表长+1
	Linklist s = new LNode;//(Linklist)malloc(sizeof(LNode));	//生成新节点
	s->data = e; 
	s->next = p->next;					//插入L中
	p->next = s;
	return OK;
}


Status CSQList_DemoDlg::Travel(Linklist L, CListCtrl &m_List)
{
	CString str;
	if (L)L = L->next;//如果表头不为空
	for (int i = 0; L; i++)
	{
		m_List.InsertItem(i, L->data.chr);//插入新行
		m_List.SetItemText(i, 1, L->data.type);//显示数据
		str.Format("%d", L->data.start);//转换格式
		m_List.SetItemText(i, 2, _T(str));//显示数据
		str.Format("%d", L->data.end);//转换格式
		m_List.SetItemText(i, 3, _T(str));//显示数据
		str.Format("%c", L->data.strand);//转换格式
		m_List.SetItemText(i, 4, _T(str));//显示数据
		L = L->next;//L指向下一位
	}
	return OK;
}

void CSQList_DemoDlg::OnDel() 
{
	int selectcolumn = m_list_deal.GetSelectionMark();//获得当前选中行
	if (selectcolumn != -1)
	{
		selectcolumn++;
		ListDelete(TairList1, selectcolumn);//调用删除函数
		m_list_deal.DeleteAllItems();
		Travel(TairList1, m_list_deal);//更新显示
	}	
}

Status CSQList_DemoDlg::DestroyList(Linklist &L)
{
	Linklist p;
	while (L)
	{
		p = L;
		L = L->next;//指向下一位
		free(p);//释放p所指空间
	}
	return OK;
}

Status CSQList_DemoDlg::ListDelete(Linklist &L, int i, ElemType &e)
{
	Linklist p = L;
	int j = 0;
	while (p->next&&j < i - 1) {//寻找第i个节点，令p指向其前驱
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;//删除位置不合理
	Linklist q = p->next; p->next = q->next;//删除并释放节点
	e = q->data; free(q);
	return OK;
}

Status CSQList_DemoDlg::ListDelete(Linklist &L, int i)
{
	Linklist p = L;
	int j = 0;
	while (p->next&&j < i - 1) {//寻找第i个节点，令p指向其前驱
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;//删除位置不合理
	Linklist q = p->next; p->next = q->next;//删除并释放节点
	free(q);
	return OK;
}

void CSQList_DemoDlg::OnBnClickedInsert()
{
	int selectcolumn1 = m_list_deal.GetSelectionMark();//获得当前选中行
	if (selectcolumn1 != -1)
	{
		selectcolumn1 += 2;
		CInsertDlg selectdlg;
		int result = selectdlg.DoModal();//在插入新窗口指定插入数据
		ElemType temp;
		if (result = IDOK)
		{
			temp = { selectdlg.m_chr,"\0",selectdlg.m_type,selectdlg.m_start,selectdlg.m_end,0,selectdlg.m_strand ? '+' : '-',0,"\0" };
			InsertList(TairList1, temp, selectcolumn1);//调用插入函数
			m_list_deal.DeleteAllItems();
			Travel(TairList1, m_list_deal);//更新数据
		}
	}
}


void CSQList_DemoDlg::OnBnClickedClear()
{
	DestroyList(TairList);
	DestroyList(TairList1);//清理数据
	m_list_orig.DeleteAllItems();
	m_list_deal.DeleteAllItems();
	Travel(TairList, m_list_orig);
	Travel(TairList, m_list_deal);//更新显示
}


void CSQList_DemoDlg::OnBnClickedOut2()
{
	m_list_deal.DeleteAllItems();//清屏
	int selectcolumn = m_list_orig.GetSelectionMark();//获得当前选中行
	if (selectcolumn != -1);
	InsertList(TairList1, ReturnElem(TairList, selectcolumn + 1), 1);//调用插入函数，插入当前选中行对应项
	Travel(TairList1, m_list_deal);//更新显示
}
