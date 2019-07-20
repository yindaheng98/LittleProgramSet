
// GFFViewerSDI v2View.cpp : CGFFViewerSDIv2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGFFViewerSDIv2View ����/����

CGFFViewerSDIv2View::CGFFViewerSDIv2View()
{
	// TODO: �ڴ˴���ӹ������

}

CGFFViewerSDIv2View::~CGFFViewerSDIv2View()
{
}

BOOL CGFFViewerSDIv2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGFFViewerSDIv2View ����

void CGFFViewerSDIv2View::OnDraw(CDC* pDC)
{
	CGFFViewerSDIv2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	extern CGene gene;
	gene.paint(40, pDC);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGFFViewerSDIv2View ��ӡ

BOOL CGFFViewerSDIv2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGFFViewerSDIv2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGFFViewerSDIv2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CGFFViewerSDIv2View ���

#ifdef _DEBUG
void CGFFViewerSDIv2View::AssertValid() const
{
	CView::AssertValid();
}

void CGFFViewerSDIv2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGFFViewerSDIv2Doc* CGFFViewerSDIv2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGFFViewerSDIv2Doc)));
	return (CGFFViewerSDIv2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGFFViewerSDIv2View ��Ϣ�������
