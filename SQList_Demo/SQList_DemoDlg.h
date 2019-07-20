// SQList_DemoDlg.h : header file
//

#if !defined(AFX_SQLIST_DEMODLG_H__58B4E525_2ED6_4E8A_8A01_43BC8E3AAE6D__INCLUDED_)
#define AFX_SQLIST_DEMODLG_H__58B4E525_2ED6_4E8A_8A01_43BC8E3AAE6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSQList_DemoDlg dialog

#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2

#define LIST_INIT_SIZE 100 //���Ա��ʼ�ռ������  
#define LISTINCREMENT   10 //���Ա�ռ��������� 

typedef int Status;
typedef struct
{
	CString chr;
	CString source;
	CString type;
	int start;
	int end;
	float score;
	char strand;
	int phase;
	CString attributes;  
} GFF;
typedef GFF ElemType;
typedef struct{
	ElemType  *elem;        //�洢�ռ�Ļ���ַ  
	int      length;        //��ǰ�ĳ���  
	int      listsize;      //��ǰ����Ĵ洢����
} Sqlist;
//---------------------------------------------------------------
//   1: InitList(L);                         /* �������Ա� */
//   **2: DestroyList(L);                      /* �������Ա� */  
//   *3: ClearList(L);                        /* �����Ա��ÿ� */
//   *4: ListEmpty(L);                        /* �ж����Ա��Ƿ�Ϊ�� */
//   *5: ListLength(L);                       /* �������Ա��� */
//   *6: GetElem(L, i, &e);                   /* ��e����L�е�i��Ԫ�� */
//   *7: LocateElem(L, e, compare());         /* ����L�е�һ����e�����ϵcompare()��Ԫ�� */
//   *8: PriorElem(L, cur_e, &pre_e);         /* ����cur_e��ǰ��Ԫ�� */
//   *9: NextElem(L, cur_e, &next_e);         /* ����cur_e�ĺ��Ԫ�� */
//  10: InsertList(L, i, e);                 /* ��L��λ��i֮ǰ����Ԫ��e */
//  11: ListDelete(L, i, &e);                /* ɾ��L�е�i��Ԫ�ز���e���ر�ɾԪ�ص�ֵ */
//  *12: ListTraverse(L, visit());            /* ��ÿ��Ԫ�ص���visit() */
//------------------------------------------------------------------
class CSQList_DemoDlg : public CDialog
{
// Construction
public:
	Status InitList(Sqlist &L, int length);
	Status DestroyList(Sqlist &L);
	Status InsertList(Sqlist &L, ElemType e, int i);
    Status ListDelete(Sqlist &L, int i, ElemType &e);
	Status ListDelete(Sqlist & L, int i);
	Status Travel(Sqlist L,CListCtrl &m_List);//�ڱ��ؼ��������
	Sqlist TairList;//�洢����
	Sqlist TairList1;
	CSQList_DemoDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CSQList_DemoDlg)
	enum { IDD = IDD_SQLIST_DEMO_DIALOG };
	CListCtrl	m_list_deal;
	CListCtrl	m_list_orig;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQList_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSQList_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedOut2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLIST_DEMODLG_H__58B4E525_2ED6_4E8A_8A01_43BC8E3AAE6D__INCLUDED_)
