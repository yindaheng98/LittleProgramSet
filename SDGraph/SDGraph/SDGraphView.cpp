
// SDGraphView.cpp : CSDGraphView 类的实现
//
#include "stdafx.h"
#include"CGraph.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CSDGraphView 构造/析构

CSDGraphView::CSDGraphView()
{
	// TODO: 在此处添加构造代码

}

CSDGraphView::~CSDGraphView()
{
}

BOOL CSDGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSDGraphView 绘制

void CSDGraphView::OnDraw(CDC* pDC)
{
	CSDGraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

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


// CSDGraphView 诊断

#ifdef _DEBUG
void CSDGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CSDGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDGraphDoc* CSDGraphView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDGraphDoc)));
	return (CSDGraphDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDGraphView 消息处理程序


void CSDGraphView::OnAddPoint()
{
	CAddPointDlg addlg;
	if (addlg.DoModal() == IDOK)
	{
		graph.AddVex(addlg.m_name[0]);
		cdt = none;
	}
	Invalidate();
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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

	// TODO: 在此添加命令处理程序代码
}
