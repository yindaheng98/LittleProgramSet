
// SortTestView.h : CSortTestView ��Ľӿ�
//

#pragma once


class CSortTestView : public CView
{
protected: // �������л�����
	CSortTestView();
	DECLARE_DYNCREATE(CSortTestView)

// ����
public:
	CSortTestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CSortTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SortTestView.cpp �еĵ��԰汾
inline CSortTestDoc* CSortTestView::GetDocument() const
   { return reinterpret_cast<CSortTestDoc*>(m_pDocument); }
#endif

