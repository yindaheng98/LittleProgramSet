
// SortTestView.h : CSortTestView 类的接口
//

#pragma once


class CSortTestView : public CView
{
protected: // 仅从序列化创建
	CSortTestView();
	DECLARE_DYNCREATE(CSortTestView)

// 特性
public:
	CSortTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CSortTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SortTestView.cpp 中的调试版本
inline CSortTestDoc* CSortTestView::GetDocument() const
   { return reinterpret_cast<CSortTestDoc*>(m_pDocument); }
#endif

