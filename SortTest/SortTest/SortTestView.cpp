
// SortTestView.cpp : CSortTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SortTest.h"
#endif

#include "SortTestDoc.h"
#include "SortTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortTestView

IMPLEMENT_DYNCREATE(CSortTestView, CView)

BEGIN_MESSAGE_MAP(CSortTestView, CView)
END_MESSAGE_MAP()

// CSortTestView 构造/析构

CSortTestView::CSortTestView()
{
	// TODO: 在此处添加构造代码

}

CSortTestView::~CSortTestView()
{
}

BOOL CSortTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSortTestView 绘制

void CSortTestView::OnDraw(CDC* pDC)
{
	CSortTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 在此处为本机数据添加绘制代码
	void paint(CDC*pDC);
	paint(pDC);
}


// CSortTestView 诊断

#ifdef _DEBUG
void CSortTestView::AssertValid() const
{
	CView::AssertValid();
}

void CSortTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortTestDoc* CSortTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortTestDoc)));
	return (CSortTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortTestView 消息处理程序
