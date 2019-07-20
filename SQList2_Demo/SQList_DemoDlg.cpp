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
	m_list_orig.ModifyStyle(0, LVS_REPORT);// ����ģʽ                
    m_list_orig.SetExtendedStyle(m_list_orig.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // �����+��ѡ�� 
	m_list_orig.InsertColumn(0,"Ⱦɫ���");  
    m_list_orig.InsertColumn(1,"����");
	m_list_orig.InsertColumn(2,"��ʼλ��");
	m_list_orig.InsertColumn(3,"��ֹλ��");
	m_list_orig.InsertColumn(4,"������");
	CRect rect;  
	m_list_orig.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_list_orig.SetColumnWidth(0, rect.Width()/5); //�����еĿ�ȡ�  
	m_list_orig.SetColumnWidth(1, rect.Width()/5);  
	m_list_orig.SetColumnWidth(2, rect.Width()/5); //�����еĿ�ȡ�  
	m_list_orig.SetColumnWidth(3, rect.Width()/5);  
	m_list_orig.SetColumnWidth(4, rect.Width()/5); //�����еĿ�ȡ�   

	m_list_deal.ModifyStyle(0, LVS_REPORT);// ����ģʽ                
    m_list_deal.SetExtendedStyle(m_list_deal.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // �����+��ѡ�� 
	m_list_deal.InsertColumn(0,"Ⱦɫ���");  
    m_list_deal.InsertColumn(1,"����");
	m_list_deal.InsertColumn(2,"��ʼλ��");
	m_list_deal.InsertColumn(3,"��ֹλ��");
	m_list_deal.InsertColumn(4,"������");
	 
	m_list_deal.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_list_deal.SetColumnWidth(0, rect.Width()/5); //�����еĿ�ȡ�  
	m_list_deal.SetColumnWidth(1, rect.Width()/5);  
	m_list_deal.SetColumnWidth(2, rect.Width()/5); //�����еĿ�ȡ�  
	m_list_deal.SetColumnWidth(3, rect.Width()/5);  
	m_list_deal.SetColumnWidth(4, rect.Width()/5); //�����еĿ�ȡ�
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
	InitList(TairList1);//��ʼ�����Ա�
	CFileDialog openDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"GFF File(*.gff)|*.gff||");
	if(openDlg.DoModal()==IDOK)  
	{  
		  CString FilePathName;  
		  FilePathName=openDlg.GetPathName();  
		  std::ifstream GffFile(FilePathName);
		  GFF gene;	
		  //ʹ����ʱ�������и�ֵ
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
			InsertList(TairList, gene, i++);//���Ա�������
		  }
		  Travel(TairList, m_list_orig);
	} 
}

ElemType CSQList_DemoDlg::ReturnElem(Linklist & L, int i)
{
	ElemType temp;//��ʱ����
	GetElem(L, i, temp);//����ȡԪ�غ���
	return temp;//������ȡԪ��
}

Status CSQList_DemoDlg::GetElem(Linklist & L, int i, ElemType & e)
{
	Linklist p = L->next;
	int j = 1;//��ʼ��
	while (p&&j < i) {
		p = p->next; ++j;
	}//˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
	if (!p || j > i)return ERROR;
	e = p->data;
	return OK;
}

Status CSQList_DemoDlg::InitList(Linklist &L)
{
	if (L = (Linklist)malloc(sizeof(LNode)))//����ͷ�ڵ�
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
	}//Ѱ�ҵ�i-1���ڵ�
	if (!p || j > i - 1)return ERROR;				//iС��1���ߴ��ڱ�+1
	Linklist s = new LNode;//(Linklist)malloc(sizeof(LNode));	//�����½ڵ�
	s->data = e; 
	s->next = p->next;					//����L��
	p->next = s;
	return OK;
}


Status CSQList_DemoDlg::Travel(Linklist L, CListCtrl &m_List)
{
	CString str;
	if (L)L = L->next;//�����ͷ��Ϊ��
	for (int i = 0; L; i++)
	{
		m_List.InsertItem(i, L->data.chr);//��������
		m_List.SetItemText(i, 1, L->data.type);//��ʾ����
		str.Format("%d", L->data.start);//ת����ʽ
		m_List.SetItemText(i, 2, _T(str));//��ʾ����
		str.Format("%d", L->data.end);//ת����ʽ
		m_List.SetItemText(i, 3, _T(str));//��ʾ����
		str.Format("%c", L->data.strand);//ת����ʽ
		m_List.SetItemText(i, 4, _T(str));//��ʾ����
		L = L->next;//Lָ����һλ
	}
	return OK;
}

void CSQList_DemoDlg::OnDel() 
{
	int selectcolumn = m_list_deal.GetSelectionMark();//��õ�ǰѡ����
	if (selectcolumn != -1)
	{
		selectcolumn++;
		ListDelete(TairList1, selectcolumn);//����ɾ������
		m_list_deal.DeleteAllItems();
		Travel(TairList1, m_list_deal);//������ʾ
	}	
}

Status CSQList_DemoDlg::DestroyList(Linklist &L)
{
	Linklist p;
	while (L)
	{
		p = L;
		L = L->next;//ָ����һλ
		free(p);//�ͷ�p��ָ�ռ�
	}
	return OK;
}

Status CSQList_DemoDlg::ListDelete(Linklist &L, int i, ElemType &e)
{
	Linklist p = L;
	int j = 0;
	while (p->next&&j < i - 1) {//Ѱ�ҵ�i���ڵ㣬��pָ����ǰ��
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;//ɾ��λ�ò�����
	Linklist q = p->next; p->next = q->next;//ɾ�����ͷŽڵ�
	e = q->data; free(q);
	return OK;
}

Status CSQList_DemoDlg::ListDelete(Linklist &L, int i)
{
	Linklist p = L;
	int j = 0;
	while (p->next&&j < i - 1) {//Ѱ�ҵ�i���ڵ㣬��pָ����ǰ��
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1)return ERROR;//ɾ��λ�ò�����
	Linklist q = p->next; p->next = q->next;//ɾ�����ͷŽڵ�
	free(q);
	return OK;
}

void CSQList_DemoDlg::OnBnClickedInsert()
{
	int selectcolumn1 = m_list_deal.GetSelectionMark();//��õ�ǰѡ����
	if (selectcolumn1 != -1)
	{
		selectcolumn1 += 2;
		CInsertDlg selectdlg;
		int result = selectdlg.DoModal();//�ڲ����´���ָ����������
		ElemType temp;
		if (result = IDOK)
		{
			temp = { selectdlg.m_chr,"\0",selectdlg.m_type,selectdlg.m_start,selectdlg.m_end,0,selectdlg.m_strand ? '+' : '-',0,"\0" };
			InsertList(TairList1, temp, selectcolumn1);//���ò��뺯��
			m_list_deal.DeleteAllItems();
			Travel(TairList1, m_list_deal);//��������
		}
	}
}


void CSQList_DemoDlg::OnBnClickedClear()
{
	DestroyList(TairList);
	DestroyList(TairList1);//��������
	m_list_orig.DeleteAllItems();
	m_list_deal.DeleteAllItems();
	Travel(TairList, m_list_orig);
	Travel(TairList, m_list_deal);//������ʾ
}


void CSQList_DemoDlg::OnBnClickedOut2()
{
	m_list_deal.DeleteAllItems();//����
	int selectcolumn = m_list_orig.GetSelectionMark();//��õ�ǰѡ����
	if (selectcolumn != -1);
	InsertList(TairList1, ReturnElem(TairList, selectcolumn + 1), 1);//���ò��뺯�������뵱ǰѡ���ж�Ӧ��
	Travel(TairList1, m_list_deal);//������ʾ
}
