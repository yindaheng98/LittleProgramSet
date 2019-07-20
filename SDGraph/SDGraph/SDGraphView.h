
// SDGraphView.h : CSDGraphView 类的接口
//

#pragma once

class CSDGraphView : public CView
{
protected: // 仅从序列化创建
	CSDGraphView();
	DECLARE_DYNCREATE(CSDGraphView)

// 特性
public:
	CSDGraphDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CSDGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // SDGraphView.cpp 中的调试版本
inline CSDGraphDoc* CSDGraphView::GetDocument() const
   { return reinterpret_cast<CSDGraphDoc*>(m_pDocument); }
#endif

