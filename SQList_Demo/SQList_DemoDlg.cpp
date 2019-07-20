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
	//CRect rect;  
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
	// TODO: Add your control notification handler code here
	InitList(TairList,LIST_INIT_SIZE);
	InitList(TairList1, LIST_INIT_SIZE);//初始化线性表
	//CFileDialog openDlg(TRUE, "GFF File(*.gff)|*.gff", NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"GFF File(*.gff)|*.gff3||", this);
	CFileDialog openDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"GFF File(*.gff)|*.gff||");
	if(openDlg.DoModal()==IDOK)  
	{  
		  CString FilePathName;  
		  FilePathName=openDlg.GetPathName();  
		  //MessageBox(str); 
		 
		  std::ifstream GffFile(FilePathName);
		  GFF gene;
		  std::string chr,source,type,start,end,score,strand,phase,attr;
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
			InsertList(TairList,gene,TairList.length+1);//线性表最后插入
			//CString tmp;
			//tmp.Format("%d",temp);
			//MessageBox(tmp);
		  }
		  Travel(TairList, m_list_orig);
	} 
}

Status CSQList_DemoDlg::InitList(Sqlist &L, int length)
{
	if (length== 0) length = LIST_INIT_SIZE;  
    //L.elem = (ElemType *)malloc(length * sizeof(ElemType));  
	L.elem=new ElemType[length];
    if(!L.elem) exit(OVERFLOW);  //分配存储空间失败  
    L.length = 0;                //初始空表长度为0  
    L.listsize = length ;//初始存储容量  
    return OK;
}

//DEL Status CSQList_DemoDlg::insertList(SqList &L, ElemType e, int i)
//DEL {
//DEL 	
//DEL }

Status CSQList_DemoDlg::InsertList(Sqlist &L, ElemType e, int i)
{
	ElemType *p,  *q;  
    if(i<1 ||i > L.length+1) return ERROR;  //i值不合法  
    if (L.length >= L.listsize) {  
        ElemType *newbase = (ElemType *)realloc(L.elem ,(L.listsize +LISTINCREMENT)*sizeof(ElemType));  
        if(!newbase) exit(OVERFLOW);   //存储分配失败    
        L.elem = newbase;               //新基值  
        L.listsize += LISTINCREMENT;    //增加存储容量  
    }  
    q = &L.elem[i-1];                     //q为插入的位置  
    for (p = &L.elem[L.length-1]; p>=q; --p) {  
        *(p+1) = *p;                    //i元素之后的元素往后移动  
    }  
    *q = e;                             //插入e  
    L.length +=1;  
    return OK;
}


Status CSQList_DemoDlg::Travel(Sqlist L, CListCtrl &m_List)
{
	CString str;
	for(int i=0; i<L.length; i++)  
    {
		m_List.InsertItem(i,L.elem[i].chr); 
		m_List.SetItemText(i, 1, L.elem[i].type);
		str.Format("%d",L.elem[i].start);
		m_List.SetItemText(i, 2, _T(str));
		str.Format("%d",L.elem[i].end);
		m_List.SetItemText(i, 3, _T(str));
		str.Format("%c",L.elem[i].strand);
		m_List.SetItemText(i, 4, _T(str));
	}
	return OK;
}

void CSQList_DemoDlg::OnDel() 
{
	int selectcolumn = m_list_orig.GetSelectionMark();//获取当前选中行行数
	if (selectcolumn != -1)
	{
		selectcolumn += 1;
		ListDelete(TairList, selectcolumn);//删除数据
		m_list_orig.DeleteAllItems();
		Travel(TairList, m_list_orig);//更新显示
	}
}

Status CSQList_DemoDlg::DestroyList(Sqlist &L)
{
	delete[](L.elem);//销毁顺序表
	L.length = L.listsize = 0;//表长置0
	return OK;
}

Status CSQList_DemoDlg::ListDelete(Sqlist &L, int i, ElemType &e)
{
	ElemType* p,*q;
   if (i < 1 || i > L.length) return ERROR;    
   p=&(L.elem[i-1]);
   e = *p;
   q=L.elem+L.length-1;
   for (++p; p <=q;++p) {
        *(p-1) = *p;        
    }
    --L.length;    
    return OK;
}

Status CSQList_DemoDlg::ListDelete(Sqlist &L, int i)
{
	ElemType* p, *q;
	if (i < 1 || i > L.length) return ERROR;
	p = &(L.elem[i - 1]);
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	--L.length;
	return OK;
}

void CSQList_DemoDlg::OnBnClickedInsert()
{
	int selectcolumn = m_list_orig.GetSelectionMark();
	int selectcolumn1 = m_list_deal.GetSelectionMark();//获取当前选中行行数
	if (selectcolumn1 != -1)
	{
		selectcolumn1 += 2;
		CInsertDlg selectdlg;
		int result = selectdlg.DoModal();
		ElemType temp;//临时变量
		if (result = IDOK)
		{
			temp = { selectdlg.m_chr,"\0",selectdlg.m_type,selectdlg.m_start,selectdlg.m_end,0,selectdlg.m_strand ? '+' : '-',0,"\0" };
			//临时变量赋值
			InsertList(TairList1, temp, selectcolumn1);//插入
			m_list_deal.DeleteAllItems();//更新显示
			Travel(TairList1, m_list_deal);
		}
	}
}


void CSQList_DemoDlg::OnBnClickedClear()
{
	DestroyList(TairList);
	DestroyList(TairList1);//销毁顺序表
	m_list_orig.DeleteAllItems();//更新显示
	m_list_deal.DeleteAllItems();
	Travel(TairList, m_list_orig);
	Travel(TairList, m_list_deal);
}


void CSQList_DemoDlg::OnBnClickedOut2()
{
	int selectcolumn = m_list_orig.GetSelectionMark();//获取当前选中行行数
	if (selectcolumn != -1)
	{
		InsertList(TairList1, TairList.elem[selectcolumn], TairList1.length+1);//插入
		m_list_deal.DeleteAllItems();
		Travel(TairList1, m_list_deal);
	}//更新显示
}
