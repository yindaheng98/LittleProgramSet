
// SortTestView.cpp : CSortTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CSortTestView ����/����

CSortTestView::CSortTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CSortTestView::~CSortTestView()
{
}

BOOL CSortTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSortTestView ����

void CSortTestView::OnDraw(CDC* pDC)
{
	CSortTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	void paint(CDC*pDC);
	paint(pDC);
}


// CSortTestView ���

#ifdef _DEBUG
void CSortTestView::AssertValid() const
{
	CView::AssertValid();
}

void CSortTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortTestDoc* CSortTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortTestDoc)));
	return (CSortTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortTestView ��Ϣ�������
