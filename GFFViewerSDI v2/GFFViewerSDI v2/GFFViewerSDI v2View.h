
// GFFViewerSDI v2View.h : CGFFViewerSDIv2View ��Ľӿ�
//

#pragma once


class CGFFViewerSDIv2View : public CView
{
protected: // �������л�����
	CGFFViewerSDIv2View();
	DECLARE_DYNCREATE(CGFFViewerSDIv2View)

// ����
public:
	CGFFViewerSDIv2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGFFViewerSDIv2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GFFViewerSDI v2View.cpp �еĵ��԰汾
inline CGFFViewerSDIv2Doc* CGFFViewerSDIv2View::GetDocument() const
   { return reinterpret_cast<CGFFViewerSDIv2Doc*>(m_pDocument); }
#endif

