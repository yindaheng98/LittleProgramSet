
// GFFViewerSDI v2View.cpp : CGFFViewerSDIv2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GFFViewerSDI v2.h"
#endif

#include "GFFViewerSDI v2Doc.h"
#include "GFFViewerSDI v2View.h"
#include"ClassGene.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGFFViewerSDIv2View

IMPLEMENT_DYNCREATE(CGFFViewerSDIv2View, CView)

BEGIN_MESSAGE_MAP(CGFFViewerSDIv2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGFFViewerSDIv2View 构造/析构

CGFFViewerSDIv2View::CGFFViewerSDIv2View()
{
	// TODO: 在此处添加构造代码

}

CGFFViewerSDIv2View::~CGFFViewerSDIv2View()
{
}

BOOL CGFFViewerSDIv2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGFFViewerSDIv2View 绘制

void CGFFViewerSDIv2View::OnDraw(CDC* pDC)
{
	CGFFViewerSDIv2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	extern CGene gene;
	gene.paint(40, pDC);
	// TODO: 在此处为本机数据添加绘制代码
}


// CGFFViewerSDIv2View 打印

BOOL CGFFViewerSDIv2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGFFViewerSDIv2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGFFViewerSDIv2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGFFViewerSDIv2View 诊断

#ifdef _DEBUG
void CGFFViewerSDIv2View::AssertValid() const
{
	CView::AssertValid();
}

void CGFFViewerSDIv2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGFFViewerSDIv2Doc* CGFFViewerSDIv2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGFFViewerSDIv2Doc)));
	return (CGFFViewerSDIv2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGFFViewerSDIv2View 消息处理程序
