
// SDGraphView.h : CSDGraphView ��Ľӿ�
//

#pragma once

class CSDGraphView : public CView
{
protected: // �������л�����
	CSDGraphView();
	DECLARE_DYNCREATE(CSDGraphView)

// ����
public:
	CSDGraphDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CSDGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddPoint();
	afx_msg void OnAddEdge();
	afx_msg void OnShortPath();
	afx_msg void OnPathPoint();
	afx_msg void OnMinitreePrim();
	afx_msg void OnMinitreeKruskal();
};

#ifndef _DEBUG  // SDGraphView.cpp �еĵ��԰汾
inline CSDGraphDoc* CSDGraphView::GetDocument() const
   { return reinterpret_cast<CSDGraphDoc*>(m_pDocument); }
#endif

