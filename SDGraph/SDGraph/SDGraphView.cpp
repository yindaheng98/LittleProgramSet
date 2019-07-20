
// SDGraphView.cpp : CSDGraphView ���ʵ��
//
#include "stdafx.h"
#include"CGraph.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SDGraph.h"
#endif

extern enum condition
{
	none, mini_tree_prim, mini_tree_kruskal, dijkstra, floyed
}cdt;

extern wchar_t find_path_start;
extern wchar_t point_start;
extern wchar_t point_end;
extern Graph graph;

#include "SDGraphDoc.h"
#include "SDGraphView.h"
#include"AddPointDlg.h"
#include"AddEdgeDlg.h"
#include"PathStartDlg.h"
#include"ShortPathDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDGraphView

IMPLEMENT_DYNCREATE(CSDGraphView, CView)

BEGIN_MESSAGE_MAP(CSDGraphView, CView)
	ON_COMMAND(ID_ADD_POINT, &CSDGraphView::OnAddPoint)
	ON_COMMAND(ID_ADD_EDGE, &CSDGraphView::OnAddEdge)
	ON_COMMAND(ID_SHORT_PATH, &CSDGraphView::OnShortPath)
	ON_COMMAND(ID_PATH_POINT, &CSDGraphView::OnPathPoint)
	ON_COMMAND(ID_MINITREE_PRIM, &CSDGraphView::OnMinitreePrim)
	ON_COMMAND(ID_MINITREE_KRUSKAL, &CSDGraphView::OnMinitreeKruskal)
END_MESSAGE_MAP()

// CSDGraphView ����/����

CSDGraphView::CSDGraphView()
{
	// TODO: �ڴ˴���ӹ������

}

CSDGraphView::~CSDGraphView()
{
}

BOOL CSDGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSDGraphView ����

void CSDGraphView::OnDraw(CDC* pDC)
{
	CSDGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	graph.DFS(pDC);
	graph.BFS(pDC);
	switch (cdt)
	{
	case mini_tree_prim:graph.Primprint(pDC, find_path_start); break;
	case mini_tree_kruskal:graph.Kruskalprint(pDC, find_path_start); break;
	case dijkstra:graph.Dijkstraprint(pDC, find_path_start); break;
	case floyed:graph.Floyedprint(pDC, point_start, point_end); break;
	}
	graph.print(pDC);
}


// CSDGraphView ���

#ifdef _DEBUG
void CSDGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CSDGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDGraphDoc* CSDGraphView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDGraphDoc)));
	return (CSDGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDGraphView ��Ϣ�������


void CSDGraphView::OnAddPoint()
{
	CAddPointDlg addlg;
	if (addlg.DoModal() == IDOK)
	{
		graph.AddVex(addlg.m_name[0]);
		cdt = none;
	}
	Invalidate();
	// TODO: �ڴ���������������
}


void CSDGraphView::OnAddEdge()
{
	CAddEdgeDlg addlg;
	if (addlg.DoModal() == IDOK)
	{
		graph.AddEdge(addlg.m_start[0], addlg.m_end[0], addlg.m_weight);
		cdt = none;
	}
	Invalidate();
	// TODO: �ڴ���������������
}


void CSDGraphView::OnShortPath()
{
	CPathStartDlg pathdlg;
	if (pathdlg.DoModal() == IDOK)
	{
		find_path_start = pathdlg.m_start[0];
		cdt = dijkstra;
	}
	Invalidate();
	// TODO: �ڴ���������������
}

void CSDGraphView::OnPathPoint()
{
	CShortPathDlg pathdlg;
	if (pathdlg.DoModal() == IDOK)
	{
		cdt = floyed;
		point_start = pathdlg.m_start[0];
		point_end = pathdlg.m_end[0];
	}
	Invalidate();
	// TODO: �ڴ���������������
}


void CSDGraphView::OnMinitreePrim()
{
	CPathStartDlg pathdlg;
	if (pathdlg.DoModal() == IDOK)
	{
		find_path_start = pathdlg.m_start[0];
		cdt = mini_tree_prim;
	}
	Invalidate();
	// TODO: �ڴ���������������
}


void CSDGraphView::OnMinitreeKruskal()
{
	CPathStartDlg pathdlg;
	if (pathdlg.DoModal() == IDOK)
	{
		find_path_start = pathdlg.m_start[0];
		cdt = mini_tree_kruskal;
	}
	Invalidate();

	// TODO: �ڴ���������������
}
