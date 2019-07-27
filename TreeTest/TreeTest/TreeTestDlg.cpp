
// TreeTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TreeTest.h"
#include "TreeTestDlg.h"
#include "afxdialogex.h"
#include"CGene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeTestDlg �Ի���



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


// CTreeTestDlg ��Ϣ�������

BOOL CTreeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CString filepath;
	CFileDialog fdlg(TRUE, _T("gff"), NULL, NULL, _T("�ļ� (*.gff;)|*.gff||"), NULL);
	INT_PTR result = fdlg.DoModal();
	if (result == IDOK)filepath = fdlg.GetPathName();
	extern CDataString data;
	data = CDataString(filepath);
	extern CGene gene;
	gene = CGene(data);
	HTREEITEM TreeRoot = m_tree.InsertItem(_T("Gene"));
	gene.paint(m_tree, TreeRoot);
	m_list.ModifyStyle(0, LVS_REPORT);// ����ģʽ                
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // �����+��ѡ�� 
	m_list.InsertColumn(0, _T("Ⱦɫ���"));
	m_list.InsertColumn(1, _T("����"));
	m_list.InsertColumn(2, _T("��ʼλ��"));
	m_list.InsertColumn(3, _T("��ֹλ��"));
	m_list.InsertColumn(4, _T("������"));
	CRect rect;
	m_list.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_list.SetColumnWidth(0, rect.Width() / 5); //�����еĿ��
	m_list.SetColumnWidth(1, rect.Width() / 5);
	m_list.SetColumnWidth(2, rect.Width() / 5); //�����еĿ��
	m_list.SetColumnWidth(3, rect.Width() / 5);
	m_list.SetColumnWidth(4, rect.Width() / 5); //�����еĿ��
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTreeTestDlg::OnPaint()
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
HCURSOR CTreeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTreeTestDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTreeTestDlg::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	m_list.DeleteAllItems();
	CString str;
	extern CDataString data;								//ȫ�ֱ�����������
	int i = m_tree.GetItemData(m_tree.GetSelectedItem());	//��ȡ��ǰ���λ��
	str.Format(_T("%s"), data.data[i].chr.c_str());			//������
	m_list.InsertItem(0, str);								//������
	str.Format(_T("%s"), data.data[i].type.c_str());		//�������
	m_list.SetItemText(0, 1, str);							//������
	str.Format(_T("%d"), data.data[i].start);				//������
	m_list.SetItemText(0, 2, str);							//������
	str.Format(_T("%d"), data.data[i].end);					//����յ�
	m_list.SetItemText(0, 3, str);							//������
	str.Format(_T("%c"), data.data[i].strand ? L'+' : L'-');//����յ�
	m_list.SetItemText(0, 4, str);							//������
}


void CTreeTestDlg::OnBnClickedButton2()
{
	m_list.DeleteAllItems();//ˢ��������
	extern CGene gene;//ȫ�ֱ�����������
	int n = 0;
	gene.travel(m_list, n);//��0�п�ʼ���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
