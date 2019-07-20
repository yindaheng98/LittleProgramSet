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

#define LIST_INIT_SIZE 100 //线性表初始空间分配量  
#define LISTINCREMENT   10 //线性表空间分配的增量 

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
	ElemType  *elem;        //存储空间的基地址  
	int      length;        //当前的长度  
	int      listsize;      //当前分配的存储容量
} Sqlist;
//---------------------------------------------------------------
//   1: InitList(L);                         /* 构造线性表 */
//   **2: DestroyList(L);                      /* 销毁线性表 */  
//   *3: ClearList(L);                        /* 将线性表置空 */
//   *4: ListEmpty(L);                        /* 判断线性表是否为空 */
//   *5: ListLength(L);                       /* 返回线性表长度 */
//   *6: GetElem(L, i, &e);                   /* 用e返回L中第i个元素 */
//   *7: LocateElem(L, e, compare());         /* 返回L中第一个与e满足关系compare()的元素 */
//   *8: PriorElem(L, cur_e, &pre_e);         /* 返回cur_e的前驱元素 */
//   *9: NextElem(L, cur_e, &next_e);         /* 返回cur_e的后继元素 */
//  10: InsertList(L, i, e);                 /* 在L中位置i之前插入元素e */
//  11: ListDelete(L, i, &e);                /* 删除L中第i个元素并用e返回被删元素的值 */
//  *12: ListTraverse(L, visit());            /* 对每个元素调用visit() */
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
	Status Travel(Sqlist L,CListCtrl &m_List);//在表格控件输出数据
	Sqlist TairList;//存储数据
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
